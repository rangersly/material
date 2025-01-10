# string 	字符串模板

`#include <string>`

##  构造
```cpp	
		string();						// 默认构造，创建一个空的字符串
		string(const char &str1);		// c风格字符串初始化
		string(int n,char c);			// 用字符填充一个字符串
```

##  赋值
```cpp	
		string& operator=(const char* str1);	// c风格字符串赋值给当前string类
		string& operator=(const string& buf);	// 另一个容器复制
		string& operator=(const cahr c);		// 字符赋值
```

##  存取
```cpp	
		
		char& operator[](int n);				// 通过[]获取字符,注意溢出
```

##  拼接
```cpp	

		string& operator+=(const string& str);	// 追加到末尾
		string& operator+=(const char* str);	// 追加到末尾
		string& operator+=(const char c);		// 追加到末尾
```

##  查找
```cpp	
		
		int find(const string& str, int pos = 0) const;	// 查找str在当前字符串第一次出现的位置,pos为开始查找的位置
		int find(const char* str, int pos = 0) const;	// 查找str在当前字符串第一次出现的位置
		int rfind(const char* str, int pos = npos) const;	// 查找str在当前字符串第一次出现的位置,反向查询

		string::npos 	在值上等于-1 即size_t的最大值 表示直到字符串结束
```

##  替换
```cpp	
		
		string& replace(int pos, int n, const string& str);	// 从pos开始替换，n个字符
		string& replace(int pos, int n, const char* str);	// 从pos开始替换，n个字符
```
		
##  比较
```cpp	

		int compare(const string& str) const;	//根据字典序
		int compare(const char* str) const;		//根据字典序

		各种比较操作符都有重载
```
	
##  子串
```cpp	
		string substr(int pos = 0, int n = npos) const;	//返回从pos开始,长度为n的子串
```

##  插入
```cpp	

		string& insert(int pos, const char* str);		//在pos位置插入
		string& insert(int pos, const string& str);		//在pos位置插入
		string& insert(int pos, int n, char c);			//在pos位置插入
```

##  删除
```cpp	

		string& erase(int pos, int n = npos);		//在pos位置插入
```

## 两种转换
```cpp	
	string str1;
	const char* str2 = str1.c_str();
	
	const char* str3;
	string str4(str3);
```

## 神奇转换函数
```cpp	
	string to_ strinf(任何类型);		//将好多类型转换成string
```
