# unistd 头文件

`<unistd.h>` 是 POSIX / C 系统编程的核心头文件之一,提供**进程控制、文件读写、管道通信、用户身份**等系统级操作。本文件收录其常用函数;进程创建相关(如 fd 继承、exec 族)另有专题深入。

统一约定:绝大多数函数以**整型文件描述符 `int fd`** 操作资源,用 `close` 释放、用 `dup`/`dup2` 复制。

---

## 1. 进程控制

### `pid_t fork(void);`

- 创建子进程,返回**新进程的 PID**
- 返回约定(基于调用方视角):
  | 返回值 | 含义 |
  |--------|------|
  | `> 0` | 父进程,返回子进程 PID |
  | `== 0` | 子进程,返回 0 |
  | `< 0` | 出错,`errno` 被设置(如 `EMFILE`) |
- **关键行为**:
  - 子进程是父进程的**镜像**,继承父进程的所有资源:打开的文件描述符、内存映像、环境变量等
  - **共享内存、堆、信号量等需显式同步**,不要假设共享语义
  - 返回后**必须分叉处理**(父/子走不同分支)
- **fd 继承规则**:子进程默认持有父进程全部打开的 fd;创建管道/套接字后务必在子进程中 `close` 不需要的端,否则 fd 泄漏
- **退出约定**:
  - 子进程应使用 **`_exit()`** 而非 `exit()` —— `exit()` 会触发 atexit/缓冲区 flush/清理函数,这些操作依赖"已加载的符号表",而子进程镜像后尚未重新加载,会导致行为异常或输出丢失
  - 切换工作目录、改变身份等操作,子进程需用 `_exit` 立即收尾
- 详见专题:[fork](../linux/fork.cpp)、[exec](../linux/exec.cpp)

```c
/* 父子分叉处理模板 */
pid_t pid = fork();
if (pid < 0) {
    perror("fork");
    return 1;
}
if (pid == 0) {
    /* 子进程:用 _exit 收尾,不要 exit */
    ...
    _exit(0);
}
/* 父进程:等待子进程 */
waitpid(pid, NULL, 0);
```

### `int execve(const char *pathname, char *const argv[], char *const envp[]);`

- 用 `pathname` 指定的**新程序**替换当前进程映像(代码、数据段、堆栈、打开的文件描述符等)
- `argv` 为程序参数数组(含 `argv[0]`),`envp` 为环境变量数组
- 成功**不会返回**(进程已变为新程序);失败返回 `-1` 并设置 `errno`
- 常见失败:`ENOENT`(路径不存在)、`EACCES`(无执行权限)、`EAGAIN`(进程资源不足)
- **fd 语义**:exec 保留父进程所有 fd 及其偏移量,新程序可直接 reuse 已打开的文件(如向 stdout 写入)

```c
char *argv[] = { "ls", "-l", NULL };
char *envp[] = { NULL };
if (execve("/bin/ls", argv, envp) == -1) {
    perror("execve");
    _exit(1);
}
```

### `unsigned int sleep(unsigned int seconds);`

- 阻塞**至多** `seconds` 秒;被信号中断时提前返回已休眠秒数(可能 `> 0`)
- 返回值**不一定等于**传入值(因信号中断),需据此判断是否真的睡够了

---

## 2. 文件操作

### `ssize_t read(int fildes, void *buf, size_t nbyte);`

- 从 fd 指向的文件读取至多 `nbyte` 字节到 `buf`
- **返回实际读取的字节数**
  - `> 0`:成功读取的字节数
  - `== 0`:文件到达**EOF**(读端无进程、或已关闭)
  - `< 0`:出错,返回 `-1`,`errno` 被设置
- **部分传输**:返回字节数可能**小于** `nbyte`,需循环处理直到满足或出错
- **非阻塞**:若 fd 为非阻塞,无数据时返回 `-1` 且 `errno = EAGAIN`
- 读写**共享偏移量**,同一 fd 的多线程访问不安全,改用 `pread`

```c
char buf[BUFSZ];
ssize_t n;
while ((n = read(fd, buf, BUFSZ - 1)) > 0) {
    buf[n] = '\0';
    fputs(buf, stdout);
}
if (n < 0) { perror("read"); }
```

### `ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset);`

- 从指定偏移量 `offset` 处读取,**不改变共享偏移量**,因此**线程安全**
- 返回值语义与 `read` 一致(实际字节数 / EOF / 错误)

### `ssize_t write(int fildes, const void *buf, size_t nbyte);`

- 从 `buf` 向 fd 写入至多 `nbyte` 字节
- **返回实际写入的字节数**
  - `> 0`:成功写入的字节数
  - `== 0`:通常不会发生(成功一般返回 `> 0`)
  - `< 0`:出错,返回 `-1`,`errno` 被设置
- **部分传输**:返回字节数可能**小于** `nbyte`,需循环处理
- **非阻塞**:无空间时返回 `-1` 且 `errno = EAGAIN`
- **管道写入**:无读进程时向管道写端写入会触发 **`SIGPIPE`**(见管道部分)

```c
ssize_t n;
const char *msg = "hello";
while ((n = write(fd, msg, strlen(msg))) == -1 && errno == EINTR)
    continue;
if (n < 0) { perror("write"); }
```

### `ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);`

- 指定偏移量 `offset` 写入,**线程安全**,返回值语义与 `write` 一致

### `int close(int fildes);`

- **关闭**已打开的文件描述符,释放内核为该 fd 占用的资源
- 返回约定:
  | 返回值 | 含义 |
  |--------|------|
  | `0` | 成功 |
  | `-1` | 失败,`errno` 被设置(如 `EBADF` 无效 fd) |
- **调用后 fd 号可能被复用**,不应再使用已关闭的 fd
- 管道/多端 fd 必须**成对关闭**,否则易死锁或触发 EOF

---

## 3. 管道操作

`pipe()` 创建一条**匿名、端到端、无缓冲的字节流通道**,用于进程间通信(仅本机相关进程可用)。

### `int pipe(int fildes[2]);`

- **语义**:
  - `fildes[0]`:读端(数据从此端读取)
  - `fildes[1]`:写端(数据写入此端)
  - 数据**单向流动**,只能从写端写入、从读端读取
- **缓冲区**:内核维护的环形缓冲区,Linux 下默认 **64 KB**;单次写原子安全长度 `PIPE_BUF = 4096`
- **阻塞行为**:写满阻塞写、空时阻塞读(具体取决于 `read`/`write` 是否非阻塞)
- **返回**:
  | 返回值 | 含义 |
  |--------|------|
  | `0` | 成功,`fildes[0]`、`fildes[1]` 分别被设为 `0`、`1` |
  | `-1` | 失败,`errno` 被设置(如 `EMFILE`、`ENFILE`、`EINVAL`) |
- **关键行为**:
  | 场景 | 行为 |
  |------|------|
  | 同一时刻多个进程向写端写 | 只能有一个写入成功,多写方应合并后再写 |
  | 无写进程 | 对读端 `read` 返回 `0`(EOF),`errno = EPIPE` |
  | 无读进程(或缓冲区满) | 向写端写入触发 **`SIGPIPE`** 信号 |
  | 默认 SIGPIPE 动作 | 终止进程;若希望写入返回错误而非崩溃,先 `signal(SIGPIPE, SIG_IGN)`,此时写入返回 `-1`、`errno = EPIPE` |
- **限制**:长度受 64 KB 约束,不适合大数据量传输;仅字节流(无"行/记录"结构),不能跨机器(跨机器用 socket)

```c
/* 父写子读示例:子进程分支末尾必须 _exit,否则坠落到父进程代码 */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSZ 64

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

    if (pid == 0) {
        /* 子进程:关闭写端,只保留读端 */
        close(fd[1]);
        printf("child: 读取到: ");
        char buf[BUFSZ];
        ssize_t n;
        while ((n = read(fd[0], buf, BUFSZ - 1)) > 0) {  /* 读 BUFSZ-1 避免溢出 */
            buf[n] = '\0';
            fputs(buf, stdout);
        }
        fflush(stdout);   /* _exit 前必须刷新,否则输出丢失 */
        if (n == -1) { perror("read"); _exit(1); }
        _exit(0);          /* 子进程必须显式退出 */
    }

    /* 父进程:关闭读端,向写端写入,等待子进程结束 */
    close(fd[0]);
    const char *msg = "hello from parent via pipe\n";
    write(fd[1], msg, strlen(msg));
    close(fd[1]);

    wait(NULL);
    printf("parent: done\n");
    return 0;
}
```

**配套函数**:`fork`、`dup2`(把管道端传给子进程)、`close`(用完须关闭两端)、`read`/`write`(传输)、`exec*`(子进程 exec 前关闭多余端)。**限制**:长度受 64 KB 约束,不适合大数据量传输;必须成对、正确地 `close`,否则易死锁或丢数据。

---

## 4. 其他

### `int dup(int fildes);`

- 复制 `fildes` 指向的文件描述符,返回一个新的、指向**同一目标**(同一 offset)的 fd
- 成功返回新 fd,失败返回 `-1` 并设置 `errno`

### `int dup2(int fildes, int fildes2);`

- 将 `fildes` 的引用复制到 `fildes2`
- **关键行为**:若 `fildes2` 已被打开且 `fildes2 != fildes`,会**先被关闭**再复制
- 返回约定:
  | 返回值 | 含义 |
  |--------|------|
  | `fildes2` | 成功(含 `fildes2 == fildes` 的特殊情况) |
  | `-1` | 失败,`errno` 被设置(`EBADF`、`EINVAL`) |

### `int isatty(int fd);`

- 判断 fd 是否指向**终端**
  | 返回值 | 含义 |
  |--------|------|
  | 非 `0` | 真(是终端) |
  | `0` | 假(不是终端) |

### `uid_t getuid(void);` / `uid_t geteuid(void);`

- `getuid()`:返回进程的**有效用户 ID**(effective UID)
- `geteuid()`:返回进程的**真实用户 ID**(real UID)
- 二者不同(如进程被 setuid 后),获取身份/权限时常需区分

### `int chdir(const char *path);`

- 切换进程工作目录
- 成功返回 `0`,失败返回 `-1` 并设置 `errno`

### `char *getcwd(char *buf, size_t size);`

- 将当前工作目录写入 `buf`(以 `\0` 结尾)
- 成功返回 `buf`,失败返回 `NULL` 并设置 `errno`

### `unsigned int usleep(useconds_t usec);`

- 阻塞**至多** `usec` 微秒;被信号中断时提前返回已休眠微秒数
- 返回值**不一定等于**传入值,需据此判断是否真的睡够

---

> 说明:本文件为 POSIX/unistd 头文件 API 索引与要点;进程创建底层语义(如 fd 继承细节、exec 族)请参见专题 [fork](../linux/fork.cpp)、[exec](../linux/exec.cpp)。
