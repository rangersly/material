# gcc-g++ 编译器

## 目录
- [编译选项](#编译选项)
- [制作库文件](#制作库文件)

## 编译选项
- `g++ -S test.s test.cpp`		编译成汇编文件
- `g++ -c test.o test.s`			目标文件
- `g++ -o test test.o`			链接

- ***优化等级***
  - **O0** 不进行任何优化
  - **O1** 基础优化
    - 删除未使用的变量和函数
	- 简化控制流（如合并重复代码）
	- 常量折叠（如 2+3 替换为 5）
	- 简单的寄存器分配
  - **O2** 中等优化，推荐级别
    - 指令调度（提高指令级并行性）
	- 循环优化（如循环展开、循环不变代码外提）
	- 函数内联（简单函数直接展开）
	- 分支预测优化
	- 数据流分析优化
  - **O3** 激进优化
	- 更激进的循环优化（如自动向量化，利用 SIMD 指令如 SSE/AVX）
	- 函数内联更积极（可能导致代码膨胀）
	- 删除冗余内存访问
	- 数学表达式重构（可能影响浮点精度）
  - **优化易导致的问题**
    - 暴露未定义行为（Undefined Behavior, UB）
	- 调试信息不匹配
	- 重新排列或合并浮点运算，导致精度损失
	- 代码体积膨胀
	- 重排内存访问顺序，影响多线程程序或硬件寄存器操作
	- 依赖时序的代码失效
	- 向量化（SIMD）导致的兼容性问题
	- 内联汇编的意外行为

- `g++ -S -o - -fverbose-asm xxx.cpp > xxx.s`	// 输出带注释的汇编

`gcc -s` 选项用于剥除可执行文件中的符号表和重定位信息，减小可执行文件的大小
- **正常功能保持**
- **性能无显著差异**
- **调试困难**：符号表中包含了函数名、变量名等调试信息。使用 `-s` 选项后，这些信息会被移除，使得调试变得非常困难
- **反汇编和分析不便**：没有符号表，反汇编工具（如 `objdump`）无法显示函数名和变量名等信息，只能显示汇编指令和地址。这会增加对程序进行反汇编分析的难度。


## 制作库文件
### 静态库制作:
	g++ -c -o libtest.a {test.cpp 源代码文件清单}
//	g++ -c test.cpp
//	ar -crv libtest.a test.o


### 动态库制作
	g++ -fPIC -shared -o libtest.so {test.cpp 源代码文件清单} 
//	g++ -fPIC -c test.cpp
//	g++ -shared -o libtest.so tset.o
	两种方法
		1 + .so 放到 /usr/lib 或 /lib
		2 + 路径放到/etc/ld.so.conf 运行ldconfd 重建/etc/ld.so.cache

### 库使用
	g++ -o main -l库名 -L库路径 -I头文件路径
	// g++ -o main -ltest -L/home/e0x1a/test

#### `-rpath 是 GNU 链接器的一个选项，它会在可执行文件中嵌入运行时库搜索路径`
`gcc -o myapp myapp.c -L../libs -lmylib -Wl,--enable-new-dtags,-rpath,'$ORIGIN/../libs'`
```
-Wl,-rpath,/path/to/libs：
    -Wl 告诉 GCC 将后面的参数传递给链接器
    -rpath 是链接器选项
    /path/to/libs 是要嵌入的运行时搜索路径
```

	如果是动态库，需要指定 `LD_LIBRARY_PATH` 环境变量 	//待查
		用 `echo $LD_LIBRARY_PATH` 查看
