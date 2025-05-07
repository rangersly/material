# LIBRARY

---

## INDEX

- [C](#C)
  - [输入/输出 stdio](#stdio)
  - [资源管理和系统交互 stdlib](#stdlib)
  - [字符串处理 string](#string)
  - [数学函数 math](#math)
  - [字符处理 ctype](#ctype)
  - [时间/日期 time](#time)
  - [错误处理 errno](#errno)
  - [断言 assert](#assert)
  - [可变参数处理 stdarg](#stdarg)
  - [信号处理 signal](#signal)
  - [标准定义stddef](#stddef)
  - [整数范围 limits](#limits)
  - [浮点数特性 float](#float)
  - [布尔类型(C99) stdbool](#stdbool)
  - [固定大小整数(C99) stdint](#stdint)
  - [复数运算(C99) complex](#complex)
  - [泛型数学(C99) tgmath](#tgmath) : 类型泛型数学宏
  - [浮点环境(C99) fenv](#fenv)
  - [多线程支持(C11) threads](#threads)
  - [原子操作(C11) stdatomic](#stdatomic)
  - [Unicode支持(C11) uchar](#uchar)
- [CPP](#CPP)
  - [STL](../STL/)
- [POSIX](#unistd)
- [SELF](#SELF)
  - [offsetof](./self/offsetof.h)
  - [string hash](./self/string_hash.c)
  - [thread pool](./self/thread-pool.cpp)
  - [BIT](./self/bit.h)

---

## **stdio**

大部分内容已经完善,请参阅这里[IO](../universal/io.md)

---

## **stdlib**

### 动态内存管理

- [看这里哦](../universal/dynamic-memory.md)

### 程序终止与控制

- `void exit(int status)`
  - 正常终止程序并调用atexit里注册的函数
  - 参数(返回码)设置为(`EXIT_SUCCESS`或`EXIT_FAILURE`)

- `void abort(void)`
  - 异常终止程序,不执行清理操作,直接终止进程(触发 SIGABRT 信号)

- `int atexit(void (*func)(void))`
  - 注册程序终止时执行的函数(按注册的逆序调用)

### 系统交互

- `int system(const char* command)`
  - 执行操作系统命令
  - 返回命令执行的状态码

- `char* getenv(const char* name)`
  - 获取环境变量值
  - 返回的字符串不可修改

### 随机数生成

- `int rand(void)`
  - 生成伪随机数
  - 范围 `0` 到 `RAND_MAX`

- `void srand(unsigned int seed)`
  - 设置随机数种子,通常用 `time(NULL)` 初始化

### 搜索与排序 

- `void qsort(void* base, size_t nmemb, size_t size,
          int (*compar)(const void*, const void*));`
  - 快速排序数组

- `void* bsearch(const void* key, const void* base,
             size_t nmemb, size_t size,
             int (*compar)(const void*, const void*));`
  - 在已排序数组中二分查找元素
  - 找到返回元素地址,否则返回 `NULL`

### 数值转换
    
- `atoi`,`atof`,`atol`
  - 将字符串转换为整数、浮点数、长整数
  - 无法检测错误

- `strtol`,`strtod`
  - 更安全的字符串转换,可检测错误和进制

- `abs`,`labs`,`llabs`
  - 返回 整数/长整数/长长整数 的绝对值

---

## **string**

- [包含于这里](../universal/c_string.md)

---

## **math**

### **1. 基本数学运算**
#### **(1) 绝对值函数**
| 函数 | 描述 | 示例 |
|------|------|------|
| `int abs(int x)` | 整数绝对值(在 `<stdlib.h>`) | `abs(-5) = 5` |
| `double fabs(double x)` | 浮点数绝对值 | `fabs(-3.14) = 3.14` |
| `long labs(long x)` | 长整数绝对值 | `labs(-100L) = 100` |

#### **(2) 幂与开方**
| 函数 | 描述 | 示例 |
|------|------|------|
| `double pow(double x, double y)` | 计算 \( x^y \) | `pow(2, 3) = 8.0` |
| `double sqrt(double x)` | 平方根 \( \sqrt{x} \) | `sqrt(16) = 4.0` |
| `double cbrt(double x)` (C99) | 立方根 \( \sqrt[3]{x} \) | `cbrt(27) = 3.0` |
| `double hypot(double x, double y)` | 计算 \( \sqrt{x^2 + y^2} \)(直角三角形的斜边) | `hypot(3, 4) = 5.0` |

#### **(3) 取整与余数**
| 函数 | 描述 | 示例 |
|------|------|------|
| `double ceil(double x)` | 向上取整 | `ceil(3.2) = 4.0` |
| `double floor(double x)` | 向下取整 | `floor(3.9) = 3.0` |
| `double round(double x)` (C99) | 四舍五入 | `round(3.5) = 4.0` |
| `double trunc(double x)` (C99) | 截断小数部分 | `trunc(3.9) = 3.0` |
| `double fmod(double x, double y)` | 浮点数取余 | `fmod(5.5, 2) = 1.5` |
| `double remainder(double x, double y)` (C99) | IEEE 754 标准余数 | `remainder(10, 3) = 1.0` |

### **2. 三角函数(角度单位：弧度)**
| 函数 | 描述 | 示例 |
|------|------|------|
| `double sin(double x)` | 正弦函数 | `sin(M_PI/2) ≈ 1.0` |
| `double cos(double x)` | 余弦函数 | `cos(0) = 1.0` |
| `double tan(double x)` | 正切函数 | `tan(M_PI/4) ≈ 1.0` |
| `double asin(double x)` | 反正弦(结果在 \([-π/2, π/2]\)) | `asin(1) ≈ 1.5708` |
| `double acos(double x)` | 反余弦(结果在 \([0, π]\)) | `acos(0) ≈ 1.5708` |
| `double atan(double x)` | 反正切(结果在 \([-π/2, π/2]\)) | `atan(1) ≈ 0.7854` |
| `double atan2(double y, double x)` | 计算 \( \arctan(y/x) \)(考虑象限) | `atan2(1, 1) ≈ 0.7854` |

**注意**：
- 使用三角函数时,通常需要先转换角度为弧度：
  ```c
  double degrees = 45.0;
  double radians = degrees * (M_PI / 180.0);
  printf("sin(45°) = %f\n", sin(radians));
  ```
- `M_PI` 不是标准 C 定义的常量,但大多数编译器支持(需 `#define _USE_MATH_DEFINES`).

### **3. 指数与对数函数**
| 函数 | 描述 | 示例 |
|------|------|------|
| `double exp(double x)` | 自然指数 \( e^x \) | `exp(1) ≈ 2.71828` |
| `double exp2(double x)` (C99) | \( 2^x \) | `exp2(3) = 8.0` |
| `double log(double x)` | 自然对数 \( \ln(x) \) | `log(10) ≈ 2.30259` |
| `double log10(double x)` | 常用对数 \( \log_{10}(x) \) | `log10(100) = 2.0` |
| `double log2(double x)` (C99) | 二进制对数 \( \log_2(x) \) | `log2(8) = 3.0` |

### **4. 双曲函数**
| 函数 | 描述 | 示例 |
|------|------|------|
| `double sinh(double x)` | 双曲正弦 | `sinh(1) ≈ 1.1752` |
| `double cosh(double x)` | 双曲余弦 | `cosh(0) = 1.0` |
| `double tanh(double x)` | 双曲正切 | `tanh(1) ≈ 0.7616` |

### **5. 误差与伽马函数(C99)**
| 函数 | 描述 |
|------|------|
| `double erf(double x)` | 误差函数 |
| `double erfc(double x)` | 互补误差函数 |
| `double tgamma(double x)` | 伽马函数 \( \Gamma(x) \) |
| `double lgamma(double x)` | \( \ln(\|\Gamma(x)\|) \) |

### **6. 浮点数操作**
| 函数 | 描述 |
|------|------|
| `double frexp(double x, int *exp)` | 分解浮点数为尾数和指数 |
| `double ldexp(double x, int exp)` | \( x \times 2^{exp} \) |
| `double modf(double x, double *intpart)` | 分离整数和小数部分 |

### **7. 其他函数**
| 函数 | 描述 |
|------|------|
| `double fmax(double x, double y)` (C99) | 返回较大值 |
| `double fmin(double x, double y)` (C99) | 返回较小值 |
| `double fdim(double x, double y)` (C99) | 返回 \( x - y \)(如果 \( x > y \),否则 0) |
| `double copysign(double x, double y)` (C99) | 返回 `x` 的绝对值 + `y` 的符号 |

### **8. 宏与常量**
| 宏 | 描述 |
|------|------|
| `INFINITY` | 表示无穷大(如 `1.0 / 0.0`) |
| `NAN` | 表示非数字(如 `0.0 / 0.0`) |
| `HUGE_VAL` | 表示极大值(溢出时返回) |
| `M_E` | 自然对数底 \( e \)(非标准) |
| `M_PI` | 圆周率 \( \pi \)(非标准) |

---

## **ctype**

`<ctype.h>` 是 C 语言标准库中用于**字符分类和转换**的头文件,提供了一系列函数用于判断字符的类型(如字母、数字、空白符等)以及大小写转换.这些函数通常以 `int` 类型参数(字符的 ASCII 值)作为输入,并返回 `int` 类型(非零表示真,零表示假).

### **1. 字符分类函数**
这些函数用于检查字符是否属于特定类别,返回 **非零值(真)** 或 **0(假)**.

| 函数 | 描述 | 示例 |
|------|------|------|
| `int isalpha(int c)` | 检查 `c` 是否是字母(`A-Z` 或 `a-z`) | `isalpha('A')` → 非零 |
| `int isdigit(int c)` | 检查 `c` 是否是数字(`0-9`) | `isdigit('5')` → 非零 |
| `int isalnum(int c)` | 检查 `c` 是否是字母或数字 | `isalnum('a')` → 非零 |
| `int isxdigit(int c)` | 检查 `c` 是否是十六进制数字(`0-9`、`A-F`、`a-f`) | `isxdigit('F')` → 非零 |
| `int islower(int c)` | 检查 `c` 是否是小写字母(`a-z`) | `islower('a')` → 非零 |
| `int isupper(int c)` | 检查 `c` 是否是大写字母(`A-Z`) | `isupper('A')` → 非零 |
| `int isspace(int c)` | 检查 `c` 是否是空白字符(` `、`\t`、`\n`、`\r`、`\v`、`\f`) | `isspace(' ')` → 非零 |
| `int isblank(int c)` (C99) | 检查 `c` 是否是空白(` ` 或 `\t`) | `isblank('\t')` → 非零 |
| `int isprint(int c)` | 检查 `c` 是否是可打印字符(包括空格) | `isprint('A')` → 非零 |
| `int isgraph(int c)` | 检查 `c` 是否是可打印字符(**不包括空格**) | `isgraph(' ')` → 0 |
| `int iscntrl(int c)` | 检查 `c` 是否是控制字符(ASCII 0-31 或 127) | `iscntrl('\n')` → 非零 |
| `int ispunct(int c)` | 检查 `c` 是否是标点符号(非字母、数字、空格) | `ispunct('!')` → 非零 |

### **2. 字符转换函数**
| 函数 | 描述 | 示例 |
|------|------|------|
| `int tolower(int c)` | 将 `c` 转换为小写字母(如果 `c` 是大写字母) | `tolower('A')` → `'a'` |
| `int toupper(int c)` | 将 `c` 转换为大写字母(如果 `c` 是小写字母) | `toupper('a')` → `'A'` |

**注意**：
- 如果 `c` 不是字母,`tolower()` 和 `toupper()` 直接返回 `c`.
- 这些函数只适用于 ASCII 字符,不适用于 Unicode.

---

## **time**
### **1. 时间表示方式**
#### **(1) `time_t`**
- `typedef long time_t;`(通常是自 1970-01-01 00:00:00 UTC 的秒数,即 **Unix 时间戳**)
- `time_t now = time(NULL); // 获取当前时间戳`

#### **(2) `struct tm`**
存储**分解时间**(Broken-Down Time),包含以下字段
```c
struct tm {
    int tm_sec;   // 秒 [0, 60](60 用于闰秒)
    int tm_min;   // 分钟 [0, 59]
    int tm_hour;  // 小时 [0, 23]
    int tm_mday;  // 月中的第几天 [1, 31]
    int tm_mon;   // 月份 [0, 11](0 = 一月)
    int tm_year;  // 自 1900 年起的年份
    int tm_wday;  // 星期几 [0, 6](0 = 周日)
    int tm_yday;  // 年中的第几天 [0, 365]
    int tm_isdst; // 夏令时标志(>0: 夏令时,=0: 非夏令时,<0: 未知)
};
```

#### **(3) `clock_t`**
- `typedef long clock_t;`(表示 CPU 时间,单位通常是**时钟滴答**)

### **2. 时间获取函数**
#### **(1) `time()`**
- `time_t time(time_t *timer);`
- 获取当前日历时间(Unix 时间戳).

#### **(2) `clock()`**
- `clock_t clock(void);`
- 获取程序运行的 **CPU 时间**(单位是 `CLOCKS_PER_SEC` 的分数).

#### **(3) `difftime()`**
- `double difftime(time_t end, time_t start);`
- 计算两个 `time_t` 时间的差值(单位：秒).

### **3. 时间转换函数**
#### **(1) `gmtime()`**
- `struct tm *gmtime(const time_t *timer);`
- 将 `time_t` 转换为 **UTC 时间**(世界标准时间).

#### **(2) `localtime()`**
- `struct tm *localtime(const time_t *timer);`
- 将 `time_t` 转换为 **本地时间**(受时区和夏令时影响).

#### **(3) `mktime()`**
- `time_t mktime(struct tm *timeptr);`
- 将 `struct tm` 转换回 `time_t`(自动调整非法时间).

#### **(4) `asctime()`**
- `char *asctime(const struct tm *timeptr);`
- 将 `struct tm` 转换为固定格式的字符串(如 `"Sun Jan 1 00:00:00 2023\n"`).

#### **(5) `ctime()`**
- `char *ctime(const time_t *timer);`
- 将 `time_t` 转换为本地时间的字符串

#### **(6) `strftime()`(更灵活的格式化)**
- `size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr);`
- `strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);`
- **功能**：自定义时间格式
- **常用格式符**：
  | 格式符 | 说明 | 示例 |
  |--------|------|------|
  | `%Y` | 年份(4 位) | 2024 |
  | `%m` | 月份(01-12) | 02 |
  | `%d` | 日(01-31) | 15 |
  | `%H` | 小时(00-23) | 14 |
  | `%M` | 分钟(00-59) | 30 |
  | `%S` | 秒(00-60) | 45 |
  | `%A` | 星期全名 | Monday |
  | `%a` | 星期缩写 | Mon |
  | `%B` | 月份全名 | February |
  | `%b` | 月份缩写 | Feb |
  | `%c` | 完整日期时间 | Mon Feb 15 14:30:45 2024 |

---

## **errno**
### **1. `errno` 全局变量**
`extern int errno; // 声明全局错误变量`
- 当标准库函数执行失败时,会设置 `errno` 为特定的错误码.
- **特点**
  - 由系统或库函数自动设置,**程序启动时初始化为 0**(表示无错误).
  - **每个线程有独立的 `errno`**(多线程安全).
  - 必须在函数返回后**立即检查**,否则可能被后续操作覆盖.

### **2. 标准错误码宏**
| 宏 | 值 | 描述 |
|----|---|------|
| `EPERM` | 1 | 操作不允许(权限不足) |
| `ENOENT` | 2 | 文件或目录不存在 |
| `EINTR` | 4 | 系统调用被中断 |
| `EIO` | 5 | 输入/输出错误 |
| `EBADF` | 9 | 错误的文件描述符 |
| `EAGAIN` | 11 | 资源暂时不可用(可重试) |
| `ENOMEM` | 12 | 内存不足 |
| `EACCES` | 13 | 权限不足 |
| `EFAULT` | 14 | 错误的地址 |
| `EBUSY` | 16 | 资源忙 |
| `EEXIST` | 17 | 文件已存在 |
| `EINVAL` | 22 | 无效参数 |
| `ENFILE` | 23 | 系统打开文件数过多 |
| `EMFILE` | 24 | 进程打开文件数过多 |
| `ENOSPC` | 28 | 设备无剩余空间 |
| `EDOM` | 33 | 数学参数超出定义域 |
| `ERANGE` | 34 | 结果超出范围 |

### **3. 错误处理函数**
- **(1) `perror()`**
  - `void perror(const char *s);`
  - 打印错误描述(自动附加 `errno` 对应的错误信息).

- **(2) `strerror()`**
  - `char *strerror(int errnum);`
  - 返回错误码对应的字符串描述.

### **4. 使用场景**
- **(1) 文件操作错误处理**
- **(2) 数学函数错误处理**
- **(3) 动态内存分配错误**

### **5. 注意事项**
1. **`errno` 的线程安全性**：
   - 在多线程环境中,`errno` 是线程局部的(每个线程独立维护).
2. **`errno` 的初始化**：
   - 程序启动时 `errno` 为 0,调用成功**不会清零**(需手动重置).
3. **`errno` 的检查时机**：
   - 必须在函数返回后**立即检查**,否则可能被后续操作覆盖.
4. **不可直接修改 `errno`**：
   - 除非明确需要设置错误码,否则不应手动修改 `errno`.

---

## **assert**
`<assert.h>` 是 C 语言标准库中用于**程序断言(Assertion)**的头文件,它提供了一个宏 `assert()`,用于在程序运行时检查条件是否满足,如果条件为假(`false`),则终止程序并输出错误信息.

- `void assert(int expression);`
  - 如果 `expression` 为 `0`(假)
    1. 打印错误信息(包含文件名、行号、断言条件).
    2. 调用 `abort()` 终止程序.
  - 如果 `expression` 非 `0`(真),则不做任何操作.

-  **2. 启用/禁用断言**
  - **(1) 调试模式(默认启用)**
  - 不定义 `NDEBUG` 宏,`assert()` 生效：

- **(2) 发布模式(禁用断言)**
  - 定义 `NDEBUG` 宏,`assert()` 会被忽略

- **3. 使用场景**
  - **(1) 检查函数参数合法性**
  - **(2) 检查程序逻辑**
  - **(3) 调试复杂条件**

- **4. 注意事项**
  - 仅在 *调试模式(`NDEBUG` 未定义)* 下生效.
  - 在发布版本中可以通过定义 `NDEBUG` 宏禁用断言.
  - *`assert` 不能替代错误处理*

---

## **stdarg**
`<stdarg.h>` 是 C 语言标准库中用于处理**可变参数**的头文件，它允许函数接受不定数量的参数，类似于 `printf()` 和 `scanf()` 的实现方式。

### **1. 核心宏和类型**
#### **(1) `va_list`**
- 用于声明一个变量，该变量将保存可变参数列表

#### **(2) `va_start`**
- **宏**：`void va_start(va_list ap, last_arg);`
- **功能**：初始化 `va_list` 使其指向第一个可变参数
- **参数**：
  - `ap`：`va_list` 对象
  - `last_arg`：最后一个固定参数的名称

#### **(3) `va_arg`**
- **宏**：`type va_arg(va_list ap, type);`
- **功能**：获取下一个参数的值
- **参数**：
  - `ap`：`va_list` 对象
  - `type`：期望获取的参数类型
- **示例**：
  ```c
  int num = va_arg(args, int);
  ```

#### **(4) `va_end`**
- **宏**：`void va_end(va_list ap);`
- **功能**：清理 `va_list` 对象
- **注意**：必须在使用完参数后调用
- **示例**：
  ```c
  va_end(args);
  ```

### **3. 重要注意事项**
1. **没有类型检查**：
   - 编译器无法验证参数类型，错误使用会导致未定义行为
   - **错误示例**：
     ```c
     int num = va_arg(args, double); // 如果传入的是int，将导致未定义行为
     ```

2. **必须知道参数数量**：
   - 通常第一个参数用于指定后续参数的数量（如`printf`使用格式化字符串）

3. **必须调用`va_end`**：
   - 忘记调用可能导致内存泄漏或崩溃

4. **避免类型混用**：
   - 如果函数期望`int`但传入`float`，行为是未定义的

### **5. 总结**
| **宏/类型** | **功能** |
|------------|---------|
| `va_list` | 保存可变参数列表 |
| `va_start` | 初始化参数列表 |
| `va_arg` | 获取下一个参数 |
| `va_end` | 清理参数列表 |

---

## **signal**

### **信号概述**

- *信号* 是操作系统发送给进程的一种异步通知,用于告知进程发生了某种事件
- 由以下方式触发
  - Ctrl - C
  - 硬件异常
  - 其他进程发送
  - 操作系统事件

- **标准信号列表**

|信号    |值  |行为  |描述                  |
|--------|----|------|----------------------|
|SIGHUP	 |1   |A     |挂起或控制进程终止    |
|SIGINT  |2   |A     |C + c                 |
|SIGFPE	 |8   |C     |浮点异常              |
|SIGKILL |9   |AEF   |kill -9 强制杀死      |
|SIGSEGV |11  |C     |无效的内存引用        |
|SIGPIPE |13  |A     |管道破裂              |
|SIGALRM |14  |A     |闹钟alarm()信号       |
|SIGTERM |15  |A     |kill默认              |
|SIGCHLD |17  |B     |子进程结束            |

  - A	终止进程
  - B	忽略
  - C	终止进程并core dump
  - D	暂停
  - E	不能捕获
  - F	不可忽略

- **信号处理函数**
  - `void (*signal(int sig, void (*handler)(int)))(int);`
    - 设置信号 sig 的处理函数 handler
    - handler : `SIG_IGN` 或 `SIG_DFL` 或信号处理函数
    - 成功:返回之前的信号处理函数
    - 失败:返回 `SIG_ERR`
    - `signal(SIGINT, handler); // 捕获 Ctrl+C`

  - `int raise(int sig);`
    - 向当前进程发送信号 `sig`

- **实际开发的使用场景**
  - 捕获 `SIGTERM` 进行资源清理
  - 忽略 `SIGINT` 让程序不被 `Ctrl+C` 杀死
  - 捕获 `SIGSEGV` 记录错误信息
  - 使用 `SIGALRM` 实现超时机制

---

## **stddef**

定义基本类型和宏的头文件,提供与平台无关的类型定义和常用常量,在各种底层编程和跨平台开发中非常有用

1. **核心定义**
- `#define NULL ((void *)0)`
  - 表示空指针

- `typedef unsigned int size_t;`
  - 实际类型取决于平台

- `typedef int ptrdiff_t;`
  - 指针差值类型,表示两个指针之间的差值
  - 实际类型取决于平台

- `#define offsetof(type, member) ((size_t)&(((type *)0)->member))`
  - 计算结构体成员的字节偏移量

- `typedef unsigned short wchar_t;`
  - 宽字符类型
  - 实际类型取决于平台

2. 跨平台注意
- `size_t`实际大小
  - 32 位系统通常是 `unsigned int`
  - 64 位系统通常是 `unsigned long`
- NULL 的实现差异
  - C 中定义为 `((void *)0)`
  - C++ 中可能是 `0` 或 `nullptr`
  - 偏移量计算的限制:`offsetof`不能用于非标准布局类型(如含虚函数的 C++ 类)

---

## **limits**
定义基本数据类型取值范围,提供了各种整数类型的最大值和最小值的宏定义

- **1. 核心宏定义**
| 宏 | 含义 | 典型值（32位系统） |
|----|------|------------------|
| `CHAR_BIT` | 一个字节的位数 | 8 |
| `SCHAR_MIN` | `signed char` 最小值 | -128 |
| `SCHAR_MAX` | `signed char` 最大值 | 127 |
| `UCHAR_MAX` | `unsigned char` 最大值 | 255 |
| `CHAR_MIN` | `char` 最小值（取决于实现） | -128 或 0 |
| `CHAR_MAX` | `char` 最大值（取决于实现） | 127 或 255 |
| `SHRT_MIN` | `short` 最小值 | -32768 |
| `SHRT_MAX` | `short` 最大值 | 32767 |
| `USHRT_MAX` | `unsigned short` 最大值 | 65535 |
| `INT_MIN` | `int` 最小值 | -2147483648 |
| `INT_MAX` | `int` 最大值 | 2147483647 |
| `UINT_MAX` | `unsigned int` 最大值 | 4294967295 |
| `LONG_MIN` | `long` 最小值 | -2147483648 |
| `LONG_MAX` | `long` 最大值 | 2147483647 |
| `ULONG_MAX` | `unsigned long` 最大值 | 4294967295 |
| `LLONG_MIN` (C99) | `long long` 最小值 | -9223372036854775808 |
| `LLONG_MAX` (C99) | `long long` 最大值 | 9223372036854775807 |
| `ULLONG_MAX` (C99) | `unsigned long long` 最大值 | 18446744073709551615 |

- `<limits.h>` 主要用于
  - **防止数值溢出**
  - **编写可移植代码**
  - **系统属性检测**
  - **安全输入验证**

---

## float
`<float.h>` 是 C 语言标准库中定义**浮点数特性**的头文件，它提供了浮点类型的取值范围、精度和误差相关的宏定义。

- **1. 核心宏定义**
| 宏 | 含义 | 典型值（IEEE 754） |
|----|------|------------------|
| `FLT_RADIX` | 浮点数基数（通常为 2） | 2 |
| `FLT_MANT_DIG` | `float` 尾数位数 | 24 |
| `DBL_MANT_DIG` | `double` 尾数位数 | 53 |
| `LDBL_MANT_DIG` | `long double` 尾数位数 | 64 |
| `FLT_MIN` | `float` 最小正规范化值 | 1.175494e-38 |
| `FLT_MAX` | `float` 最大值 | 3.402823e+38 |
| `DBL_MIN` | `double` 最小正规范化值 | 2.225074e-308 |
| `DBL_MAX` | `double` 最大值 | 1.797693e+308 |
| `LDBL_MIN` | `long double` 最小正规范化值 | 3.362103e-4932 |
| `LDBL_MAX` | `long double` 最大值 | 1.189731e+4932 |
| `FLT_DIG` | `float` 的十进制有效数字 | 6 |
| `DBL_DIG` | `double` 的十进制有效数字 | 15 |
| `LDBL_DIG` | `long double` 的十进制有效数字 | 18 |
| `FLT_EPSILON` | `float` 的最小可表示差值 | 1.192093e-07 |
| `DBL_EPSILON` | `double` 的最小可表示差值 | 2.220446e-16 |
| `LDBL_EPSILON` | `long double` 的最小可表示差值 | 1.084202e-19 |
| `FLT_ROUNDS` | 当前浮点数舍入模式 |
- `<float.h>` 主要用于：
  - **浮点数安全比较**
  - **数值范围验证**
  - **精度控制**
  - **跨平台浮点运算**

---

## stdbool
用于布尔类型支持的头文件,C99 引入,提供了更清晰的布尔类型定义

1. **核心定义**
```#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
```

---

## stdint
定义固定宽度整数类型的头文件,C99,提供了明确位宽的整数类型

1. **核心整数类型定义**
| 类型 | 位宽 | 取值范围 | 对应传统类型 |
|------|------|----------|--------------|
| `int8_t` | 8位 | -128 ~ 127 | `signed char` |
| `uint8_t` | 8位 | 0 ~ 255 | `unsigned char` |
| `int16_t` | 16位 | -32768 ~ 32767 | `short` |
| `uint16_t` | 16位 | 0 ~ 65535 | `unsigned short` |
| `int32_t` | 32位 | -2147483648 ~ 2147483647 | `int` |
| `uint32_t` | 32位 | 0 ~ 4294967295 | `unsigned int` |
| `int64_t` | 64位 | -2^63 ~ 2^63-1 | `long long` |
| `uint64_t` | 64位 | 0 ~ 2^64-1 | `unsigned long long` |
| `int_least8_t` | 至少8位的有符号整数 |
| `uint_least8_t` | 至少8位的无符号整数 |
| ...（16/32/64位同理） | ... |
| `int_fast8_t` | 最快处理的至少8位有符号整数 |
| `uint_fast8_t` | 最快处理的至少8位无符号整数 |
| ...（16/32/64位同理） | ... |
| `intmax_t` | 系统支持的最大有符号整数 |
| `uintmax_t` | 系统支持的最大无符号整数 |
| `intptr_t` | 可保存指针值的有符号整数 |
| `uintptr_t` | 可保存指针值的无符号整数 |


2.  **极限值宏定义**
| 宏 | 含义 |
|----|------|
| `INT8_MIN`/`INT8_MAX` | `int8_t` 的最小/最大值 |
| `UINT8_MAX` | `uint8_t` 的最大值 |
| `INTMAX_MIN`/`INTMAX_MAX` | `intmax_t` 的极限值 |
| `UINTMAX_MAX` | `uintmax_t` 的最大值 |
| `PTRDIFF_MIN`/`PTRDIFF_MAX` | `ptrdiff_t` 的极限值 |
| `SIZE_MAX` | `size_t` 的最大值 |

3. **格式化输出宏**
| 宏 | 对应类型 | 格式化字符串 |
|----|----------|--------------|
| `PRIi8`/`PRIu8` | `int8_t`/`uint8_t` | `%hhd`/`%hhu` |
| `PRIi16`/`PRIu16` | `int16_t`/`uint16_t` | `%hd`/`%hu` |
| `PRIi32`/`PRIu32` | `int32_t`/`uint32_t` | `%d`/`%u` |
| `PRIi64`/`PRIu64` | `int64_t`/`uint64_t` | `%lld`/`%llu` |
| `PRIiMAX`/`PRIuMAX` | `intmax_t`/`uintmax_t` | `%jd`/`%ju` |

- `<stdint.h>` 为 C 语言带来了：
  - **精确的位宽控制**
  - **更好的跨平台兼容性**
  - **更安全的数值操作**

---

## **unistd**
- 进程控制
  - [fork](../linux/fork.cpp)
  - [exec](../linux/exec.cpp)
  - `unsigned int sleep(unsigned int seconds);`

- 文件操作
  - `ssize_t read(int fildes, void *buf, size_t nbyte);`
    - 共享偏移量
  - `ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset);`
    - 指定偏移量,线程安全
  - `ssize_t write(int fildes, const void *buf, size_t nbyte);`
  - `ssize_t pwrite(int fildes, const void *buf, size_t nbyte);`
  - `int clos(int fildes);`

- 管道操作
  - `int pipe(int fildes[2]);`
    - 创建匿名管道
    - [0]读
    - [1]写
    - 0 成功  -1 失败

- `uid_t getuid(void);`
  - 获取用户真实uid

- 目录操作
  - `int chdir(const char *path);`
    - 切换工作目录
    - 0 成功  -1 失败
  - `char *getcwd(char buf[.size], size_t size);`

- 其他
  - `int dup(int fildes);`
  - `int dup2(int fildes, int fildes2);`
    - 复制文件描述符
  - `int isatty(int fd);`
    - 检查文件描述符是否关联到终端

---
