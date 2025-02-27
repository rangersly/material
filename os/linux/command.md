# 基础命令
>	sudo	
>	>	配置文件/etc/sudoers 使用visudo进行编辑
	+	-u		# 指定用户

>	pwd

>	cd

>	ls
>	>	列出目录下所有内容
	+	-F				# 在文件名后加提示符 '/' '*' '@'
	+	-a				# 显示隐藏文件
	+	-l				# 列出文件信息
	+	-d				# 目录
	+	-h				# 将文件大小输出为易读的格式
	+	-s				# 在行首显示(大小)?
	+	-i				# inode


# 文件目录操作管理
>	cat
>	>
	+	-n				# 显示行号

>	less

>	od
>	>	查看非纯文本
	+	-t 			# 类型 a, d, f, o, x

>	grep
>	>	文件字符串匹配
	+	-A <n>			# 后续n行
	+	-B <n>			# 前n行
	+	-n				# 显示行号
	+	-v				# 反向选择
	+	-E 'o1|o2|o3'	# 多匹配

>	wc
>	>	统计
	+	-l	行数
	+	-m	字符
	+	-w	

>	mkdir

>	touch

>	mv
>	>
	+	-i			# 覆盖时警告
	+	-b			# 重合加~

>	cp	
>	>	copy
	+	-i			# 覆盖时警告
	+	-b			# 重合加~
	+	-u			# 仅复制更新
	+	-v			# 详细显示
	+	-r			# 目录

>	rm
>	>
	+	-i			# 覆盖时警告
	+	-r			# 目录
	+	-f			# 强制

>	chown
>	>	所有权
	+	-R			# 同时更改所有子目录

>	chmod
>	>	权限修改
	+	-R			# 同时更改所有子目录
```bash
	SUID	4
		执行二进制文件时，权限提升为文件所有者
		
	SGID	2
		在此权限下的目录进入后，有效用户组变为所有组

	SBIT	1
		在此权限下的文件夹里创建文件，仅有root与属主有权操作
```

>	file
>	>	观察文件类型
	+	-i		查看编码格式
	+	-z		查看压缩格式
	+	-b		查看文件的系统架构
	+	-p		详细信息

>	umark
>	>	设置默认权限，默认是拿掉权限

>	ln
>	>	链接(硬)
	+	-s			# 符号链接(软)

>	diff
>	>	比较文件
	+	-b			# 忽略空格
	+	-i			# 忽略大小写
	+	-B			# 忽略空白行

>	patch
>	>	补丁制作
>	>	example
```bash
	diff -Naur <oldfile> <newfile>  >  <file.patch>		# -p[n] 拿掉路径中的/
	patch -p<n> <  <file.patch>			# 制作
	patch -p<n>-R <  <file.patch>		# 还原
```

>	rsync
>	>	文件同步工具,它通过比较源和目标文件的大小、时间戳等信息，只同步发生变化的部分,提高了效率
>	>	rsync [选项] 源文件/目录 目标文件/目录
	+	-a（archive）：归档模式,用于完整同步
	+	-v（verbose）：详细模式，显示同步过程中的详细信息。
	+	-u（update）：仅在目标文件不存在或源文件更新时才同步。
	+	-z（compress）：在传输过程中压缩文件数据。
	+	--delete：删除目标目录中多余的文件，使目标目录与源目录保持一致
	+	-e（rsh）：指定远程连接时使用的工具（如 ssh）。
	+	--exclude：指定排除的文件或目录模式。
	+	--include：指定包含的文件或目录模式。
	+	-P --progress：显示同步进度。
	+	--bwlimit : 限速，用于单个大文件，避免占用过多带宽
	+	--dry-run：模拟同步操作，不实际执行，用于测试同步命令的效果。
>	>	example
	1.	本地同步
		rsync -avP /path/to/source/ /path/to/destination/
	2.	从本地同步到远程
		rsync -avzP /path/to/source/ user@remote_host:/path/to/destination/
	3.  同步时删除多余文件
		rsync -av --delete /path/to/source/ /path/to/destination/
	4.  排除某些文件或目录
		rsync -av --exclude 'temp/*' --exclude '*.log' /path/to/source/ /path/to/destination/
		--exclude 'temp/*'：排除 temp 目录下的所有文件。
		--exclude '*.log'：排除所有 .log 文件。
	5.  包含某些文件或目录
		rsync -av --include 'data/*' --exclude '*' /path/to/source/ /path/to/destination/
		--include 'data/*'：仅包含 data 目录下的文件。
		--exclude '*'：排除其他所有文件。
	6.  模拟同步操作
		rsync -av --dry-run /path/to/source/ /path/to/destination/


# 文件查找
>	find
>	>	find [OPTION] [path] [expression]
	+	-name [filename]	# 指定文件名
	+	-print				# 打印结果在终端
	+	-type [type]		# 指定类型
	+	-atime <+-n>		# n天前使用的文件
	+	-mtime <+-n>		# n天前修改的文件
>	>	example
	+	find /usr/bin -name zip -print

>	locate

>	whereis
>	>	找命令文件

>	which
>	>	找PATH
	+	-a		# 全部列出
>	whoami

>	uname
>	>	查看系统版本信息
	+	-a	全部信息


# 文件压缩
>	gzip
>	>
	+	-d			# 解压
	+	-l			# 查看压缩效果

>	bzip2
>	>	
	+	-d			# 解压
	+	-l			# 查看压缩效果

>	xz
>	>
	+	-z			# 压缩
	+	-d			# 解压
	+	-l			# 查看压缩效果
	+	-k			# 保留压缩原文件
	+	-<number>	# 压缩等级
	+	-T <n>		# 使用多个线程
	+	-v			# 显示详细过程

>	tar 
>	>	文件打包
	+	-c			# 创建
	+	-x			# 解开
	+	-v			# 显示详细过程
	+	-f <file>	# 指定文件名
	+	-z			# 调用gzip
	+	-j			# 调用bzip2
	+	-J			# 调用xz
>	>	example
	+	tar -cvjf shell.tar.bz2 shell/

>	dd
>	>	
	+	if		# input file/device
	+	of		# output file/device
	+	bs		# one black size
	+	count	# *bs
	




# 磁盘
>	mount
>	>	挂载文件系统
	+	-r			# 只读
	+	-o <loop>	# 特殊设备
>	>	/etc/fstab	配置文件
	+	auto		# 开机自动挂载
	+	noauto		# 不自动挂载
	+	ro			# read only
	+	rw			# read and write
	+	user		# 任意用户可挂载
>	>	example
	+	[设备/UUID]		[挂载点]	[文件系统]	[参数] 0 0

>	umount
>	>	卸载文件系统

>	df
>	>	观察磁盘使用情况
>	>	example
	+	df -hT

>	sync

>	 smartctl
>	>	查看硬盘状态参数
		-a	全部参数
		-H	是否正常

>	parted
>	>	磁盘分区管理工具
>	>	parted [OPTIONS] [DEVICES] [COMMAND]
	+	-i		列出所有设备的分区信息
	+	-s		非交互模式
>	>	交互模式常用命令
	+	print					显示当前设备的分区表
	+	mklabel [gpt/msdos]		创建分区表
	+	mkpart [part-type] [fs-type] [start] [end]		创建一个分区
`例:	mkpart primary ext4 1MiB 1000MiB`
	+	rm [number]				删除指定编号的分区
	+	resizepart [number] [size]	重调大小
	+	set [number] [mode]		设置分区标志
	+	quit
>	>	非交互
`sudo parted -s /dev/sdb mklabel gpt mkpart primary ext4 0% 100%`
`sudo parted -s /dev/sdb rm 2`


# 用户
>	useradd
>	>
	+	-m		# 同时建立主目录
	+	-g		# 指定用户组
	+	-s		# 指定shell

>	groupadd

>	passwd

>	userdel
>	>
	+	-r		# 删除主目录

>	usermod
>	>
	+	-d			# 修改主目录
	+	-e <MM/DD/YY># 修改账号有效期
	+	-s			# 修改shell

>	id
>	>	查看用户信息

>	/etc/passwd
>	>	example
	+	登录名:口令:UID:GID:x信息:主目录:shell

>	/etc/group
>	>	example
	+	组名:组口令(一般无):GID:user1,user2,user3

### 用户所有组是passwd和groups的并集

>	newgrp
>	>	切换有效用户组



# 进程
>	ps
>	>	
	+	aux

>	top

>	lsop	
>	>	查看占用文件的进程

>	kill
>	>	发送信号
	+	-l			# 列出所有信号

>	nice  renice
>	>	调整谦让度

>	bg
>	>	让后台中的进程继续运行

>	fg
>	>	把后台进程拉回前台

>	jobs
>	>	列出后台进程



# 网络
>	ip
>	>	查看网络的各种信息
>	>	address		地址等连接信息
>	>	neigh		arp相关
	+	ip neigh [OPTIONS] [COMMAND]
	+	ip neigh add [IP] lladdr [MAC] dev [eth0] 		添加表项
	+	ip neigh del [IP] dev [eth0] 					删除表项
	+	ip neigh flush all								清空
	_________________________________
	REACHABLE：表示邻居设备可达。
	STALE：表示邻居设备的条目已过期，但之前是可达的。
	DELAY：表示正在等待确认邻居设备是否可达。
	PROBE：表示正在积极探测邻居设备是否可达
	_________________________________

>	ss
>	>	查看端口开放情况
	+	-t		# tcp
	+	-u		# udp
	+	-n		# 以端口号显示
	+	-l		# 列出正在监听的服务
	+	-p		# + pid
	+`	-r		# 路由表
>	>	example
	+	ss -tlunp

>	ping


# 系统
>	systemctl
>	>	systemctl [command] [unit]
	+	start
	+	stop
	+	restart
	+	reload
	+	enable
	+	disable
	+	status
	+	mask		# 强制注销
	+	unmask
>	>	
	+	list-units
>	>
	+	get-default		# 获取目前target
	+	set-default		# 设置默认target
	+	isolate			# 切换target
>	>	>
		+ 	poweroff
		+ 	reboot
		+ 	suspend		# 挂起
		+ 	hibernate	# 休眠
		+ 	rescue		# 修复


# 硬件
>	dmidecode
>	>	获取硬件信息
	+	-q		# 简洁
	+	-t		# 指定查看类型



# 软件包管理
>	dpkg
>	>	.deb
	+	-i		# 安装
	+	-l		# 查看版本
	+	-r		# 卸载

>	apt
>	>	apt-get
>	>	>
		+	updata		# 更新软件包缓存
		+	upgrade		# 更新已有软件包的最新版本
		+	install		# 下载并安装
		+	remove		# 卸载
		+	source		# 下载源码
>	>	apt-cache
>	>	>
		+	search		# 搜索
		+	depends		# 列出依赖
>	>	配置源
	+	/etc/apt/sources.list


# 其他命令
	# nohup	命令挂机(退出登陆后依然执行)
		nohup [command] &
		`screen` 主要用于用户开启多个独立的会话(称为"窗口")在这些会话之间可以自由切换而不会中断已经运行的程序
		### 基本使用方法：
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
	
	
	
	# ulimit
		查看和修改进程运行资源限制	
		-H/S		# 设置/显示 软/硬 限制
		-a			# 显示所有
		-t			# cpu time
		-f			# file size
		-s			# stack size
		-c			# core file size
		-m			# memory size
		-l			# lock memory size
	-p			# user processes
	-n 			# open file

	#ulimit -Ht 3600
