# Nmap 使用

Nmap（Network Mapper）用于主机发现、端口扫描、服务与版本识别、操作系统探测和脚本扫描，是网络排查与安全评估的基础工具。

> 只扫描自己拥有或已获得明确授权的目标，未经授权的扫描可能违法。

## 安装

```bash
# Arch Linux
sudo pacman -S nmap

# Debian / Ubuntu
sudo apt install nmap

# 查看版本
nmap -V
```

## 基本语法

```bash
nmap [扫描类型] [选项] {目标}
```

目标可以是 IP、域名、网段或文件：

```bash
nmap 192.168.1.10
nmap example.com
nmap 192.168.1.0/24
nmap -iL targets.txt
```

## 快速上手

```bash
# 扫描单机最常见的 100 个端口
nmap -F 192.168.1.10

# 扫描全端口并只显示开放的
nmap -p- --open 192.168.1.10

# 识别服务和操作系统，并运行默认脚本
sudo nmap -A 192.168.1.10

# 保存三种格式的报告
nmap -sV -oA scan 192.168.1.10
```

## 主机发现

|参数|作用|
|---|---|
|`-sn`|只做主机发现，不扫描端口|
|`-Pn`|跳过主机发现，视目标全部在线|
|`-PS22,80`|向指定端口发 TCP SYN 探测|
|`-PA80`|发送 TCP ACK 探测|
|`-PU53`|发送 UDP 探测|
|`-PE` / `-PP` / `-PM`|ICMP echo / 时间戳 / 子网掩码探测|
|`-PR`|ARP 扫描，仅限本地网段（局域网默认）|
|`-n`|不做 DNS 反向解析|
|`-R`|始终做 DNS 解析|
|`--exclude 192.168.1.1`|排除指定主机|

```bash
nmap -sn 192.168.1.0/24
nmap -Pn -n 192.168.1.10
```

目标禁 ping 或防火墙拦截 ICMP 时，用 `-Pn` 继续扫描端口。

## 端口指定

|示例|说明|
|---|---|
|`-p 22`|单个端口|
|`-p 22,80,443`|多个端口|
|`-p 1-1000`|端口范围|
|`-p-`|全部 65535 个端口|
|`-p http,https`|按服务名指定|
|`-p U:53,T:80`|分别指定 UDP / TCP 端口|
|`--top-ports 100`|最常见的 100 个端口|
|`-F`|快速扫描，等价于 top 100|

## 扫描类型

|参数|说明|
|---|---|
|`-sS`|TCP SYN 半开扫描，快速隐蔽，需 root（root 下默认）|
|`-sT`|完整 TCP 连接扫描，非 root 时默认|
|`-sU`|UDP 扫描，速度慢|
|`-sA`|ACK 扫描，用于判断防火墙规则|
|`-sN` / `-sF` / `-sX`|NULL / FIN / Xmas 扫描，绕过部分无状态防火墙|
|`-sn`|仅主机发现|

非 root 用户无法构造原始包，只能用 `-sT`。UDP 扫描建议限定端口：

```bash
sudo nmap -sU -p 53,67,68,123,161 192.168.1.10
```

## 服务与版本探测

```bash
nmap -sV 192.168.1.10
nmap -sV --version-intensity 5 -p 22,80,443 192.168.1.10
```

`-sV` 通过发送探测包识别服务名和版本，强度 `0-9` 越大越准确也越慢。`--version-light` 和 `--version-all` 是常用预设。

## 操作系统探测

```bash
sudo nmap -O 192.168.1.10
sudo nmap -O --osscan-guess 192.168.1.10
```

`-O` 需要目标至少有一个开放端口和一个关闭端口，否则可能无法判断。`--osscan-guess` 允许给出可能性最大的猜测结果。

一条命令同时完成多项探测：

```bash
sudo nmap -A 192.168.1.10
```

`-A` 等价于启用 `-sV`、`-O`、`-sC` 和 `--traceroute`，信息最全但噪声和耗时也最大。

## NSE 脚本

NSE（Nmap Scripting Engine）用 Lua 脚本扩展扫描能力，脚本位于 `/usr/share/nmap/scripts/`。

|参数|作用|
|---|---|
|`-sC`|运行默认脚本，等价 `--script=default`|
|`--script=名称或类别`|运行指定脚本|
|`--script-args`|向脚本传参|
|`--script-help`|查看脚本说明|
|`--script-updatedb`|更新脚本数据库|

常用类别：

|类别|用途|
|---|---|
|`default`|默认脚本，安全且通用|
|`safe`|不会影响目标|
|`discovery`|收集更多主机与服务信息|
|`version`|辅助版本识别|
|`auth`|认证相关检测|
|`vuln`|漏洞检测|
|`brute`|口令爆破|
|`intrusive`|可能影响目标，慎用|

```bash
# 查看网站标题和响应头
nmap -sV --script=http-title,http-headers -p 80,443 192.168.1.10

# 检查 MS17-010
nmap -p 445 --script=smb-vuln-ms17-010 192.168.1.10

# 运行所有漏洞检测脚本
nmap -sV --script=vuln 192.168.1.10

# 查看某类脚本说明
nmap --script-help "http-*"
```

`brute` 和 `intrusive` 类脚本可能触发告警或影响服务，只应在授权环境使用。

## 输出

|参数|说明|
|---|---|
|`-oN file`|普通文本格式|
|`-oX file`|XML 格式，便于程序处理|
|`-oG file`|grepable 格式|
|`-oA base`|同时生成 `.nmap`、`.xml`、`.gnmap`|
|`-v` / `-vv`|提高详细程度|
|`--open`|只显示开放端口|
|`--reason`|显示端口状态判断依据|

```bash
nmap -sV -oA reports/web 192.168.1.10
nmap -oX - 192.168.1.10 > scan.xml
```

后续可用 `grep` 或 `xmlstarlet` 从报告中提取结果。

## 性能与时限

|参数|说明|
|---|---|
|`-T0` ~ `-T5`|时序模板，越高越快|
|`--min-rate` / `--max-rate`|限制每秒发包数|
|`--min-parallelism` / `--max-parallelism`|调整并发探测数|
|`--host-timeout`|单主机超时时间|
|`--scan-delay`|两次探测之间的间隔|

时序模板依次为 `paranoid`、`sneaky`、`polite`、`normal`、`aggressive`、`insane`。日常用 `-T4`，网络不稳定时降到 `-T3`，`-T5` 可能丢包导致漏报。

## 规避与隐蔽（了解）

这些选项用于穿透或干扰检测，日常排查一般不需要：

|参数|作用|
|---|---|
|`-f` / `--mtu`|分片数据包|
|`-D RND:10`|使用诱饵地址混淆来源|
|`--spoof-mac`|伪造源 MAC|
|`--data-length`|附加随机数据改变包长|
|`--source-port`|伪造源端口|
|`--randomize-hosts`|打乱扫描顺序|

现代 IDS/IPS 对这类手段已有识别能力，不要把它当作可靠的隐藏方式。

## 典型工作流

```bash
# 1. 发现网段内在线主机
nmap -sn 192.168.1.0/24

# 2. 快速了解目标开放端口
nmap -T4 -F --open 192.168.1.10

# 3. 全端口确认
nmap -T4 -p- --open 192.168.1.10

# 4. 对开放端口做服务识别和默认脚本
sudo nmap -sV -sC -p 22,80,443 192.168.1.10

# 5. 保存报告
sudo nmap -A -oA scan-192.168.1.10 192.168.1.10
```

排查服务的顺序通常是：主机是否在线 → 端口是否开放 → 服务与版本是什么 → 配置或漏洞是否有问题。
