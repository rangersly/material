# makefile

makefile 是一个通用的项目代码构建器
由规则 依赖 命令构成

规则:依赖
	命令

+	-n		参数可以打印出make会执行的命令，但不真正执行

# 注意: 命令前面必须要用Tab

# 伪目标
.PHONY:clean

# 自动变量
	$@		目标文件
	$<		第一个依赖文件
	$^		全部的依赖文件

# 普通变量定义
OPTION = -O3 -Wall

# 变量使用
	g++ $(OPTION) xxx

# 使用通配符
%.o: %.c
	g++ $(OPTION) -c $< -o $@


```makefile
.PHONY:clean
INCLUDE = -I/home/e0x2d/include
main: file1.o file2.o
	g++ -o $@ file1.o file2.o

file1.o: file1.cpp
	g++ -c file1.o file1.cpp 

file2.o: file2.cpp
	g++ -c file2.o file2.cpp ${INCLUDE}

clean: 
	rm *.o demo
```
