#include <iostream>
#include <cstring>
using namespace std;

void c_char(const char *,const char *);
void c_string(const char *,const char *);

int main() {
	char a[1000],b[1000];
	cin >> a >> b;		// 流读入

	c_char(a, b);		//c风格字符串
	c_string(a, b);		//string

	return 0;
}

void c_char(const char *str1,const char *str2) {
	char buf1[1000],buf2[1000];
	printf("c风格字符串\n\n");
	strcpy(buf1, str1);	strcpy(buf2, str2);	

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

}
void c_string(const char *str1, const char *str2) {
	string buf;

/*
	// 构造
		
		string();						// 默认构造，创建一个空的字符串
		string(const char &str1);		// c风格字符串初始化
		string(int n,char c);			// 用字符填充一个字符串

	// 赋值

		string& operator=(const char* str1);	// c风格字符串赋值给当前string类
		string& operator=(const string& buf);	// 另一个容器复制
		string& operator=(const cahr c);		// 字符赋值

	// 存取
		
		char& operator[](int n);				// 通过[]获取字符,注意溢出

	// 拼接

		string& operator+=(const string& str);	// 追加到末尾
		string& operator+=(const char* str);	// 追加到末尾
		string& operator+=(const char c);		// 追加到末尾

	// 查找
		
		int find(const string& str, int pos = 0) const;	// 查找str在当前字符串第一次出现的位置,pos为开始查找的位置
		int find(const char* str, int pos = 0) const;	// 查找str在当前字符串第一次出现的位置
		int rfind(const char* str, int pos = npos) const;	// 查找str在当前字符串第一次出现的位置,反向查询

		string::npos 	在值上等于-1 即size_t的最大值 表示直到字符串结束

	// 替换
		
		string& replace(int pos, int n, const string& str);	// 从pos开始替换，n个字符
		string& replace(int pos, int n, const char* str);	// 从pos开始替换，n个字符
		
	// 比较

		int compare(const string& str) const;	//根据字典序
		int compare(const char* str) const;		//根据字典序

		各种比较操作符都有重载
	
	// 子串

		string substr(int pos = 0, int n = npos) const;	//返回从pos开始,长度为n的子串

	// 插入

		string& insert(int pos, const char* str);		//在pos位置插入
		string& insert(int pos, const string& str);		//在pos位置插入
		string& insert(int pos, int n, char c);	//在pos位置插入

	// 删除

		string& erase(int pos, int n = npos);		//在pos位置插入

# 两种转换

	string str1;
	const char* str2 = str1.c_str();
	
	const char* str3;
	string str4(str3);

# 神奇转换函数

	string to_ strinf(任何类型);		//将好多类型转换成string

*/

}
