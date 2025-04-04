# gcc-g++ 编译器

## 目录
- [编译选项](#编译选项)
- [制作库文件](#制作库文件)

## 编译选项
`g++ -S test.s test.cpp`		编译成汇编文件
`g++ -c test.o test.s`			目标文件
`g++ -o test test.o`			链接

`g++ -O1/-O2/-O3`			// 优化选项

`g++ -S -o - -fverbose-asm xxx.cpp > xxx.s`	// 输出带注释的汇编

`gcc -s` 选项用于剥除可执行文件中的符号表和重定位信息，减小可执行文件的大小
- **正常功能保持**
- **性能无显著差异**
- **调试困难**：符号表中包含了函数名、变量名等调试信息。使用 `-s` 选项后，这些信息会被移除，使得调试变得非常困难
- **反汇编和分析不便**：没有符号表，反汇编工具（如 `objdump`）无法显示函数名和变量名等信息，只能显示汇编指令和地址。这会增加对程序进行反汇编分析的难度。


## 制作库文件
> 静态库制作:
	g++ -c -o libtest.a {test.cpp 源代码文件清单}
//	g++ -c test.cpp
//	ar -crv libtest.a test.o


> 动态库制作
	g++ -fPIC -shared -o libtest.so {test.cpp 源代码文件清单} 
//	g++ -fPIC -c test.cpp
//	g++ -shared -o libtest.so tset.o
	两种方法
		1 + .so 放到 /usr/lib 或 /lib
		2 + 路径放到/etc/ld.so.conf 运行ldconfd 重建/etc/ld.so.cache

> 库使用
	g++ -o main -l库名 -L库路径 -I头文件路径
	// g++ -o main -ltest -L/home/e0x1a/test

	如果是动态库，需要指定 LD_LIBRARY_PATH 环境变量 	//待查
		用 echo $LD_LIBRARY_PATH 查看
