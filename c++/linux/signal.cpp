#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void func(int signum) {
	printf("接收到一个信号 %d\n",signum);
}

int main() {

	// 信号的处理
	//sighandler_t signal(int signum, sighandler_t handler):
	//						信号编号		处理函数
	//
	//	signal(1, SIG_DFL);	对信号1恢复默认处理方式
	//	signal(1, SIG_IGN);	对信号1忽略
	//
	//通过发送0的信号，可以检测程序是否存活

	signal(1, func);		//接受1的信号并使用func()处理	注意! func()不要加()

	alarm(5);			//闹钟, 5秒后向本程序发送14的信号,只有一次
	signal(14, func);

	// 信号的发送
	//int kill(pid_t pid, int sig);
	// pid > 0  	发送给进程号pid的进程
	// pid == 0		发给相同进程组的所有进程
	// pid = -1		广播给系统内所有进程
	


	while(1) sleep(1);
	return 0;
}
/*
	信号类型
	SIGHUP	1	A	挂起或控制进程终止
->	SIGINT 	2	A	C + c
	SIGFPE	8	C	浮点异常
->	SIGKILL	9	AEF kill -9 强制杀死
	SIGSEGV 11	C	无效的内存引用
	SIGPIPE 13	A	管道破裂
->	SIGALRM	14	A	闹钟alarm()信号
->	SIGTERM	15	A	kill默认
->	SIGCHLD 17	B	子进程结束

	A	终止进程
	B	忽略
	C	终止进程并core dump
	D	暂停
	E	不能捕获
	F	不可忽略
*/
