# linux基础命令

## 目录
- [文件操作](#)
  - [cd](#)
  - [ls](#)
  - [cat](#)
  - [less](#)
  - [od](#):查看二进制文件
  - [grep](#)
  - [wc](#)
  - [mkdir](#)
  - [touch](#)
  - [mv](#)
  - [cp](#)
  - [rm](#)
  - [chown](#)
  - [chmod](#)
  - [file](#)
  - [umark](#)
  - [ln](#)
  - [diff](#)
  - [patch](#)
  - [rsync](#):同步命令
  - [find](#)
  - [locate](#):高效文件查找
  - [whereis](#)
  - [which](#):查找命令
  - [whoami](#)
  - [uname](#):系统内核版本等信息
- [文件压缩](#)
  - [gzip](#)
  - [bzip2](#)
  - [xz](#)
  - [tar](#)
  - [dd](#)
- [磁盘](#)
  - [iostat](#iostat) : 监测磁盘活动
  - [mount](#)
  - [umount](#)
  - [df](#)
  - [sync](#)
  - [smartctl](#):查看smart参数
  - [parted](#)
- [用户](#)
  - [sudo](#)
  - [useradd](#)
  - [groupadd](#)
  - [passwd](#)
  - [userdel](#)
  - [usermod](#)
  - [id](#)
  - [newgrp](#):切换有效用户组
  - [last](# last) : 查看用户登陆记录
- [进程](#)
  - [ps](#)
  - [uptime](#uptime)
  - [vmstat](#vmstat)
  - [top](#)
  - [btop](#)
  - [lsop](#):查看占用文件的进程
  - [kill](#)
  - [bg](#) : 暂停的jobs 放到后台运行
  - [fg](#) : 后台拉回前台
  - [jobs](#)
  - [ulimit](#)
- [网络](#)
  - [ip](#) : many net tool
  - [ss](#) : 端口
  - [ping](#)
  - [curl](#)
  - [wget](#)
  - [NetworkManager](# networkmanager)
- [系统](#)
  - [systemctl](#)
  - [dmidecode](#)
  - [dpkg](#)
  - [apt](#)
  - [编解码工具](#)
- [其他](#)
  - [](#)


## 文件操作
### pwd

###    cd

###    ls
    +    -F                # 在文件名后加提示符 '/' '*' '@'
    +    -a                # 显示隐藏文件
    +    -l                # 列出文件信息
    +    -d                # 目录
    +    -h                # 将文件大小输出为易读的格式
    +    -s                # 在行首显示(大小)?
    +    -i                # inode

###    cat
    +    -n                # 显示行号

###    less

###    od
    +    -t             # 类型 a, d, f, o, x

###    grep
    +    -A <n>          # 后续n行
    +    -B <n>          # 前n行
    +    -n              # 显示行号
    +    -v              # 反向选择
    +    -E 'o1|o2|o3'   # 多匹配
    +    -r "指定字符串" /目标文件夹路径  # 结合递归选项来查找文件夹下包含指定字符串的文件

### wc
    +    -l    行数
    +    -m    字符
    +    -w    word

### mkdir

### touch

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
        执行二进制文件时，权限提升为文件所有者
        
    SGID    2
        在此权限下的目录进入后，有效用户组变为所有组

    SBIT    1
        在此权限下的文件夹里创建文件，仅有root与属主有权操作
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
    +    -a（archive）：归档模式,用于完整同步
    +    -v（verbose）：详细模式，显示同步过程中的详细信息。
    +    -u（update）：仅在目标文件不存在或源文件更新时才同步。
    +    -z（compress）：在传输过程中压缩文件数据。
    +    --delete：删除目标目录中多余的文件，使目标目录与源目录保持一致
    +    -e（rsh）：指定远程连接时使用的工具（如 ssh）。
    +    --exclude：指定排除的文件或目录模式。
    +    --include：指定包含的文件或目录模式。
    +    -P --progress：显示同步进度。
    +    --bwlimit : 限速，用于单个大文件，避免占用过多带宽
    +    --dry-run：模拟同步操作，不实际执行，用于测试同步命令的效果。
    1.    本地同步
        `rsync -avP /path/to/source/ /path/to/destination/`
    2.    从本地同步到远程
        `rsync -avzP /path/to/source/ user@remote_host:/path/to/destination/`
    3.  同步时删除多余文件
        `rsync -av --delete /path/to/source/ /path/to/destination/`
    4.  排除某些文件或目录
        `rsync -av --exclude 'temp/*' --exclude '*.log' /path/to/source/ /path/to/destination/`
        --exclude 'temp/*'：排除 temp 目录下的所有文件。
        --exclude '*.log'：排除所有 .log 文件。
    5.  包含某些文件或目录
        `rsync -av --include 'data/*' --exclude '*' /path/to/source/ /path/to/destination/`
        --include 'data/*'：仅包含 data 目录下的文件。
        --exclude '*'：排除其他所有文件。
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


## 文件压缩
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
    

## 磁盘
### mount
    +    -r            # 只读
    +    -o <loop>     # 特殊设备
    +    auto          # 开机自动挂载
    +    noauto        # 不自动挂载
    +    ro            # read only
    +    rw            # read and write
    +    user          # 任意用户可挂载

__/etc/fstab__
[设备/UUID]        [挂载点]    [文件系统]    [参数] 0 0

### umount

### df
    +    df -hT

### sync

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


##  用户
### sudo    
    +    -u        # 指定用户

### useradd
    +    -m        # 同时建立主目录
    +    -g        # 指定用户组
    +    -s        # 指定shell

### groupadd

### passwd

### userdel
    +    -r        # 删除主目录

### usermod
    +    -d            # 修改主目录
    +    -e <MM/DD/YY># 修改账号有效期
    +    -s            # 修改shell

### id

`/etc/passwd`
登录名:口令:UID:GID:x信息:主目录:shell

`/etc/group`
    +    组名:组口令(一般无):GID:user1,user2,user3

__用户所有组是passwd和groups的并集__

### newgrp

### last
- **-n <数字>**  表示查看最近n条
- **-i**  显示IP而不是主机名

## 进程
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
1. **启动一个新的 screen 会话**：
   screen
2. **列出当前的 screen 会话**：
   screen -ls
3. **重新连接到一个已存在的会话**：
   screen -r [会话ID或名称]
4. **分离当前会话**：
   在 screen 会话中按 `Ctrl-a` 然后按 `d`。
9. **退出 screen 会话**：
   - 关闭当前窗口：在 screen 会话中按 `Ctrl-a` 然后按 `k`。
   - 退出所有窗口并结束会话：在 screen 会话中按 `Ctrl-a` 然后按 `\`。
10. **锁定当前会话**：
    在 screen 会话中按 `Ctrl-a` 然后按 `x`。

### ulimit
        查看和修改进程运行资源限制    
        -H/S        # 设置/显示 软/硬 限制
        -a            # 显示所有
        -t            # cpu time
        -f            # file size
        -s            # stack size
        -c            # core file size
        -m            # memory size
        -l            # lock memory size
    -p            # user processes
    -n             # open file

    #ulimit -Ht 3600


## 网络
### ip
    +    ip neigh [OPTIONS] [COMMAND]
    +    ip neigh add [IP] lladdr [MAC] dev [eth0]         添加表项
    +    ip neigh del [IP] dev [eth0]                     删除表项
    +    ip neigh flush all                                清空
    _________________________________
    REACHABLE：表示邻居设备可达。
    STALE：表示邻居设备的条目已过期，但之前是可达的。
    DELAY：表示正在等待确认邻居设备是否可达。
    PROBE：表示正在积极探测邻居设备是否可达
    _________________________________

### ss
    +    -t        # tcp
    +    -u        # udp
    +    -n        # 以端口号显示
    +    -l        # 列出正在监听的服务
    +    -p        # + pid
    +`    -r        # 路由表
    +    ss -tlunp

### ping

### curl

### wget

### networkmanager
- 连接无线网络
  1. `nmcli device status`  检查网卡是否启用
  2. `nmcli device wifi on` 启用wifi射频
  3. `nmcli device wifi rescan` 刷新列表
  4. `nmcli device wifi list`  列出所有可用wifi
  5. `nmcli device wifi connect <SSID> password "password"
  6. `nmcli connection show`  验证连接

## 系统
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

## 其他
=======
# linux基础命令

## 目录
- [linux基础命令](#linux基础命令)
  - [目录](#目录)
  - [文件操作](#文件操作)
    - [pwd](#pwd)
    - [cd](#cd)
    - [ls](#ls)
    - [cat](#cat)
    - [less](#less)
    - [od](#od)
    - [grep](#grep)
    - [wc](#wc)
    - [mkdir](#mkdir)
    - [touch](#touch)
    - [mv](#mv)
    - [cp](#cp)
    - [rm](#rm)
    - [chmod](#chmod)
    - [file](#file)
    - [umark](#umark)
    - [ln](#ln)
    - [diff](#diff)
    - [patch](#patch)
    - [rsync](#rsync)
    - [find](#find)
    - [locate](#locate)
    - [whereis](#whereis)
    - [which](#which)
    - [whoami](#whoami)
    - [uname](#uname)
  - [文件压缩](#文件压缩)
    - [gzip](#gzip)
    - [bzip2](#bzip2)
    - [xz](#xz)
    - [tar](#tar)
    - [dd](#dd)
  - [磁盘](#磁盘)
    - [mount](#mount)
    - [umount](#umount)
    - [df](#df)
    - [sync](#sync)
    - [smartctl](#smartctl)
    - [parted](#parted)
  - [用户](#用户)
    - [sudo](#sudo)
    - [useradd](#useradd)
    - [groupadd](#groupadd)
    - [passwd](#passwd)
    - [userdel](#userdel)
    - [usermod](#usermod)
    - [id](#id)
    - [newgrp](#newgrp)
  - [进程](#进程)
    - [ps](#ps)
    - [top](#top)
    - [btop](#btop)
    - [lsop](#lsop)
    - [kill](#kill)
    - [bg](#bg)
    - [fg](#fg)
    - [jobs](#jobs)
    - [nohup](#nohup)
    - [ulimit](#ulimit)
  - [网络](#网络)
    - [ip](#ip)
    - [ss](#ss)
    - [ping](#ping)
    - [curl](#curl)
    - [wget](#wget)
  - [系统](#系统)
    - [systemctl](#systemctl)
    - [dmidecode](#dmidecode)
    - [dpkg](#dpkg)
    - [apt](#apt)
    - [编解码工具](#编解码工具)
  - [其他](#其他)


## 文件操作
### pwd

### cd

### ls
    +    -F                # 在文件名后加提示符 '/' '*' '@'
    +    -a                # 显示隐藏文件
    +    -l                # 列出文件信息
    +    -d                # 目录
    +    -h                # 将文件大小输出为易读的格式
    +    -s                # 在行首显示(大小)?
    +    -i                # inode

### cat
    +    -n                # 显示行号

### less

###    od
    +    -t             # 类型 a, d, f, o, x

###    grep
    +    -A <n>          # 后续n行
    +    -B <n>          # 前n行
    +    -n              # 显示行号
    +    -v              # 反向选择
    +    -E 'o1|o2|o3'   # 多匹配
    +    -r "指定字符串" /目标文件夹路径  # 结合递归选项来查找文件夹下包含指定字符串的文件

### wc
    +    -l    行数
    +    -m    字符
    +    -w    word

### mkdir

### touch

###    mv
    +    -i            # 覆盖时警告
    +    -b            # 重合加~

### cp    
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
        执行二进制文件时，权限提升为文件所有者
        
    SGID    2
        在此权限下的目录进入后，有效用户组变为所有组

    SBIT    1
        在此权限下的文件夹里创建文件，仅有root与属主有权操作
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
    +    -a（archive）：归档模式,用于完整同步
    +    -v（verbose）：详细模式，显示同步过程中的详细信息。
    +    -u（update）：仅在目标文件不存在或源文件更新时才同步。
    +    -z（compress）：在传输过程中压缩文件数据。
    +    --delete：删除目标目录中多余的文件，使目标目录与源目录保持一致
    +    -e（rsh）：指定远程连接时使用的工具（如 ssh）。
    +    --exclude：指定排除的文件或目录模式。
    +    --include：指定包含的文件或目录模式。
    +    -P --progress：显示同步进度。
    +    --bwlimit : 限速，用于单个大文件，避免占用过多带宽
    +    --dry-run：模拟同步操作，不实际执行，用于测试同步命令的效果。
    1.    本地同步
        `rsync -avP /path/to/source/ /path/to/destination/`
    2.    从本地同步到远程
        `rsync -avzP /path/to/source/ user@remote_host:/path/to/destination/`
    3.  同步时删除多余文件
        `rsync -av --delete /path/to/source/ /path/to/destination/`
    4.  排除某些文件或目录
        `rsync -av --exclude 'temp/*' --exclude '*.log' /path/to/source/ /path/to/destination/`
        --exclude 'temp/*'：排除 temp 目录下的所有文件。
        --exclude '*.log'：排除所有 .log 文件。
    5.  包含某些文件或目录
        `rsync -av --include 'data/*' --exclude '*' /path/to/source/ /path/to/destination/`
        --include 'data/*'：仅包含 data 目录下的文件。
        --exclude '*'：排除其他所有文件。
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


## 文件压缩
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
    +    tar -cvjf shell.tar.bz2 shell/

### dd
    +    if        # input file/device
    +    of        # output file/device
    +    bs        # one black size
    +    count     # count
	+    `oflag=sync`  sync
    

## 磁盘
### mount
    +    -r            # 只读
    +    -o <loop>     # 特殊设备
    +    auto          # 开机自动挂载
    +    noauto        # 不自动挂载
    +    ro            # read only
    +    rw            # read and write
    +    user          # 任意用户可挂载

__/etc/fstab__
[设备/UUID]        [挂载点]    [文件系统]    [参数] 0 0

### umount

### df
    +    df -hT

### sync

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


##  用户
### sudo    
    +    -u        # 指定用户

### useradd
    +    -m        # 同时建立主目录
    +    -g        # 指定用户组
    +    -s        # 指定shell

### groupadd

### passwd

### userdel
    +    -r        # 删除主目录

### usermod
    +    -d            # 修改主目录
    +    -e <MM/DD/YY># 修改账号有效期
    +    -s            # 修改shell

### id

`/etc/passwd`
登录名:口令:UID:GID:x信息:主目录:shell

`/etc/group`
    +    组名:组口令(一般无):GID:user1,user2,user3

__用户所有组是passwd和groups的并集__

### newgrp


## 进程
### ps
    +    aux

### top

### btop

### lsop    

### kill
    +    -l            # 列出所有信号

### bg

### fg

### jobs

### nohup
nohup [command] &
`screen` 主要用于用户开启多个独立的会话(称为"窗口")在这些会话之间可以自由切换而不会中断已经运行的程序
1. **启动一个新的 screen 会话**：
   screen
2. **列出当前的 screen 会话**：
   screen -ls
3. **重新连接到一个已存在的会话**：
   screen -r [会话ID或名称]
4. **分离当前会话**：
   在 screen 会话中按 `Ctrl-a` 然后按 `d`。
9. **退出 screen 会话**：
   - 关闭当前窗口：在 screen 会话中按 `Ctrl-a` 然后按 `k`。
   - 退出所有窗口并结束会话：在 screen 会话中按 `Ctrl-a` 然后按 `\`。
10. **锁定当前会话**：
    在 screen 会话中按 `Ctrl-a` 然后按 `x`。

### ulimit
        查看和修改进程运行资源限制    
        -H/S        # 设置/显示 软/硬 限制
        -a            # 显示所有
        -t            # cpu time
        -f            # file size
        -s            # stack size
        -c            # core file size
        -m            # memory size
        -l            # lock memory size
    -p            # user processes
    -n             # open file

    #ulimit -Ht 3600


## 网络
### ip
    +    ip neigh [OPTIONS] [COMMAND]
    +    ip neigh add [IP] lladdr [MAC] dev [eth0]         添加表项
    +    ip neigh del [IP] dev [eth0]                     删除表项
    +    ip neigh flush all                                清空
    _________________________________
    REACHABLE：表示邻居设备可达。
    STALE：表示邻居设备的条目已过期，但之前是可达的。
    DELAY：表示正在等待确认邻居设备是否可达。
    PROBE：表示正在积极探测邻居设备是否可达
    _________________________________

### ss
    +    -t        # tcp
    +    -u        # udp
    +    -n        # 以端口号显示
    +    -l        # 列出正在监听的服务
    +    -p        # + pid
    +`    -r        # 路由表
    +    ss -tlunp

### ping

### curl
用于从服务器传输数据或向服务器传输数据，支持多种协议，包括 HTTP、HTTPS、FTP、FTPS、SMTP、POP3 等

1. 基本用法
+ `curl http://example.com`  访问网页或API
+ `curl -o output.html http://example.com`  保存响应到文件
+ `curl -v http://example.com`  显示详细信息
+ `curl -s http://example.com`  静默模式
+ `curl -X POST -d "param1=value1&param2=value2" http://example.com/api`  发送POST请求
+ `curl -X POST -H "Content-Type: application/json" -d '{"key":"value"}' http://example.com/api`  发送JSON数据
+ `curl -X POST -F "file=@/path/to/file" http://example.com/upload`  上传文件

### wget
`wget [参数] [URL]`一个下载文件的工具,可以使用HTTP代理,所谓的自动下载是指，wget可以在用户退出系统的之后在后台执行。这意味这你可以登录系统，启动一个wget下载任务，然后退出系统，wget将在后台执行直到任务完成

1．特点
+ 支持断点下传功能
+ 同时支持FTP和HTTP下载方式
+ 支持代理服务器
+ 设置方便简单
+ 程序小，完全免费

2. 参数
> `-V`  
> `-b`  启动后转后台  
> `-O [FILE]`  写入文件  
> `-d`  debug信息  
> `-c`  continue继续下  
> `-T`  设定响应超时的秒数  
> `-r`  递归下载  

__example__
+ `wget http://www.minjieren.com/wordpress-3.1-zh_CN.zip`  下载单个文件
+ `wget -O wordpress.zip http://www.minjieren.com/download.aspx?id=1080`  以不同的文件名保存
+ `wget -c http://www.minjieren.com/wordpress-3.1-zh_CN.zip`  使用wget -c断点续传
+ `wget --mirror -p --convert-links -P ./LOCAL URL`  镜像整个网站到本地
+ `wget -r -A.pdf url`  使用wget -r -A下载指定格式文件


## 系统
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

## 其他
>>>>>>> Stashed changes
