#	c风格字符串

`#include <cstring>`

```cpp
	strcpy(buf1, "hello");		// 用后面的字符串覆盖前面的字符串
	strncpy(buf1, "hello", 5);	// 增加指定长度

	strcat(buf1, "hello");		// 连接字符串
	strncat(buf1, "hello", 5);

	strcmp(buf1, "hello");		// 比较字符串,相等返回0

	strlen(buf1);				// 返回长度，不包括'\0'

	strstr(buf1, "hello");		// 返回第一次出现子串的指针

	strtok(buf1, " ");			// 分割字符串，返回分割过的字符串

	memset(buf1, 0, sizeof(buf1));//覆写内存块

	memcpy(buf1, "hello", 5);	//复制内存块

	memmove(buf1 + 1, buf1, 4);	//移动5个字节到前一个位置
```
## 两种转换
```cpp
	string str1;
	const char* str2 = str1.c_str();
	
	const char* str3;
	string str4(str3);
```
