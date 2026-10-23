# Linux 网络命令

## 快速排障

```bash
ip a
ip r
ping -c 4 example.com
ss -tlunp
traceroute -n example.com
dig example.com
curl -I https://example.com
```

## ip

|命令|作用|
|---|---|
|`ip a` / `ip addr`|查看接口和 IP 地址|
|`ip link`|查看接口状态|
|`ip link set eth0 up`|启用接口|
|`ip r` / `ip route`|查看路由表|
|`ip neigh`|查看 ARP/NDP 邻居表|
|`ip -s link`|查看收发统计|

### 统计信息

`-s` 是 `statistics` 选项，显示接口的收发统计：

```bash
ip -s link
ip -s link show eth0
ip -s -s link show eth0
```

输出中的 `RX` 是接收，`TX` 是发送，常见指标：

|指标|含义|
|---|---|
|`bytes` / `packets`|字节数 / 包数|
|`errors`|错误包数|
|`dropped`|丢弃包数|
|`overrun`|缓冲区溢出|
|`missed`|资源不足未接收|
|`carrier`|载波错误|
|`collsns`|冲突次数|

连续写两次 `-s`（`ip -s -s link`）会显示更细的错误分类，例如长度错误、CRC、FIFO、overrun。`ip -s addr` 也会在地址信息后附带收发统计。

添加地址和默认路由：

```bash
sudo ip addr add 192.168.1.10/24 dev eth0
sudo ip route add default via 192.168.1.1
```

> 旧教程中的 `ifconfig`、`route`、`arp` 已由 `ip` 取代。

## ping

```bash
ping -c 4 example.com
ping -6 -c 4 example.com
```

`-c` 指定次数，`-i` 指定间隔，`-W` 指定超时。

## traceroute 与 mtr

```bash
traceroute -n example.com
mtr example.com
```

`-n` 不解析域名；`mtr` 适合持续观察每一跳的丢包和延迟。

## ss

```bash
ss -tlunp
ss -s
```

`-t` TCP，`-u` UDP，`-l` 仅监听，`-n` 不解析端口名，`-p` 显示进程。

`Recv-Q`/`Send-Q` 在监听状态下表示当前连接队列和最大队列；非监听状态下表示接收/发送缓冲区。查看其他用户的进程需要 `sudo`。

## nmap

```bash
nmap -sn 192.168.1.0/24
nmap -p 22,80,443 192.168.1.10
nmap -sV -p 80,443 192.168.1.10
```

`-sn` 主机发现，`-p` 指定端口，`-sV` 识别服务版本。只扫描自己有权测试的网络。

## curl

```bash
curl -I https://example.com
curl -i https://example.com
curl -v https://example.com
curl -L -o file.zip https://example.com/file.zip
curl -X POST -H "Content-Type: application/json" -d '{"name":"test"}' https://example.com/api
curl -u user:pass https://example.com
curl -F "file=@photo.jpg" https://example.com/upload
curl -x http://127.0.0.1:8080 https://example.com
```

`-I` 只看响应头，`-i` 带头输出，`-v` 调试，`-L` 跟随重定向，`-x` 使用代理，`-u` Basic 认证，`-F` 上传文件。`-m` 最大耗时，`--connect-timeout` 连接超时。`-k` 忽略证书校验，只用于测试。

## wget

```bash
wget -c https://example.com/file.zip
wget -O file.zip https://example.com/file.zip
wget -P /tmp https://example.com/file.zip
wget -i urls.txt
```

`-c` 断点续传，`-O` 指定文件名，`-P` 指定目录，`-i` 从文件批量下载。

## nmcli

```bash
nmcli device status
nmcli radio wifi on
nmcli device wifi list
nmcli device wifi connect "<SSID>" password "<password>"
nmcli connection show
```

## ufw

```bash
sudo ufw status verbose
sudo ufw allow 22/tcp
sudo ufw allow from 192.168.1.0/24 to any port 22
sudo ufw deny 23/tcp
sudo ufw delete allow 8080/tcp
sudo ufw default deny incoming
sudo ufw enable
```

## iperf3

服务端：

```bash
iperf3 -s
```

客户端：

```bash
iperf3 -c <server-ip>
iperf3 -c <server-ip> -R
iperf3 -c <server-ip> -u -b 100M
```

`-R` 反向测试，`-u` UDP，`-b` 目标带宽，`-P` 并发连接数。服务端默认监听 `5201`，注意防火墙放行。

## vnstat

```bash
vnstat
vnstat -d
vnstat -m
vnstat -i eth0
```

首次使用：

```bash
sudo systemctl enable --now vnstat
sudo vnstat -i eth0 --create
```

## DNS 查询

```bash
dig example.com
dig +short example.com
dig example.com MX
nslookup example.com
```

`dig` 信息更完整，`nslookup` 更简单。

## 抓包

```bash
sudo tcpdump -i any -nn port 80
sudo tcpdump -i eth0 -w capture.pcap
```

`-nn` 不解析地址和端口，`-w` 保存为 pcap 文件。
