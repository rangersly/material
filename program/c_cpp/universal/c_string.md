# c风格字符串
`#include <cstring>`

---

## INDEX

- [字符串库函数](# std-string)
- [内存操作标准库函数](# std-mem)
- [与string容器转换](# to-string)

---

## **std-string**
```c
	strcpy(buf1, "hello");		// 用后面的字符串覆盖前面的字符串
	strncpy(buf1, "hello", 5);	// 增加指定长度

	strcat(buf1, "hello");		// 连接字符串
	strncat(buf1, "hello", 5);

	strcmp(buf1, "hello");		// 比较字符串,相等返回0

	strlen(buf1);				// 返回长度，不包括'\0'

	strstr(buf1, "hello");		// 返回第一次出现子串的指针

	strtok(buf1, " ");			// 分割字符串，返回分割过的字符串
```
___注:未进行长度指定的函数有溢出风险 例如:strcpy___

---

## **std-mem**

- 内存操作函数与str系的最大不同是不检测EOF
```c
	memset(buf1, 0, sizeof(buf1));//覆写内存块

	memcpy(buf1, "hello", 5);	//复制内存块,不处理内存重叠

	memmove(buf1 + 1, buf1, 4);	//移动5个字节到前一个位置,可处理重叠
```
- `int memcmp(const void *ptr1, const void *ptr2, size_t num);`
  - 比较函数,返回0表示相等

--- 

## 两种转换
```cpp
	string str1;
	const char* str2 = str1.c_str();
	
	const char* str3;
	string str4(str3);
```
