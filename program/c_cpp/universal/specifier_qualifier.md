# 说明符

## 目录
- [static](#static)
- [extern](#extern):引用声明
- [mutable](#mutable)
- [thread local](#`thread_local`)
- [const](#const)
  -[const with point](# const-with-point)
- [volatile](#volatile):强制读内存
- [restrict](#restrict) : 指示编译器优化指针(C99)


##	static
- 用在整个文件的声明中，表示内部连接性
- 局部声明中，代表存储持续性为静态

- 可将函数限制为内部连接性
> `static void show();`

- 在c语言中常用于将内部函数与外部接口分离

##	extern
	引用声明
	声明引用在其他地方定义的变量或者函数

##	mutable
	即使结构(类)被声明为const,也可以被修改的成员函数
```cpp
	struct people {
		int scora;
		mutable int accesses;
	};
	const people demo;
	demo.accesses = 0;
```

##	const
	const 全局变量的连接性为内部(默认外部)
	就像使用了static
	如果希望连接性为外部，则可以用extern覆盖

### const-with-point
```c
const int * p;  // 指向常量的指针
int *const p;  // 指针常量(不可修改指向)
const int * const p;  // 指针和被指向的都不可修改
```

## restrict
- 在没有 restrict 的情况下，编译器需要考虑指针之间可能存在的别名关系。编译器会频繁地从内存中读取数据，以确保每次使用指针时数据是最新的。这会导致不必要的内存访问
- 使用 restrict 后，编译器可以假设带有 restrict 的指针是唯一的，不会与其他指针指向同一块内存。因此，编译器可以减少不必要的内存访问

```c
void copy(int *restrict dest, int *restrict src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}
```
__如果违反了 restrict 的约束（即多个 restrict 指针指向同一块内存），程序的行为是未定义的__
