#include <iostream>
#include <time.h>		// 时间函数库
#include <unistd.h>		//程序睡眠函数库

using namespace std;
int main() {
	time_t t1;		//存放时间类型的类型	typedef long time_t
	
	// time() 获取当前时间
	// 原型 time_t time(time_t *tloc)
	t1 = time(0); // == time(&t1);

	/*
		struct tm {
			int tm_year;
			int tm_mon;
			int tm_mday;
			int tm_hour;
			int tm_min;
			int tm_sec;
			int tm_wday;
			int tm_yday; 	从每年1.1开始算
			int tm_isdst;
		}

		struct tm * localtime(const time_t *time) 		把time_t转换成tm结构体
		struct tm * localtime_r(const time_t *time, struct tm *result)	线程安全
		
		time_t mktime(struct tm *tm);	把tm转换成time_t
	*/

	// 程序睡眠
	unsigned int sleep(unsigned int seconds);	//单位s
	int usleep(useconds_t usec);		//微妙
	
	return 0;
}
