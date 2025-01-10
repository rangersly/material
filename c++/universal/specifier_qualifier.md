# 存储说明符
+	static
+	extern
+	mutable
+	thread_local

#	cv 说明符
+	const
+	volatile


##	static
	用在整个文件的声明中，表示内部连接性
	局部声明中，代表存储持续性为静态

	可将函数限制为内部连接性
	`static void show();`

##	extern
	引用声明
	声明引用在其他地方定义的变量

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

##	volatile 强制读内存
