# C Socket 编程

## 头文件

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
```

> 使用 `-std=c11` 等严格模式编译时，需要定义 `_POSIX_C_SOURCE=200809L`，或直接使用 `-std=gnu11`。

## 核心流程

- TCP 服务端：`socket` → `bind` → `listen` → `accept` → `recv`/`send` → `close`
- TCP 客户端：`socket` → `connect` → `send`/`recv` → `close`
- 函数失败通常返回 `-1`，错误码在 `errno`

## socket()

```c
int socket(int domain, int type, int protocol);
```

|参数|常用值|
|---|---|
|`domain`|`AF_INET`（IPv4）、`AF_INET6`（IPv6）|
|`type`|`SOCK_STREAM`（TCP）、`SOCK_DGRAM`（UDP）|
|`protocol`|通常填 `0`，由内核根据前两个参数选择|

## 地址结构

```c
struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
};
```

- `sin_family = AF_INET`
- `sin_port = htons(port)`
- `sin_addr` 用 `inet_pton` 填充
- `bind`/`connect` 需要转换成 `(struct sockaddr *)`

## 字节序

网络字节序是大端，端口和 32 位地址需要转换：

|函数|作用|
|---|---|
|`htons` / `htonl`|主机字节序转网络字节序|
|`ntohs` / `ntohl`|网络字节序转主机字节序|

## 地址转换

```c
struct sockaddr_in addr = {0};
char buf[INET_ADDRSTRLEN];

inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof buf);
```

`inet_pton`/`inet_ntop` 替代旧的 `inet_addr`/`inet_aton`/`inet_ntoa`，支持 IPv6 且线程安全。

## 域名解析

```c
struct addrinfo hints = {0}, *res, *p;
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

if (getaddrinfo("example.com", "80", &hints, &res) != 0) {
    return 1;
}

int fd = -1;
for (p = res; p != NULL; p = p->ai_next) {
    fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (fd < 0) continue;
    if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) break;
    close(fd);
    fd = -1;
}

freeaddrinfo(res);
```

`getaddrinfo` 替代只支持 IPv4、非线程安全的 `gethostbyname`。遍历结果时使用 `res->ai_family`、`res->ai_socktype`、`res->ai_addr`。

## 常用函数

|函数|作用|
|---|---|
|`bind`|绑定本地地址和端口|
|`listen`|把 socket 转为监听状态|
|`accept`|取出已完成连接的客户端|
|`connect`|客户端发起连接|
|`send`/`recv`|收发数据，可能只处理一部分，需要循环|
|`close`|关闭 socket|

服务端建议设置 `SO_REUSEADDR`，避免重启时端口被占用：

```c
int opt = 1;
setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
```

## 最小 TCP 服务端

```c
int fd = socket(AF_INET, SOCK_STREAM, 0);
if (fd < 0) { perror("socket"); return 1; }

int opt = 1;
setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

struct sockaddr_in addr = {0};
addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
addr.sin_addr.s_addr = htonl(INADDR_ANY);

if (bind(fd, (struct sockaddr *)&addr, sizeof addr) < 0) { perror("bind"); return 1; }
if (listen(fd, 128) < 0) { perror("listen"); return 1; }

struct sockaddr_in peer;
socklen_t len = sizeof peer;
int conn = accept(fd, (struct sockaddr *)&peer, &len);
if (conn < 0) { perror("accept"); return 1; }

char buf[1024];
ssize_t n = recv(conn, buf, sizeof buf, 0);
if (n > 0) send(conn, buf, n, 0);

close(conn);
close(fd);
```

## 最小 TCP 客户端

```c
int fd = socket(AF_INET, SOCK_STREAM, 0);
if (fd < 0) { perror("socket"); return 1; }

struct sockaddr_in addr = {0};
addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

if (connect(fd, (struct sockaddr *)&addr, sizeof addr) < 0) {
    perror("connect");
    return 1;
}

send(fd, "hello", 5, 0);

char buf[1024];
ssize_t n = recv(fd, buf, sizeof buf, 0);

close(fd);
```

## 常见问题

- `EADDRINUSE`：端口被占用，检查旧进程或设置 `SO_REUSEADDR`
- `ECONNREFUSED`：目标端口未监听或被防火墙拒绝
- `send`/`recv` 返回值小于请求长度：需要循环处理剩余数据
- 同时处理多个连接：使用 `poll`/`epoll`，见 [poll IO 多路复用](../../program/c/linux/poll.md)
