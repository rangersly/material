#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
int main() {

	//第一种方法
	// int system(const char *command);
	// 创建一个子进程来执行
	system("/bin/ls -ls");

	
	//第二种方法
	// exec函数族
/*
	最主要两个exec函数
		int execl(const char *path, const char *arg, ...);
		int execv(const char *path, char *const argv[]);	//可以用argv[]来放参数,最后一个是0
*/
	execl("/bin/ls", "/bin/ls", "-ls", "/tmp", 0);	//最后的0不能省略
	//执行完后不返回
	//新进程的进程号与原来相同
	//新进程取代了原来的代码段，数据段，堆栈
	return 0;
}
