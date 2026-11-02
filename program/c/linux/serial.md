# 串口打开与配置

Linux 下串口是字符设备，通常需要以非阻塞方式打开，再通过 termios 配置成原始模式的 8N1、无流控。

常见设备节点：`/dev/ttyS0`（板载 UART）、`/dev/ttyUSB0`（USB 转串口）、`/dev/ttyACM0`（CDC-ACM）。

## 打开设备

```c
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK | O_CLOEXEC);
```

| 标志 | 作用 |
|---|---|
| `O_RDWR` | 读写方式打开 |
| `O_NOCTTY` | 不把设备设为控制终端，避免终端信号干扰 |
| `O_NONBLOCK` | 非阻塞打开，读写无数据时返回 `EAGAIN` |
| `O_CLOEXEC` | `exec` 时自动关闭 fd，防止泄漏给子进程 |

打开失败返回 `-1`，原因在 `errno`。普通用户通常需要加入 `dialout` 组才能访问串口。

## 配置流程

```c
struct termios tty;

tcgetattr(fd, &tty);

cfmakeraw(&tty);

tty.c_cflag &= ~(CSIZE | PARENB | CSTOPB | CRTSCTS);
tty.c_cflag |= (CS8 | CLOCAL | CREAD);

cfsetispeed(&tty, baud);
cfsetospeed(&tty, baud);

tty.c_cc[VMIN] = 1;
tty.c_cc[VTIME] = 0;

tcsetattr(fd, TCSANOW, &tty);
tcflush(fd, TCIFLUSH);
```

以上代码省略了错误检查，实际使用时每一步失败都应关闭 fd 并返回。

各步骤作用：

+ `tcgetattr`：读取当前配置。必须先执行，否则后续会基于未初始化内存修改 termios。
+ `cfmakeraw`：进入原始模式，关闭回显、行缓冲、信号字符和换行转换。
+ `c_cflag`：清 `CSIZE`、`PARENB`、`CSTOPB`、`CRTSCTS`，再设置 `CS8`、`CLOCAL`、`CREAD`，得到 8N1、无流控。
+ `cfsetispeed` / `cfsetospeed`：设置输入/输出波特率，参数必须是 `B9600`、`B115200` 这类 `speed_t` 常量。
+ `VMIN` / `VTIME`：阻塞模式下的读取策略；fd 为非阻塞时内核会忽略它们。
+ `tcsetattr(TCSANOW)`：立即让配置生效。
+ `TCIFLUSH`：丢弃打开前残留的输入数据，避免第一次读取读到脏数据。
+ 失败时关闭已打开的 fd；`close` 可能改写 `errno`，需要先保存再恢复。

## 完整示例

```c
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>

int OpenSerial(const char *path, speed_t baud) {
    if (path == NULL) {
        errno = EINVAL;
        return -1;
    }

    int fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK | O_CLOEXEC);
    if (fd < 0) {
        return -1;
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) < 0) {
        goto fail;
    }

    cfmakeraw(&tty);

    tty.c_cflag &= ~(CSIZE | PARENB | CSTOPB | CRTSCTS);
    tty.c_cflag |= (CS8 | CLOCAL | CREAD);

    if (cfsetispeed(&tty, baud) < 0) {
        goto fail;
    }
    if (cfsetospeed(&tty, baud) < 0) {
        goto fail;
    }

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &tty) < 0) {
        goto fail;
    }

    tcflush(fd, TCIFLUSH);
    return fd;

fail: {
    int saved_errno = errno;
    close(fd);
    errno = saved_errno;
    return -1;
}
}
```

调用：

```c
int fd = OpenSerial("/dev/ttyUSB0", B115200);
if (fd < 0) {
    perror("OpenSerial");
    return 1;
}

char buf[256];
ssize_t n = read(fd, buf, sizeof(buf));
if (n > 0) {
    write(STDOUT_FILENO, buf, (size_t)n);
} else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
    perror("read");
}

close(fd);
```

## 非阻塞读写

返回的 fd 带 `O_NONBLOCK`，直接循环读写会空转。通常配合 `poll`：

```c
#include <poll.h>

struct pollfd pfd = {.fd = fd, .events = POLLIN};

if (poll(&pfd, 1, -1) > 0 && (pfd.revents & POLLIN)) {
    ssize_t n = read(fd, buf, sizeof(buf));
    /* n > 0 有数据；n < 0 且 errno 为 EAGAIN 表示暂时无数据 */
}
```

详见 [poll IO 多路复用](./poll.md)。

## 注意事项

+ 波特率必须与对端一致，否则乱码或收不到数据。
+ `cfmakeraw` 不一定会清除停止位和硬件流控，仍需显式清 `CSTOPB`、`CRTSCTS`。
+ 非阻塞 fd 的 `EAGAIN` / `EWOULDBLOCK` 不是错误，应等待下次可读/可写。
+ `write` 可能只写入一部分，需要循环或配合 `POLLOUT`。
+ 串口是字节流，没有消息边界，需要应用层协议分帧。
+ 成功返回的 fd 由调用方负责 `close`。
