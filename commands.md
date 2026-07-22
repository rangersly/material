# 命令大全

- [文件与目录](#文件与目录)
- [文本与数据流](#文本与数据流)
- [系统信息与监控](#系统信息与监控)
- [磁盘与文件系统](#磁盘与文件系统)
- [用户与权限](#用户与权限)
- [进程与服务管理](#进程与服务管理)
- [网络](#网络)
- [软件包管理](#软件包管理)
- [开发工具](#开发工具)
- [实用工具集](#实用工具集)

## 文件与目录

- **查找**
  - [find](#find) : 文件查找
  - **locate** : 高效文件查找
  - [which](#which): 查找命令
- **查看与编辑**
  - [cat](#cat) : 输出文件内容
  - [tail](#tail): 显示文件的末尾内容
  - [od](#od) : 查看二进制文件内容
  - [vim](./tools/vim/vim.md) : 文件内容编辑工具
- **属性与统计**
  - [ls](#ls) : 查看当前工作目录下的文件
  - [file](#file): 查看文件类型
  - [wc](#wc) : 统计文件信息
- **差异与补丁**
  - [diff](#diff): 文件差异对比
  - [patch](#patch) : 补丁
- **同步与备份**
  - [rsync](#rsync) : 文件同步命令,更好用的cp
- **打包压缩**
  - [tar](#tar) : 打包工具,将许多文件合而为一(方便压缩)
  - [gzip](#gzip) : 最通用的压缩
  - [xz](#xz) : 现代化的压缩工具
- **基本操作**
  - **mv** : 移动/重命名
  - [cp](#cp) : 复制
  - **rm** : 删除
  - **ln** : 链接(加-s为符号链接)
- **权限与属性**
  - [chmod](#chmod): 更改文件权限
  - **chown** : 更改文件所有者
  - **umask** : 默认权限掩码
  - [acl](#acl): 访问控制列表
  - [attr](#attr): 底层文件属性控制

## 文本与数据流

- **文本处理**
  - [grep](#grep) : 查找指定内容
  - **awk**
  - **sed**
- **管道与重定向**
  - [tee](#tee): 数据分流
- **编解码与校验**
  - **md5sum** : MD5 校验
  - **sha1sum** : SHA1 校验
  - **cksum** : CRC 校验
  - **base64** : Base64 编解码
  - **basenc** : 各种 base 变种
  - **iconv** : 字符编码转换
  - **xxd** : 十六进制转换

## 系统信息与监控

- **系统信息**
  - [uname](#uname): 系统内核版本等信息
  - [dmidecode](#dmidecode): 硬件信息
  - [uptime](#uptime): 负载信息
- **资源监控**
  - [top](#top): 进程实时监控
  - [btop](#btop): 更现代的 top
  - [vmstat](#vmstat): 计算机资源统计
  - [iostat](#iostat) : 监测磁盘活动
  - [perf](./program/tool/perf.md): 性能分析工具
- **用户与会话**
  - [last](#last) : 查看用户登录记录
  - [whoami](#whoami): 当前用户
  - [id](#id): 身份信息

## 磁盘与文件系统

- **设备查看**
  - [lsblk](#lsblk) : 查看块设备及其依赖关系
  - [smartctl](#smartctl) : 查看 S.M.A.R.T. 参数
- **分区管理**
  - [parted](#parted): 分区工具
- **挂载管理**
  - [mount](#mount): 挂载文件系统
  - [umount](#umount): 卸载文件系统
  - **/etc/fstab** : 开机自动挂载配置
- **磁盘用量**
  - [df](#df): 磁盘空间使用情况
  - [du](#du): 文件占用大小分析
- **磁盘操作**
  - [dd](#dd): 磁盘克隆与备份

## 用户与权限

- **用户管理**
  - [sudo](#sudo): 权限提升
  - [useradd](#useradd): 添加用户
  - [userdel](#userdel): 删除用户
  - [usermod](#usermod): 修改用户
  - [passwd](#passwd): 密码管理
- **组管理**
  - [groupadd](#groupadd): 添加组
  - [newgrp](#newgrp): 切换有效用户组
- **身份查询**
  - [id](#id): 用户与组 ID
  - [whoami](#whoami): 显示当前用户
  - [last](#last) : 查看用户登录记录

## 进程与服务管理

- **进程查看**
  - [ps](#ps): 进程快照
  - [lsof](#lsop): 查看占用文件的进程 (原 `lsop` 应为 `lsof`)
- **作业控制**
  - `&` : 加在命令末尾直接在后台运行
  - `jobs` : 列出当前终端中所有后台任务
  - `bg %n` : 将暂停的作业在后台继续运行
  - `fg` : 将后台作业拉回前台
  - `Ctrl + z` : 将当前前台任务暂停扔到后台
  - `nohup 命令 &` : 使程序在终端关闭之后继续运行
  - [tmux](./tools/tmux.md) : 终端复用器
  - [xargs](#xargs) : 并行任务工具
- **信号与资源**
  - `kill %n` : 发送信号让任务停止,也可以`kill -9 %n`强制杀
  - [ulimit](#ulimit): 资源限制
- **服务管理**
  - [systemctl](#systemctl): 系统服务管理

## 网络

- **基础配置**
  - [ip](#ip) : 多功能网络工具
  - [NetworkManager](#networkmanager): 网络连接管理 (nmcli)
- **连接与诊断**
  - [ping](#ping): 连通性测试
  - [ss](#ss) : 套接字统计
  - [nmap](#nmap): 网络探测
  - [vnstat](#vnstat) : 网络流量日志
- **数据传输**
  - [curl](#curl): URL 传输工具
  - [wget](#wget): 文件下载
- **防火墙**
  - [ufw](#ufw) : 简化防火墙配置
- **性能测试**
  - [iperf3](#iperf) : 网络性能测试

## 软件包管理

- **Debian 系**
  - [apt](#apt): 高级包管理工具
  - [dpkg](#dpkg): 底层包管理
- **archlinux**
  - [pacman](#pacman)

## 开发工具

- [objdump](./program/tool/objdump.md) : 可执行文件反汇编
- [readelf](./program/tool/readelf.md) : ELF 文件结构分析

## 实用工具集

- [bc](#bc): 高精度计算器
- [timeshift](#timeshift) : 系统备份与恢复
- [ffmpeg](./tools/ffmpeg.md) : 多媒体处理工具

## ls

- `ls [<选项>]`

|选项|功能|
|---|---|
|`-F`|在文件名后加提示符 '/' '*' '@'|
|`-a`|显示隐藏文件|
|`-l`|列出文件信息|
|`-d`|目录|
|`-h`|将文件大小输出为易读的格式|
|`-s`|在行首显示大小|
|`-i`|inode|

## cat

`-n` 显示行号

## od

- `-t [<o/x>]` 使用不同进制显示

## grep

- 基本命令格式
  - `grep [选项] "要搜索的字符串" 目标路径`

|选项|功能|
|---|---|
|`-A <n>`|后续n行|
|`-B <n>`|前n行|
|`-n`|显示行号|
|`-v`|反向选择|
|`-r`|递归搜索子目录|
|`-i`|忽略大小写|
|`-E 'o1|o2|o3'`|多匹配|

## wc

|参数|效果|
|---|---|
|`-l`|行数|
|`-m`|字符|
|`-w`|word|

## cp

|参数|效果|
|---|---|
|`-a`|归档模式|
|`-p`|保留文件的原始属性|
|`-i`|覆盖时警告|
|`-b`|重合加~|
|`-u`|仅复制更新|
|`-v`|详细显示|
|`-r`|目录|

## rm

|参数|效果|
|---|---|
|`-i`|删除时询问|
|`-r`|递归删除子目录|
|`-f`|强制删除|

## chmod

- `-R` 同时更改所有子目录

特殊权限 : 4位显示法的第一位

```
SUID    4
    执行二进制文件时,权限提升为文件所有者

SGID    2
    在此权限下的目录进入后,有效用户组变为所有组

SBIT    1
    在此权限下的文件夹里创建文件,仅有root与属主有权操作
```

## file

查看文件的信息

|参数|效果|
|---|---|
|`-i`|查看编码格式|
|`-z`|查看压缩格式|
|`-b`|查看文件的系统架构|
|`-p`|详细信息|

## diff

|参数|效果|
|---|---|
|`-r`|递归比较两个目录|
|`-b`|忽略空格|
|`-i`|忽略大小写|
|`-B`|忽略空白行|
|`-w`|忽略空白字符|
|`-u`|使用"统一格式”显示,易于生成补丁文件|

## patch

补丁文件
- [diff](#diff):文件差异对比

```bash
    diff -Naur <oldfile> <newfile>  >  <file.patch##     # -p[n] 拿掉路径中的/
    patch -p<n> <  <file.patch##         # 制作
    patch -p<n>-R <  <file.patch##     # 还原
```

## rsync

|参数|效果|
|---|---|
|`-a(archive)`|归档模式,用于完整同步|
|`-v(verbose)`|详细模式,显示同步过程中的详细信息.|
|`-u(update)`|仅在目标文件不存在或源文件更新时才同步.|
|`-z(compress)`|在传输过程中压缩文件数据.|
|`--delete`|删除目标目录中多余的文件,使目标目录与源目录保持一致|
|`-e(rsh)`|指定远程连接时使用的工具(如 ssh).|
|`--exclude`|指定排除的文件或目录模式.|
|`--include`|指定包含的文件或目录模式.|
|`-P --progress`|显示同步进度.|
|`--bwlimit `| 限速,用于单个大文件,避免占用过多带宽|
|`--dry-run`|模拟同步操作,不实际执行,用于测试同步命令的效果.|

**示例内容**

1.  本地同步
    `rsync -avP /path/to/source/ /path/to/destination/`
2.  从本地同步到远程
    `rsync -avzP /path/to/source/ user@remote_host:/path/to/destination/`
3.  同步时删除多余文件
    `rsync -av --delete /path/to/source/ /path/to/destination/`
4.  排除某些文件或目录
    `rsync -av --exclude 'temp/*' --exclude '*.log' /path/to/source/ /path/to/destination/`
    --exclude 'temp/*':排除 temp 目录下的所有文件.
    --exclude '*.log':排除所有 .log 文件.
5.  包含某些文件或目录
    `rsync -av --include 'data/*' --exclude '*' /path/to/source/ /path/to/destination/`
    --include 'data/*':仅包含 data 目录下的文件.
    --exclude '*':排除其他所有文件.
6.  模拟同步操作
    `rsync -av --dry-run /path/to/source/ /path/to/destination/`

## find

|参数|效果|
|---|---|
|`-name [filename]`|指定文件名|
|`-print`|打印结果在终端|
|`-type [type]`|指定类型|
|`-atime <+-n##`|n天前使用的文件|
|`-mtime <+-n##`|n天前修改的文件|
|`find /usr/bin -name zip -print`|

## which

+    -a    全部列出

## uname

显示系统版本

+    -a    全部信息

## gzip

+ `-d` 解压
+ `-l` 查看压缩效果

## xz

- **参数**
  - `-d` 解压
  - `-l` 查看压缩效果
  - `-k` 保留压缩原文件
  - `-[0-9]` 压缩等级(
  - `-T [0-j]` 使用多个线程,0为尽可能多
  - `-v` 显示详细过程
  - `-c` 输出到标准输出,通常用于管道操作
  - `-tvv` 测试完整性详细信息
- **示例**
  - `xz filename` 生成filename.xz,原文件消失(加k保留原文件)
  - `xz -l --verbose filename.xz` 查看压缩文件信息
  - `xc -c filename > filename.xz`

## tar

- `-c` 创建
- `-x` 解开
- `-v` 显示详细过程
- `-f [file]` 指定文件名
- `-z` 调用gzip
- `-J` 调用xz
- `-p` 保留权限和所有

- `tar -cvjf shell.tar.bz2 shell/

## dd

- `if`    input file/device
- `of`    output file/device
- `bs`    one black size
- `count` count
- `oflag=sync`  sync


## mount
    +    -r            # 只读
    +    -o <loop>     # 特殊设备
    +    auto          # 开机自动挂载
    +    noauto        # 不自动挂载
    +    ro            # read only
    +    rw            # read and write
    +    user          # 任意用户可挂载

- `/etc/fstab` 文件
- `[设备/UUID] [挂载点] [文件系统] [参数] 0 0`


## df
    +    df -hT

##  smartctl

- `-a` 全部参数

|属性ID|属性名              |含义	            |正常范围	|重要性 |
|1	   |Raw_Read_Error_Rate	|原始读取错误率	    |越低越好	|高     |
|3	   |Spin_Up_Time        |启动时间（毫秒）	|< 10000ms	|中     |
|4	   |Start_Stop_Count    |启动/停止次数	    |< 300,000	|中     |
|5	   |Reallocated_Sector_Ct|重分配扇区数	    |0       	|非常高 |
|7	   |Seek_Error_Rate	    |寻道错误率	        |越低越好   |高     |
|9	   |Power_On_Hours	    |通电时间(h)        |根据型号	|中     |
|10	   |Spin_Retry_Count	|旋转重试次数	    |0	        |高     |
|12	   |Power_Cycle_Count	|电源开关次数	    |< 50,000	|中     |
|187   |Reported_Uncorrect	|报告不可纠正错误	|0	        |非常高 |
|188   |Command_Timeout	    |命令超时次数	    |0	        |高     |
|189   |High_Fly_Writes	    |飞行高度写入错误	|0	        |高     |
|190   |Airflow_Temperature_Cel|温度（摄氏度）	|20-50°C	|中     |
|192   |Power-Off_Retract_Count|意外断电次数	|越低越好	|中     |
|193   |Load_Cycle_Count	|磁头加载/卸载次数	|< 600,000	|中     |
|194   |Temperature_Celsius	|温度（另一种表示）	|20-50°C	|中     |
|197   |Current_Pending_Sector|待处理扇区数	    |0       	|非常高 |
|198   |Offline_Uncorrectable|离线不可纠正扇区	|0	        |非常高 |

## parted
    +    -i        列出所有设备的分区信息
    +    -s        非交互模式
    +    print                    显示当前设备的分区表
    +    mklabel [gpt/msdos]        创建分区表
    +    mkpart [part-type] [fs-type] [start] [end]        创建一个分区
`例:    mkpart primary ext4 1MiB 1000MiB`
    +    rm [number]                删除指定编号的分区
    +    resizepart [number] [size]    重调大小
    +    set [number] [mode]        设置分区标志
    +    quit
`sudo parted -s /dev/sdb mklabel gpt mkpart primary ext4 0% 100%`
`sudo parted -s /dev/sdb rm 2`


## sudo

授权用户以其他用户身份执行程序

### 优势

- 最小权限:只有必要权限
- 完整审计追踪:记录所有操作
- 细粒度控制:针对不同用户/组设置不同权限
- 用户使用自己的密码即可,无需root密码

### 常用选项

|参数|作用|
|---|---|
|`-u <用户>`|指定以某用户权限|
|`-i`|模拟完整的登录环境|
|`-l`|列出当前用户可执行的命令|
|`-e <文件名>`|编辑系统配置文件临时提权,强烈推荐!|

### 配置

`/etc/sudoers` 包含用户的名字,可执行的命令,执行身份等写入配置

- **权限规则设置** : `用户 主机=(运行身份:组) 命令`
  - 用户如果使用用户组进行标记的话要在前面加个`%`
  - 定义用户别名 : `User_Alias ADMINS = alice, rg, e0x1a`
  - 定义命令别名 : `Cmnd_Alias CMD = /usr/bin/systemctl start nginx,/usr/bin/systemctl stop nginx`

> [!IMPORTANT]
> 更推荐在`/etc/sudoers.d/`下创建配置,避免文件出错影响整体配置

### 使用记录

对于使用`systemd`的系统可以使用`journalctl`查看记录

- `sudo journalctl _COMM=sudo` 查看日志
- `sudo journalctl _COMM=sudo --since today` 仅查看今天
- `sudo journalctl _COMM=sudo _UID=1001` 通过`id -u <username>` 获取用户uid,然后进行过滤

## useradd
    +    -m        # 同时建立主目录
    +    -g        # 指定用户组
    +    -s        # 指定shell

## userdel
    +    -r        # 删除主目录

## usermod
    +    -d            # 修改主目录
    +    -e <MM/DD/YY># 修改账号有效期
    +    -s            # 修改shell

## id

- `/etc/passwd`
- `登录名:口令:UID:GID:x信息:主目录:shell`

`/etc/group`
    +    组名:组口令(一般无):GID:user1,user2,user3

__用户所有组是passwd和groups的并集__

## last

- **-n <数字>**  表示查看最近n条
- **-i**  显示IP而不是主机名

## ps

+    aux

## vmstat

+ **`r`**      cpu队列
+ **`b`**      io等待
+ **`si/so`**  swap队列

- `-f`  自启动fork次数
- `-d`  磁盘统计信息
- `-s`  统计

## ulimit

- 查看和修改进程运行资源限制
- `-H/S`        # 设置/显示 软/硬 限制
- `-a`          # 显示所有
- `-t`          # cpu time
- `-f`          # file size
- `-s`          # stack size
- `-c`          # core file size
- `-m`          # memory size
- `-l`          # lock memory size
- `-p`          # user processes
- `-n`          # open file

## ip

实现了Linux的网络命名空间,主要作用于数据链路层和网络层(TCP/IP五层模型)

**作为一个统一的接口管理网络**

+ **全局选项**
  + `-s` - 更多信息
  + `-d` - 更详细
  + `-4` - 仅IPv4
  + `-6`
  + `-o` - 单行

+ **link - 网络接口(链路层)**
  + `show` - 显示所有接口
  + `set <dev> up/down` - 开启或关闭接口
  + `set <dev> address <MAC>` - 设置MAC地址(down)

+ **addr - IP地址**
  + `ip a` - 显示所有接口地址
  + `add <IP> dev <devname>` - 添加IP地址
  + `del <IP> dev <devname>`
  + `flush dev <devname>` - 清空

+ **route - 路由表**
  + `ip r` - 显示所有路由表
  + `get <IP>` -获取指定IP的路由

+ **neigh - ARP/NDISC缓存**
  + `ip n`
  + `add [IP] lladdr [MAC] dev [eth0]` - 添加表项
  + `del [IP] dev [eth0]` - 删除表项
  + `flush all` - 清空

```
REACHABLE:表示邻居设备可达.
STALE:表示邻居设备的条目已过期,但之前是可达的.
DELAY:表示正在等待确认邻居设备是否可达.
PROBE:表示正在积极探测邻居设备是否可达
```

+ **rule - 策略路由规则**

+ **tunnel - IP隧道**

+ **maddress - 多播地址**

+ **monitor - 网络事件**
  + `all` - 所有事件


## ss

用于查看网络套接字统计信息

格式 : `ss [选项] [过滤器]`

|选项|功能|
|---|---|
|`-t`|tcp|
|`-u`|udp|
|`-n`|以端口号显示,不解析服务名,加快输出速度|
|`-l`|仅列出正在监听的服务|
|`-p`|显示关联的进程 pid|
|`-r`|解析主机名(默认行为),与`-n`相反|
|`-e`|拓展信息(inode,用户)|
|`-m`|显示套接字内存使用详情|
|`-s`|汇总统计:列出各类协议收发包,错误,连接数总计|
|`ss -tlunp`||

**输出列解读**

- `Recv-Q` 和 `Send-Q`
  - 对于 `LISTEN` 状态
    - `Recv-Q` : 当前全连接队列(已完成三次握手但未`accept()`)(注意是否大量堆积)
    - `Send-Q` : 最大连接队列长度(即backlog)
  - 对于非监听
    - `Recv-Q` : 内核接收缓冲区中,未被用户态程序拷走的数据字节数
    - `Send-Q` : 已发送但尚未被远端确认的数据字节数(TCP) 或发送缓冲区尚未发出的数据字节数(UDP)
- `ss -s` 快速汇总
  - `Total` 所有协议族的套接字总数
  - TCP行
    - `estab` : 已建立连接状态的数量(TCP总数远大于estab,或者estab暴增都可能是DDoS攻击)
    - `closed` : `CLOSED` 状态的套接字,通常少见
    - `orphaned` : **孤儿套接字** 进程将其关闭,但是内核保留一段时间
    - `timewait` : `TIME_WAIT` 状态,主动关闭一方等待2MSL(数量过大可能是短链接泛洪攻击)

## **curl**

curl用于 **传输数据**,支持多种协议(HTTP、HTTPS、FTP、FTPS、SCP、SFTP、TFTP、LDAP、DICT、TELNET等).广泛用于测试API、下载文件、上传数据等场景.


- `-X` 或 `--request`: 指定HTTP请求方法(GET, POST, PUT, DELETE等)
  ```bash
  curl -X POST https://example.com/api
  ```

- `-H` 或 `--header`: 添加请求头
  ```bash
  curl -H "Content-Type: application/json" https://example.com/api
  ```

- `-d` 或 `--data`: 发送POST请求的数据
  ```bash
  curl -d "name=John&age=30" https://example.com/api
  ```

- `--data-raw`: 发送原始数据(不处理特殊字符)
- `--data-binary`: 发送二进制数据
- `--data-urlencode`: URL编码发送的数据
  ```bash
  curl --data-urlencode "name=John Doe" https://example.com/api
  ```

- `-F` 或 `--form`: 发送multipart/form-data(文件上传)
  ```bash
  curl -F "file=@photo.jpg" https://example.com/upload
  ```

- `-i` 或 `--include`: 输出包含响应头
- `-I` 或 `--head`: 只获取响应头
- `-v` 或 `--verbose`: 显示详细操作信息
- `-s` 或 `--silent`: 静默模式(不显示进度或错误信息)
- `-o` 或 `--output`: 将输出写入文件
  ```bash
  curl -o output.html https://example.com
  ```

- `-O` 或 `--remote-name`: 使用远程文件名保存
  ```bash
  curl -O https://example.com/file.zip
  ```

- `-u` 或 `--user`: 用户名和密码认证
  ```bash
  curl -u username:password https://example.com
  ```

- `--basic`: 使用HTTP Basic认证
- `--digest`: 使用HTTP Digest认证
- `--negotiate`: 使用HTTP Negotiate认证

- `-x` 或 `--proxy`: 使用代理服务器
  ```bash
  curl -x http://proxy.example.com:8080 https://example.com
  ```

- `--connect-timeout`: 连接超时时间(秒)
- `-m` 或 `--max-time`: 最大请求时间(秒)
- `--retry`: 失败重试次数
- `--retry-delay`: 重试间隔时间(秒)


- `-k` 或 `--insecure`: 允许不安全的SSL连接
- `--cacert`: 指定CA证书文件
- `--cert`: 客户端证书文件
- `--key`: 私钥文件

- 发送JSON数据
```bash
curl -H "Content-Type: application/json" -d '{"name":"John","age":30}' https://example.com/api
```

- 从文件读取POST数据
```bash
curl -d @data.json https://example.com/api
```

- 使用cookie
```bash
curl -b "name=value" https://example.com  # 发送cookie
curl -c cookies.txt https://example.com  # 保存cookie到文件
curl -b cookies.txt https://example.com  # 从文件读取cookie
```

- 跟随重定向
```bash
curl -L https://example.com
```

- 限制下载速度
```bash
curl --limit-rate 100K -O https://example.com/largefile.zip
```

- 断点续传
```bash
curl -C - -O https://example.com/largefile.zip
```

- 同时下载多个文件
```bash
curl -O https://example.com/file1.zip -O https://example.com/file2.zip
```

- 使用通配符下载
```bash
curl -O https://example.com/files/[1-10].jpg
```

- 显示进度条
```bash
curl -# -O https://example.com/largefile.zip
```

---

## wget

## networkmanager
- 连接无线网络
  1. `nmcli device status`  检查网卡是否启用
  2. `nmcli device wifi on` 启用wifi射频
  3. `nmcli device wifi rescan` 刷新列表
  4. `nmcli device wifi list`  列出所有可用wifi
  5. `nmcli device wifi connect <SSID> password "password"
  6. `nmcli connection show`  验证连接

## systemctl
    +    start
    +    stop
    +    restart
    +    reload
    +    enable
    +    disable
    +    status
    +    mask        # 强制注销
    +    unmask
    +    list-units
    +    get-default        # 获取目前target
    +    set-default        # 设置默认target
    +    isolate            # 切换target
        +     poweroff
        +     reboot
        +     suspend        # 挂起
        +     hibernate    # 休眠
        +     rescue        # 修复

## dmidecode

|选项|功能|
|---|---|
|`-q`|简洁|
|`-t`|指定查看类型|

## dpkg

|选项|功能|
|---|---|
|`-i`|安装|
|`-l`|查看版本|
|`-r`|卸载|

## apt

|选项|功能|
|---|---|
|`updata`|从所有源下载软件包列表,不实际安装|
|`upgrade`|更新已有软件包的最新版本|
|`full-upgrade`|更彻底的升级,必要时删除冲突的包|
|`search`|搜索包名或描述中包含关键词的包|
|`show <包名>`|显示包的详细信息|
|`list --installed`|列出所有已安装的包,可配合grep检查某包是否已装|
|`rdepends <包名>`|列出哪些包依赖了这个包|
|`install <包名>/<./本地包.deb>`|下载并安装|
|`remove <包名>`|卸载,但保留配置文件|
|`purge <包名>`|啥都不留|
|`autoremove`|删除不再被需要的依赖包|
|`clean`|清空所有包缓存|
|`edit-source`|修改软件源文件|

**软件源配置文件** : `/etc/apt/sources.list`

**新版APT源配置格式** : 主要修改 `URIs` 行

```
Types: deb
URIs: https://mirrors.aliyun.com/ubuntu/
Suites: noble noble-updates noble-backports noble-security
Components: main restricted universe multiverse
Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg
```

**多个下载导致死锁问题** : 执行下面的命令强制删除锁

```
sudo rm /var/lib/apt/lists/lock
sudo rm /var/cache/apt/archives/lock
sudo rm /var/lib/dpkg/lock*
```

## 编解码工具
 +  md5sum   md5编码
 +  sha1sum  sha1
 +  cksum    crc
 +  base64
 +  basenc   各种base64变种
   +  `--base64url`
   +  `--base32`
   +  `--base16`
   +  `--base2msbf`  二进制
 +  `echo -n 你好|iconv -t ucs-2be|xxd-ps|sed 's/..../\\u&/g`  unicode码

---

## **bc**
`bc`支持高精度数学运算、变量、函数、条件语句等编程功能

- **基本用法**
  - **交互模式**:终端输入 `bc` 后回车
  - **非交互模式**:直接计算表达式
    ```bash
    echo "5 + 3" | bc
    ```

- **设置精度**
  - 通过内置变量 `scale` 控制小数位数
  ```bash
  echo "scale=3; 10/3" | bc  # 输出 3.333
  ```

- **进制转换**
  - **输入进制**:用 `ibase` 设置输入数字的进制.
  - **输出进制**:用 `obase` 设置输出结果的进制.
  - **调整输入进制一定要注意先后顺序**
  ```bash
  echo "ibase=2; 1101" | bc   # 二进制 1101 → 十进制 13
  echo "obase=16; 255" | bc   # 十进制 255 → 十六进制 FF
  ```

- **变量和函数**
```bash
a=5
b=a*2  # b=10
```
```bash
define square(x) {
  return x*x
}
square(4)  # 输出 16
```

- **数学库函数**
启动时添加 `-l` 参数启用数学库

- **支持的函数**
  - `s(x)`:正弦(弧度)
  - `c(x)`:余弦(弧度)
  - `a(x)`:反正切(结果弧度)
  - `l(x)`:自然对数
  - `e(x)`:指数函数(e^x)
  - `sqrt(x)`:平方根
  - `j(n, x)`:贝塞尔函数

- **example**
  - 计算Pi
  `echo "scale=1000; a=1; b=1/sqrt(2); t=1/4; p=1; for (i=0; i<10; i++) { a1=(a+b)/2; b1=sqrt(a*b); t1=t - p*(a - a1)^2; p1=2*p; a=a1; b=b1; t=t1; p=p1 }; (a+b)^2/(4*t)" | bc -l`
  `echo "scale=1000; 4*a(1)" | bc -l`

- **退出**
输入 `quit` 或按 `Ctrl+D` 退出交互模式.

---

## **timeshift**

系统级备份工具(配置文件在`/etc/timeshift/timesift.json`)

`sudo timeshift --list-devices` 查看可用备份设备(选择非系统盘进行备份)

**创建快照** 完全非交互

```
sudo timeshift --create \
  --snapshot-device /dev/sda2 \
  --rsync \
  --comments "手动备份：$(date +%Y-%m-%d_%H:%M)" \
  --tags O
```
- `snapshot-device` : 存放快照的分区设备名
- `rsync` : 强制使用rsync
- `comments "xxx"` : 快照描述
- `tags` : 标签,O(On demand)按需备份,D(每日),W(每周)
- 如果已经配置过默认位置可以直接`--create + --comments`

1. 列出快照 : `sudo timeshift --list`
2. 恢复快照 : `sudo timeshift --restore --snapshot "2026-05-30-18-22-00" --yes`
3. 删除旧快照 : `sudo timeshift --delete --snapshot "2026-05-31-xxx"`

### timeshift.json 配置文件

位置: `/etc/timeshift/timeshift.json`

**基于RSYNC模式的重点选项讲解**

|配置项|含义|
|---|---|
|`backup_device_uuid`|存放快照的分区UUID|
|`btrfs_mode`|选择false为RSYNC模式|
|`exclude`|排除目录(`/`代表根目录开始,`**`匹配任意多级子目录)|

---

**系统恢复步骤**

1. 挂载原系统根目录与重要分区到`/mnt`

2. 挂载timeshift存储位置(如果在独立分区)
```
mkdir /mnt/timeshift
mount /dev/sda1 /mnt/timeshift  # 挂载快照分区到临时目录
```

3. chroot到原系统

4. 执行恢复

`timeshift --restore --snapshot '2024-05-20_12-00-00' --target /  --yes`

- `--snapshot` 指定快照名称
- `--target /` 恢复到根分区
- `--yes` 跳过确认

5. 修复引导
```bash
# 针对 Arch Linux
mkinitcpio -P
grub-install /dev/nvme0n1    # 安装 GRUB 到磁盘(非分区)
grub-mkconfig -o /boot/grub/grub.cfg
```

6. 退出重启
```bash
exit      # 退出 chroot
umount -R /mnt  # 卸载所有分区
reboot
```

## **iperf**

- 通用参数
  - `-p` : 指定端口
  - `-i` : 报告间隔时间(s)
  - `-V` : 详细日志

- 客户端参数
  - `-c` : 指定服务端IP
  - `-u` : UDP
  - `-R` : 反向传输(服务器发,客户端收)
  - `-P` : 并发连接数
  - `-b` : UDP目标带宽

- 服务端参数
  - `-s` : 启动服务器
  - `-B` : 绑定指定IP

## **tee**

接收来自前一个命令通过管道送来的输出,输出到stdout和多个文件中

+ `-a` - 将数据追加到文件末尾

**特性:可处理`>`符号无法做到的权限问题**

## **acl**

允许你为单个用户或组以及不在文件所属组中的用户或组设置更精细的访问权限

- **核心概念**
  - 一个 ACL 由一系列条目组成,每个条目定义了一个用户或组对该文件的访问权限
    - 用户条目:`u:user:permission`
    - 组条目:`g:groupname:permission`
    - 掩码条目:`mask`

- `setfacl [选项] 规则 文件/目录`
  - 选项
    - `-m`:修改
    - `-x`:删除
    - `-b`:删除所有
    - `-d`:应用于默认ACL
    - `-R`
  - 规则
    - `[d:] [u/g/o:]用户名或组名:[权限]

- `getfacl [选项] 文件/目录`
  - 选项
    - `-d`:仅显示默认
    - `-e`:考虑掩码之后

---

## **attr**

控制文件本身的行为特性

- 属性
  - `a`(Append Only):只允许追加
  - `i`(Immutable):完全不可变,只读
  - `A`(No Atime Updates):不更新访问时间(Atime)

- `chattr [选项] [+/-/=][属性] [FileName]`
  - `-R`
  - `-V`:详细输出

- `lsattr [选项] [files...]`
  - `-R`
  - `-V`:详细输出
  - `-a`:所有文件(包含隐藏)

## tail

用于显示文件的末尾内容,它默认显示文件的最后 10 行,但可以通过选项进行高度自定义

- **常用功能说明**

1. **显示指定行**
  ```
  # 显示最后五行
  tail -5 filename.txt

  # 从20行到末尾
  tail -n +20 filename.txt
  ```

2. **实时监控文件变化**
  ```
  tail -F filname.log
  ```

3. **显示文件名**
  ```
  # 总是显示文件名标题
  tail -v filename.txt
  ```

## ufw

Ubuntu默认的防火墙配置工具,简化了iptables的配置过程

- **基础命令**
  - `status verbose` : 列出详细规则
  - `enable` : 启动UFW
  - `disable` : 彻底关闭UFW
  - `reset` : 完全重置,删除所有规则
  - `allow 22/tcp` : 允许22端口连接
    - `allow from 192.168.0.0/24` : 允许特定IP
    - `allow from 192.168.0.0/24 to any port 22` : 允许特定IP
  - `deny 21/tcp` : 拒绝端口访问
    - `deny log 23/tcp` : 拒绝并记录日志(通常在`/var/log/ufw.log`)
  - `delete allow 8080/tcp` : 删除规则(`delete`后接原始规则)
  - `default deny incoming` : 默认拒绝所有传入(outcoming为传出)
  - `logging on` : 启用日志

## lsblk

- 命令格式 `lsblk [选项] [设备]`

- [硬盘相关](./hardware/disk.md)

- **常用选项**
  - `-a` 显示所有设备
  - `-d` 不显示从属设备(只有硬盘无分区)
  - `-f` 显示文件系统信息(类型,标签,UUID,挂载点)
  - `-p` 完整路径
  - `-t` 显示拓扑信息(RAID,多路径)
  - `-o` 指定输出列(输出列参数如下)
    - `NAME` 设备名称
    - `SIZE` 设备大小
    - `TYPE` 设备类型
    - `MOUNTPOINT` 挂载点
    - `FSTYPE` 文件系统类型
    - `UUID`
    - `MODEL` 硬盘型号
    - `SERIAL` 序列号
    - `TRAN` 传输类型(sata,usb,nvme)
    - `WWN` 全球唯一网络名
    - `ROTA` 0-SSD 1-HDD

- **示例**
  - `lsblk -o NAME,SIZE,MODEL,SERIAL,MOUNTPOINT`

## pacman

+  `-S` 同步
+  `-y` 更新软件包数据库
+  `-u` 升级已有安装包
+  `-R` 卸载
+  `-Q` 查看已安装
- 示例
  +  `pacman -Sy` 同步数据库
  +  `pacman -Syu` 更新系统
  +  `pacman -S <package_name>` 安装软件包
  +  `pacman -Rs <package_name>` 卸载同时删除无用的依赖
  +  `pacman -Ss <keyword>` 搜索软件包
  +  `sudo pacman -Sc` 清除缓存

**pacman签名问题**

1. `sudo rm -rf /etc/pacman.d/gnupg` 清除旧配置
2. `/etc/pacman.conf` 去除 `multlib` 注释
3. 重建签名
   - `sudo pacman-key --init`
   - `sudo pacman-key --populate archlinux` 或 `sudo pacman -Sy archlinux-keyring`
   - `sudo pacman -Sy archlinuxcn-keyring`

## xargs

|选项|功能|
|---|---|
|`-P N`|设置最大并发数|
|`-I {}`|定义替换字符串|
|`-n M`|每次传递M个参数给命令|

- 示例
  - `cat urls.txt | xargs -P 8 -n 1 wget -q` : 多线程下载文件列表

## vnstat

超低性能占用的网络历史流量记录工具

**安装后初始化**

1. `sudo systemctl enable --now vnstat` 启动开机自启
2. `ip link show` 查看网卡名
3. `sudo vnstat -i eth0 --create` 未网卡创建数据库

|选项|功能|
|---|---|
|`-h`|每小时流量|
|`-d`|每日流量|
|`-m`|每月流量|
|`-t`|流量最高的十天|
|`-i eth0`|指定查看某网卡|
