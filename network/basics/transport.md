# TCP 与 UDP

## 一句话

传输层用端口区分应用，TCP 可靠，UDP 轻量。

## TCP 与 UDP 对比

|特性|TCP|UDP|
|---|---|---|
|连接|面向连接|无连接|
|可靠性|确认、重传、按序|不保证到达和顺序|
|速度|开销较大|开销小|
|典型用途|HTTP、SSH、SMTP|DNS、DHCP、视频、游戏|

## 端口

- `0-1023`：系统端口
- `1024-49151`：注册端口
- `49152-65535`：客户端临时端口
- 服务端监听固定端口，客户端通常使用临时端口

常见端口见 [端口速查](../reference/ports.md)。

## TCP 三次握手

1. 客户端发送 `SYN`
2. 服务端回复 `SYN-ACK`
3. 客户端回复 `ACK`

目的：确认双方都能收发，并同步序列号。

## TCP 四次挥手

1. 主动方发送 `FIN`
2. 被动方回复 `ACK`
3. 被动方发送 `FIN`
4. 主动方回复 `ACK`

主动关闭方进入 `TIME_WAIT`，等待 2MSL，确保最后的 `ACK` 能到达并让旧数据包过期。

## 常见连接状态

|状态|含义|
|---|---|
|`LISTEN`|服务端正在监听|
|`SYN_SENT`|客户端已发送 SYN|
|`ESTABLISHED`|连接已建立|
|`FIN_WAIT_1/2`|主动关闭过程中|
|`CLOSE_WAIT`|被动方等待应用关闭|
|`TIME_WAIT`|主动关闭后的等待状态|
|`SYN_RECV`|服务端收到 SYN，等待最后确认|

## 查看连接

```bash
ss -tlunp
ss -tan
ss -s
```

`Recv-Q`/`Send-Q` 在监听状态下表示当前连接队列和最大队列，非监听状态下表示接收/发送缓冲区。

## 快速判断

- `TIME_WAIT` 很多：通常是短连接多，不一定是故障
- `CLOSE_WAIT` 很多：通常是程序没有正确 `close`
- `SYN_RECV` 很多：可能是 SYN Flood 或服务端队列满

## 相关

- [IP 地址与路由](./ip.md)
- [DNS 与 DHCP](./dns-dhcp.md)
- [Linux 网络命令](../linux/commands.md)
