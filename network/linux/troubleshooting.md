# 网络故障排查

## 排查顺序

按链路 → 地址 → 路由 → 连通性 → DNS → 端口 → 防火墙 → 抓包逐层缩小范围。

## 1. 检查链路

```bash
ip link
ip -s link
nmcli device status
```

关注接口是否 `UP`、是否有收发统计、Wi-Fi 是否连接。没有链路时先检查网线、Wi-Fi 和接口状态。

## 2. 检查地址

```bash
ip a
ip r
```

- 地址是 `169.254.x.x`：DHCP 没有拿到地址
- 没有默认路由：网关配置问题
- 不清楚目标怎么走：`ip route get 8.8.8.8`

## 3. 检查连通性

```bash
ping -c 4 <网关IP>
ping -c 4 8.8.8.8
ping -c 4 example.com
traceroute -n example.com
mtr example.com
```

判断顺序：

- 网关都不通：本机链路、地址或局域网问题
- 网关通、`8.8.8.8` 不通：路由、上游网络或防火墙问题
- IP 通、域名不通：DNS 问题
- 时通时不通：看 `mtr` 的丢包位置

## 4. 检查 DNS

```bash
dig example.com
dig @8.8.8.8 example.com
getent hosts example.com
resolvectl status
```

- 默认 DNS 失败、指定 `8.8.8.8` 成功：本机 DNS 配置问题
- `NXDOMAIN`：域名不存在
- 超时：DNS 服务器不可达
- 解析结果不对：检查 `/etc/hosts`、缓存和 TTL

## 5. 检查端口和服务

```bash
ss -tlunp
ss -tan
curl -v http://127.0.0.1:8080
```

- 没有 `LISTEN`：服务没启动或监听地址不对
- 只监听 `127.0.0.1`：外部访问不到，需要监听 `0.0.0.0` 或指定网卡地址
- `Connection refused`：端口没有监听或被拒绝
- 连接超时：更可能是路由、防火墙丢包或目标不可达

## 6. 检查防火墙

```bash
sudo ufw status verbose
sudo nft list ruleset
```

同时检查云服务器安全组和上游防火墙。Docker 可能绕过 ufw，见 [Docker 网络](../services/docker-network.md)。

## 7. 抓包确认

```bash
sudo tcpdump -i any -nn host <目标IP> and port <端口>
sudo tcpdump -i any -nn -w capture.pcap
```

关注：

- 只有 SYN、没有 SYN-ACK：目标未响应或被拦截
- 出现 RST：端口关闭或被拒绝
- 大量重传：链路质量差或丢包

## 常见现象速查

|现象|优先检查|
|---|---|
|地址是 `169.254.x.x`|DHCP|
|`ping` IP 通、域名不通|DNS|
|网关通、外网不通|路由、上游网络、防火墙|
|`Connection refused`|端口未监听或被拒绝|
|连接超时|防火墙丢包、路由、目标不可达|
|本机访问正常、外部访问失败|监听地址、防火墙、安全组|
|`TIME_WAIT` 很多|短连接较多，不一定是故障|
|`CLOSE_WAIT` 很多|程序没有正确关闭连接|
|HTTPS 证书报错|证书、域名、系统时间|

## 相关

- [Linux 网络命令](./commands.md)
- [IP 地址与路由](../basics/ip.md)
- [TCP 与 UDP](../basics/transport.md)
- [DNS 与 DHCP](../basics/dns-dhcp.md)
