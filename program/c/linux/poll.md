# poll IO 多路复用

## 概念

+ IO 多路复用:让单个线程/进程同时监视多个文件描述符,任一就绪即可处理
+ 阻塞式 `read` 一次只能盯一个 fd,poll 把"关心哪些 fd、关心什么事件"交给内核统一等待
+ poll 相对 select 的改进
  \  无 `FD_SETSIZE`(默认 1024)数量限制
  \  `pollfd` 数组由内核填写 revents,不必像 `fd_set` 那样每次调用前重建

## 头文件与函数原型

```c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

+ `fds`  : 待监视的 pollfd 数组
+ `nfds` : 数组元素个数
+ `timeout` : 超时时间(毫秒)

## struct pollfd

```c
struct pollfd {
    int   fd;      // 要监视的文件描述符;负值表示忽略该元素
    short events;  // 入参:关心的事件
    short revents; // 出参:内核填写实际发生的事件
};
```

## 事件标志(events / revents)

| 标志 | 值 | 含义 | 可用位置 |
|------|----|------|----------|
| POLLIN | 0x001 | 可读 | events/revents |
| POLLPRI | 0x002 | 有紧急数据可读 | events/revents |
| POLLOUT | 0x004 | 可写 | events/revents |
| POLLRDNORM | 0x040 | 普通数据可读 | events/revents |
| POLLWRNORM | 0x100 | 普通数据可写 | events/revents |
| POLLERR | 0x008 | 发生错误 | 仅 revents |
| POLLHUP | 0x010 | 挂起(对端关闭) | 仅 revents |
| POLLNVAL | 0x020 | fd 非法 | 仅 revents |

+ `POLLERR` / `POLLHUP` / `POLLNVAL` 即使没在 events 中申请,也会在 revents 中返回
+ 判断方式:`if (fds[i].revents & POLLIN) ...`

## 返回值与 timeout

| 返回值 | 含义 |
|--------|------|
| > 0 | 就绪的 fd 个数(即 revents 非 0 的项数) |
| 0 | 超时,没有任何 fd 就绪 |
| -1 | 出错,errno 被设置 |

+ `timeout > 0` : 等待指定毫秒
+ `timeout = 0` : 立即返回,不阻塞
+ `timeout = -1`: 无限阻塞,直到有 fd 就绪

## 使用步骤(模板)

```c
struct pollfd fds[MAX];
int nfds = 0;

fds[nfds].fd = fd_a;  fds[nfds].events = POLLIN;  nfds++;
fds[nfds].fd = fd_b;  fds[nfds].events = POLLOUT; nfds++;

while (1) {
    int ready = poll(fds, nfds, -1);
    if (ready < 0) {
        if (errno == EINTR) continue; // 被信号中断,重试
        perror("poll");
        break;
    }
    for (int i = 0; i < nfds; i++) {
        if (fds[i].revents == 0) continue;
        if (fds[i].revents & POLLIN)  { /* 读处理 */ }
        if (fds[i].revents & POLLOUT) { /* 写处理 */ }
        if (fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) { /* 关闭并移除 */ }
    }
}
```

## 与 select / epoll 对比

| 维度 | select | poll | epoll |
|------|--------|------|-------|
| 数据结构 | fd_set 位图 | pollfd 数组 | 内核红黑树 + 就绪链表 |
| fd 数量上限 | FD_SETSIZE(默认 1024) | 无(受内存限制) | 无 |
| 每次调用开销 | O(n),需重建 fd_set | O(n),需拷贝整个数组 | O(1),事件驱动 |
| 触发方式 | 水平触发 | 水平触发 | 水平 / 边缘触发 |
| 可移植性 | 最好 | 较好 | 仅 Linux |

## 移除 / 无效 fd 的处理

poll 没有专门的删除接口,靠约定管理数组,常用三种方式:

| 方式 | 做法 | 复杂度 | 特点 |
|------|------|--------|------|
| 标记忽略 | `fds[i].fd = -1` | O(1) | fd 为负值时 poll 忽略该项,revents 置 0;留空洞,可复用 |
| 末尾覆盖 | `fds[i] = fds[--nfds]` | O(1) | 不留空洞,但打乱顺序 |
| 整体搬移 | `memmove` 后续元素后 `nfds--` | O(n) | 保持顺序 |

+ 遍历到无效结构体本身不会出差错(只要 `i < nfds`),真正的坑在于 close 之后有没有同步处理数组
  \  只把 `fd` 设为 -1:poll 忽略该项,revents 为 0,循环中 `continue` 跳过,安全
  \  close 了 fd 却没动数组:fd 号未被复用则 revents 置 POLLNVAL;fd 号已被新打开的 fd 复用则会去监视别人的 fd,产生串号 bug
+ 铁律:不要留下仍指向已关闭 fd 号的结构体继续参与 poll,close 前(或同时)就移除或置 -1
+ 循环中删除时,末尾覆盖要配 `i--`,且循环上限必须用实时的 `nfds`,不要用数组长度(否则会遍历到未初始化的槽位)

```c
for (int i = 0; i < nfds; i++) {
    if (fds[i].revents == 0) continue;

    if (fds[i].revents & (POLLIN | POLLERR | POLLHUP | POLLNVAL)) {
        // ... 处理;需要移除时:
        close(fds[i].fd);
        fds[i] = fds[--nfds];  // 末尾元素补位
        i--;                   // 重新检查补上来的这一项
    }
}
```

## 注意事项

+ `revents` 每次调用由内核清零后重填,不要沿用上一次的值
+ `POLLERR` / `POLLHUP` / `POLLNVAL` 是输出专用,无需在 events 中申请也会返回
+ poll 为水平触发:只要缓冲区仍有数据就会持续返回就绪,处理时尽量读干净
+ 就绪判断后仍需真正 `read` / `write`,并处理 `EAGAIN`
+ fd 数量很大时,线性扫描开销明显,应考虑 epoll
