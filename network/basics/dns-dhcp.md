# DNS 与 DHCP

## DNS

作用：把域名解析成 IP 地址。

解析顺序大致是：本机缓存和 `hosts` → 递归 DNS 服务器 → 根服务器 → 顶级域 → 权威 DNS。TTL 决定缓存多久。

## 常见记录

|记录|用途|
|---|---|
|`A`|IPv4 地址|
|`AAAA`|IPv6 地址|
|`CNAME`|域名别名|
|`MX`|邮件服务器|
|`TXT`|验证信息、SPF 等|
|`NS`|权威 DNS 服务器|
|`PTR`|反向解析|

## 本机配置

- `/etc/hosts`：本地静态解析，优先级高于 DNS
- `/etc/resolv.conf`：配置 DNS 服务器
- 使用 systemd-resolved 时，用 `resolvectl status` 查看
- `getent hosts example.com` 按系统实际顺序查询

## 常用命令

```bash
dig example.com
dig +short example.com
dig example.com MX
nslookup example.com
```

`dig` 信息更完整，`nslookup` 更简单。

## DNS 排查

- 能 `ping` IP 但不能 `ping` 域名：DNS 问题
- `dig` 超时：DNS 服务器不可达
- 返回 `NXDOMAIN`：域名不存在
- 改了记录不生效：TTL 缓存还没过期

## DHCP

作用：自动分配 IP、子网掩码、网关和 DNS。

DORA 流程：

1. **Discover**：客户端广播寻找 DHCP 服务器
2. **Offer**：服务器提供一个可用地址
3. **Request**：客户端请求使用该地址
4. **Ack**：服务器确认分配

地址有租约，到期前会续租。DHCP 失败时常见 `169.254.x.x` 地址。

## 端口

- DNS：`53/TCP` 和 `53/UDP`
- DHCP：`67/UDP` 服务端，`68/UDP` 客户端

## 相关

- [IP 地址与路由](./ip.md)
- [HTTP 与 HTTPS](./http.md)
- [Linux 网络命令](../linux/commands.md)
