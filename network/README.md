# 网络

本分区整理网络基础概念、Linux/Windows 网络命令、网络服务、Socket 编程与故障排查相关内容。

## 学习路线

建议按下面的顺序学习，先建立整体模型，再练习命令，最后进入服务和编程：

1. **基础概念**：分层模型 → IP 地址 → 路由 → TCP/UDP → DNS/DHCP → HTTP
2. **命令实践**：Linux 网络命令 → Windows 网络命令
3. **故障排查**：按链路、地址、路由、DNS、端口、防火墙逐层定位
4. **网络服务**：SSH、SCP/SFTP、Nginx、Docker 网络、P2P
5. **编程实践**：C Socket 编程
6. **速查手册**：常见端口、在线工具

## 目录

### 基础概念

- [TCP/IP 分层模型](./basics/tcp-ip.md) : OSI 与 TCP/IP 分层、封装、常用协议
- [IP 地址与路由](./basics/ip.md) : IPv4/IPv6、子网掩码、CIDR、网关、NAT、路由表
- [TCP 与 UDP](./basics/transport.md) : 端口、握手挥手、连接状态
- [DNS 与 DHCP](./basics/dns-dhcp.md) : 域名解析、hosts、DHCP 分配流程
- [HTTP 与 HTTPS](./basics/http.md) : 请求响应、状态码、代理、TLS 概述
- [以太网与网线](./basics/ethernet.md) : 以太网帧、MAC、ARP、网线规格

### Linux 网络

- [Linux 网络命令](./linux/commands.md) : `ip`、`ss`、`ping`、`traceroute`、`curl`、`wget`、`ufw` 等
- [网络故障排查](./linux/troubleshooting.md) : 分层排查流程与常用组合命令

### Windows 网络

- [Windows 网络命令](./windows/commands.md) : `ipconfig`、`arp`、`nslookup`、`netstat`、`tracert` 等

### 网络服务

- [SSH](./services/ssh.md) : 远程登录、密钥认证、隧道转发
- [SCP 与 SFTP](./services/scp-sftp.md) : 远程文件传输
- [Nginx](./services/nginx.md) : HTTP 服务、反向代理
- [Docker 网络](./services/docker-network.md) : 网络模式、端口映射、容器互联
- [P2P](./services/p2p.md) : BT、磁力链接与相关工具

### 编程

- [C Socket 编程](./programming/socket-c.md) : socket、地址结构、TCP 客户端/服务端

### 工具与速查

- [VPN 与代理](./tools/vpn.md) : 节点测试与基础概念
- [网络在线工具](./tools/online-tools.md) : 公网 IP、测速、DDNS 等
- [常见端口速查](./reference/ports.md) : 端口范围与常见服务端口

## 与其他分区的关系

- 网线硬件知识已迁入本分区：[以太网与网线](./basics/ethernet.md)
- Linux 系统安装时的网络验证见：[Arch Linux 安装](../linux/arch/install.md)
- WSL 网络配置见：[WSL](../windows/wsl.md)
- Docker 其他用法见：[Docker](../tools/docker.md)
- I/O 多路复用是 Socket 编程的延伸：[poll IO 多路复用](../program/c/linux/poll.md)

## 维护约定

- 内容以高频、必备的基础知识为主，低频或进阶内容等真正用到时再补充。
- 新增网络相关内容优先放入本分区，并按主题归入对应子目录。
- 迁移旧文档时，在旧位置保留一行跳转，避免链接失效。
- 命令类内容只保留常用参数和典型示例，避免堆砌完整手册。
- 概念类内容尽量用一句话讲清用途，并与实际命令对应。
