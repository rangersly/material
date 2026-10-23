# Windows 网络命令

## CMD 常用

|命令|作用|
|---|---|
|`ipconfig /all`|查看 IP、网关、DNS 和 MAC|
|`ipconfig /flushdns`|清空 DNS 缓存|
|`ipconfig /release`|释放 DHCP 地址|
|`ipconfig /renew`|重新获取 DHCP 地址|
|`ping <host>`|测试连通性|
|`tracert <host>`|查看路由路径|
|`nslookup <domain>`|查询 DNS|
|`netstat -ano`|查看连接、监听端口和 PID|
|`arp -a`|查看 ARP 缓存|
|`route print`|查看路由表|

`netstat`、`arp` 在 CMD 中仍然常用；PowerShell 有更现代的对应命令。

## PowerShell 对应

|CMD|PowerShell|
|---|---|
|`ipconfig /all`|`Get-NetIPConfiguration`|
|`ipconfig /flushdns`|`Clear-DnsClientCache`|
|`ping <host>`|`Test-Connection <host>`|
|`tracert <host>`|`Test-NetConnection <host> -TraceRoute`|
|`nslookup <domain>`|`Resolve-DnsName <domain>`|
|`netstat -ano`|`Get-NetTCPConnection`、`Get-NetUDPEndpoint`|
|`arp -a`|`Get-NetNeighbor`|
|`route print`|`Get-NetRoute`|

## WSL 网络

WSL2 默认使用 NAT。WSL 内访问 Windows 服务通常使用 Windows 主机 IP，Windows 访问 WSL 服务通常使用 `localhost` 加端口转发。详见 [WSL](../../windows/wsl.md)。
