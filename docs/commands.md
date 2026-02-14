# 命令大全(以linux平台为主,Win会进行特殊标注


## 目录




- [文件操作](#文件操作)
- [打包压缩](#打包压缩)
- [权限管理](#权限管理)
- [磁盘](#磁盘)
- [用户](#用户)
- [进程](#进程)
- [网络](#网络)
- [系统](#系统)
- [开发](#开发)
- [其他](#其他)


## 文件操作

- [cd]() : 切换工作目录
- [ls](#ls) : 查看当前工作目录下的文件
- [cat](#cat) : 输出文件内容
- [od](#od) : 查看二进制文件内容
- [grep](#grep) : 查找指定内容
- [file](#file)
- [wc](#wc) : 统计文件信息
- [ln](#ln)
- [diff](#diff):文件差异对比
- [patch](#patch)
- [rsync](#rsync):同步命令
- [find](#find)
- [locate](#locate):高效文件查找
- [whereis](#whereis)
- [tee](#tee):数据分流
- [tail](#tail):显示文件的末尾内容
- [vim](./vim.md) : 文件内容编辑工具


## 打包压缩

- [gzip](#gzip)
- [bzip2](#bzip2)
- [xz](#xz)
- [tar](#tar)
- [dd](#dd)


## 权限管理

- [chown](#chown)
- [chmod](#chmod)
- [umark](#umark)
- [acl](#acl):访问控制列表
- [attr](#attr):底层文件属性控制

---

## 磁盘

- [iostat](#iostat) : 监测磁盘活动
- [mount](#mount)
- [umount](#umount)
- [df](#df)
- [du](#du):分析文件占用大小
- [sync](#sync)
- [smartctl](#smartctl):查看smart参数
- [parted](#parted)

---

##  用户

- [sudo](#sudo)
- [useradd](#useradd)
- [groupadd](#groupadd)
- [passwd](#passwd)
- [userdel](#userdel)
- [usermod](#usermod)
- [id](#id):身份信息
- [newgrp](#newgrp):切换有效用户组
- [last](#last) : 查看用户登陆记录
- [which](#which):查找命令
- [whoami](#whoami)

---

## 进程

- [ps](#ps)
- [uptime](#uptime)
- [vmstat](#vmstat)
- [top](#top)
- [btop](#btop)
- [lsop](#lsop):查看占用文件的进程
- [kill](#kill)
- [bg](#bg) : 暂停的jobs 放到后台运行
- [fg](#fg) : 后台拉回前台
- [jobs](#jobs)
- [ulimit](#ulimit)

---

## 网络

- [ip](#ip) : many net tool
- [ss](#ss) : 端口
- [ping](#ping)
- [curl](#curl)
- [wget](#wget)
- [NetworkManager](#networkmanager)
- [nmap](#nmap)
- [iperf3](#iperf) : 网络性能测试工具
- [ufw](#ufw) : 防火墙配置工具

---

## 系统

- [systemctl](#systemctl)
- [perf](../../program/tool/perf.md)
- [dmidecode](#dmidecode)
- [dpkg](#dpkg)
- [apt](#apt)
- [timeshift](#timeshift) : 备份工具
- [uname](#uname):系统内核版本等信息

---

## 开发

- [objdump](../program/tool/objdump.md) : 可自行文件反汇编
- [readelf](../program/tool/readelf.md) : 观察elf文件结构

---

## 其他

- [编解码工具](#编解码工具)
- [高精度计算器](#bc)


### ls

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

### cat

`-n` 显示行号

### od

- `-t [<o/x>]` 使用不同进制显示

### grep

|选项|功能|
|---|---|
|`-A <n>`|后续n行|
|`-B <n>`|前n行|
|`-n`|显示行号|
|`-v`|反向选择|
|`-E 'o1|o2|o3'|多匹配|

### wc
    +    -l    行数
    +    -m    字符
    +    -w    word

###    mv
    +    -i            # 覆盖时警告
    +    -b            # 重合加~

### cp    
	+	 -a            # 归档模式
	+    -p            # 保留文件的原始属性
    +    -i            # 覆盖时警告
    +    -b            # 重合加~
    +    -u            # 仅复制更新
    +    -v            # 详细显示
    +    -r            # 目录

### rm
    +    -i            # 覆盖时警告
    +    -r            # 目录
    +    -f            # 强制


    +    -R            # 同时更改所有子目录

### chmod
    +    -R            # 同时更改所有子目录
```bash
    SUID    4
        执行二进制文件时,权限提升为文件所有者
        
    SGID    2
        在此权限下的目录进入后,有效用户组变为所有组

    SBIT    1
        在此权限下的文件夹里创建文件,仅有root与属主有权操作
```

### file
    +    -i        查看编码格式
    +    -z        查看压缩格式
    +    -b        查看文件的系统架构
    +    -p        详细信息

### umark

### ln
    +    -s            # 符号链接(软)

### diff
    +    -r            # 递归比较两个目录
    +    -b            # 忽略空格
    +    -i            # 忽略大小写
    +    -B            # 忽略空白行
    +    -w            # 忽略空白字符
    +    -u            # 使用"统一格式”显示,易于生成补丁文件

### patch
```bash
    diff -Naur <oldfile> <newfile>  >  <file.patch###     # -p[n] 拿掉路径中的/
    patch -p<n> <  <file.patch###         # 制作
    patch -p<n>-R <  <file.patch###     # 还原
```

### rsync
    +    -a(archive):归档模式,用于完整同步
    +    -v(verbose):详细模式,显示同步过程中的详细信息.
    +    -u(update):仅在目标文件不存在或源文件更新时才同步.
    +    -z(compress):在传输过程中压缩文件数据.
    +    --delete:删除目标目录中多余的文件,使目标目录与源目录保持一致
    +    -e(rsh):指定远程连接时使用的工具(如 ssh).
    +    --exclude:指定排除的文件或目录模式.
    +    --include:指定包含的文件或目录模式.
    +    -P --progress:显示同步进度.
    +    --bwlimit : 限速,用于单个大文件,避免占用过多带宽
    +    --dry-run:模拟同步操作,不实际执行,用于测试同步命令的效果.
    1.    本地同步
        `rsync -avP /path/to/source/ /path/to/destination/`
    2.    从本地同步到远程
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

### find
    +    -name [filename]    # 指定文件名
    +    -print                # 打印结果在终端
    +    -type [type]        # 指定类型
    +    -atime <+-n###     # n天前使用的文件
    +    -mtime <+-n###     # n天前修改的文件
    +    find /usr/bin -name zip -print

### locate

### whereis

### which
    +    -a        # 全部列出
### whoami

### uname
    +    -a    全部信息


### gzip
    +    -d            # 解压
    +    -l            # 查看压缩效果

### bzip2
    +    -d            # 解压
    +    -l            # 查看压缩效果

### xz
    +    -z            # 压缩
    +    -d            # 解压
    +    -l            # 查看压缩效果
    +    -k            # 保留压缩原文件
    +    -<number>     # 压缩等级
    +    -T <n>        # 使用多个线程
    +    -v            # 显示详细过程

### tar 
    +    -c            # 创建
    +    -x            # 解开
    +    -v            # 显示详细过程
    +    -f <file>     # 指定文件名
    +    -z            # 调用gzip
    +    -j            # 调用bzip2
    +    -J            # 调用xz
	+	 -p            # 保留权限和所有
    +    tar -cvjf shell.tar.bz2 shell/

### dd
    +    if        # input file/device
    +    of        # output file/device
    +    bs        # one black size
    +    count     # count
	+    `oflag=sync`  sync
    

### mount
    +    -r            # 只读
    +    -o <loop>     # 特殊设备
    +    auto          # 开机自动挂载
    +    noauto        # 不自动挂载
    +    ro            # read only
    +    rw            # read and write
    +    user          # 任意用户可挂载

- `/etc/fstab` 文件
- `[设备/UUID] [挂载点] [文件系统] [参数] 0 0`


### df
    +    df -hT

###  smartctl
        -a    全部参数
        -H    是否正常

### parted
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


### sudo    
    +    -u        # 指定用户

### useradd
    +    -m        # 同时建立主目录
    +    -g        # 指定用户组
    +    -s        # 指定shell

### userdel
    +    -r        # 删除主目录

### usermod
    +    -d            # 修改主目录
    +    -e <MM/DD/YY># 修改账号有效期
    +    -s            # 修改shell

### id

- `/etc/passwd`
- `登录名:口令:UID:GID:x信息:主目录:shell`

`/etc/group`
    +    组名:组口令(一般无):GID:user1,user2,user3

__用户所有组是passwd和groups的并集__

### newgrp

### last
- **-n <数字>**  表示查看最近n条
- **-i**  显示IP而不是主机名

### ps
    +    aux

### uptime
`load average` 为过去 1, 5, 15 分钟内等待资源的进程数量
若持续高于cpu核心数,表明进程可能在争抢资源

### vmstat
检测系统状态
+ **`r`**      cpu队列  
+ **`b`**      io等待  
+ **`si/so`**  swap队列  

- `-f`  自启动fork次数
- `-d`  磁盘统计信息
- `-s`  统计

### top

### btop

### lsop    

### kill
    +    -l            # 列出所有信号

### bg

### fg

### jobs

### nohup    命令挂机(退出登陆后依然执行)
nohup [command] &
`screen` 主要用于用户开启多个独立的会话(称为"窗口")在这些会话之间可以自由切换而不会中断已经运行的程序
1. **启动一个新的 screen 会话**:
   screen
2. **列出当前的 screen 会话**:
   screen -ls
3. **重新连接到一个已存在的会话**:
   screen -r [会话ID或名称]
4. **分离当前会话**:
   在 screen 会话中按 `Ctrl-a` 然后按 `d`.
9. **退出 screen 会话**:
   - 关闭当前窗口:在 screen 会话中按 `Ctrl-a` 然后按 `k`.
   - 退出所有窗口并结束会话:在 screen 会话中按 `Ctrl-a` 然后按 `\`.
10. **锁定当前会话**:
    在 screen 会话中按 `Ctrl-a` 然后按 `x`.

### ulimit
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

---

### ip
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
  
+ **address - IP地址**
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


### ss
    +    -t        # tcp
    +    -u        # udp
    +    -n        # 以端口号显示
    +    -l        # 列出正在监听的服务
    +    -p        # + pid
    +`    -r        # 路由表
    +    ss -tlunp

### ping

---

### **curl**

curl是一个强大的命令行工具,用于传输数据,支持多种协议(HTTP、HTTPS、FTP、FTPS、SCP、SFTP、TFTP、LDAP、DICT、TELNET等).它被广泛用于测试API、下载文件、上传数据等场景.


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

### wget

### networkmanager
- 连接无线网络
  1. `nmcli device status`  检查网卡是否启用
  2. `nmcli device wifi on` 启用wifi射频
  3. `nmcli device wifi rescan` 刷新列表
  4. `nmcli device wifi list`  列出所有可用wifi
  5. `nmcli device wifi connect <SSID> password "password"
  6. `nmcli connection show`  验证连接

### systemctl
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

### dmidecode
    +    -q        # 简洁
    +    -t        # 指定查看类型

### dpkg
    +    -i        # 安装
    +    -l        # 查看版本
    +    -r        # 卸载

### apt
        +    updata        # 更新软件包缓存
        +    upgrade        # 更新已有软件包的最新版本
        +    install        # 下载并安装
        +    remove        # 卸载
        +    source        # 下载源码
        +    search        # 搜索
        +    depends        # 列出依赖
    +    /etc/apt/sources.list

### 编解码工具
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

### **bc**
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

### **timeshift**
- 系统恢复步骤

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

---

### **iperf**

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

---

### **tee**

接收来自前一个命令通过管道送来的输出,输出到stdout和多个文件中

+ `-a` - 将数据追加到文件末尾

**特性:可处理`>`符号无法做到的权限问题**

---

### **acl**

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

### **attr**

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

---

### tail

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

---

### ufw

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

---
