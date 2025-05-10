# gdb c/c++ 代码调试工具
使用 -g 生成调试文件，不可以加 -O 选项

## 目录
- [基础使用](#base)
  - [run](#run)
  - [set](#set)
  - [mem](#mem)
  - [disassemble](#disassemble)
  - [info](#info)
- [core](#core)

## base
`l n`         列出源码
`b n`         在第n行打断点
`break main if var_name > 10`  满足条件时打断点
`d n`         删除断点
`lay next`    切换窗口布局TUI
`Ctrl-x a`    退出TUI
`Ctrl-x 1`    恢复单窗口布局
`Ctrl-x o`    切换窗口焦点
`ref``Ctrl-L` 刷新布局

### run
`r`           开始运行到第一个断点
`c`     继续运行到下一个断点
`s`     步入
`si`    单步汇编
`n`     步过
`ni`
`q`     退出

### set
`set [argc]`  传入参数
`set var []`		# 修改变量的值
`set $rsp = 0x7ccc`	# 修改寄存器的值

### mem
`p` 				# 查看特定变量或表达式的值
`bt`				# 查看函数调用栈
`bt full`			# 详细信息
`x/10gx $rsp`		# 查看内存中由$rsp开始的10个八字节数据 g:八字节 x:16进制

### disassemble
`disassemble`		# 查看当前函数的汇编，可在后面加函数名看指定汇编
`x/i $pc`           # 检查pc处的汇编

### info
`info locals`		# 查看局部变量
`info registers`	# 查看寄存器状态
`info program`  	# 查看程序运行信息
`info break`		# 查看断点信息
`info threads`  	# 查看所有线程

## core
1. `ulimit -c unlimited`   使挂掉的程序产生core文件

2. 修改 `/proc/sys/kernel/core_pattern`  使其在当前目录下生成core文件
> `sudo echo "./core" > /proc/sys/kernel/core_pattern

3. gdb ./a.out core

gdb demo -p [pid]		# 调试运行中的程序
