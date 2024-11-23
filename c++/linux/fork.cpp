#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main() {

//	进程标识(pid)
//	pid_t getpid(void);		当前进程
//	pid_t getppid(void);	父进程

//	fork()	函数
//	pid_t fork(void);	创建一个子进程,父进程返回pid，子进程返回0
//	子进程获取父进程 数据空间,堆,栈 的副本，并不是共享
//	若父进程比子进程先退出，那么子进程由1号进程托管
//	若子进程先退出，而父进程没处理，则会造成僵尸进程(No!)

	pid_t pid;
	pid = fork();	//创建一个子进程
	if(pid != 0) cout << "是父进程" << getpid() << endl;
	else if(pid == 0) cout << "是子进程" << getpid() << endl;
	else cout << "进程创建失败" << endl;

//	僵尸进程的避免
//	1.
//		signal(SIGCHLD, SIG_IGN);	忽略子进程退出的信息，交由系统处理
//
//	2.	使用wait()/waitpid() 阻塞等待子进程结束
//		pid_t wait(int *stat_loc);		返回子进程pid
//		pid_t waitpid(pid_t pid, int *stat_loc, int options);
//
//		stat_loc是进程终止的信息
//		a. 正常终止 WIFEXITED(stat_loc) 返回真 WEXITSTATUS(stat_loc)获取终止信息
//		b. 异常终止 WTERMSIG(stat_loc) 获取终止进程的信号
//
//	3.	收到SIGCHLD信号后wait()	相当于非阻塞,不影响父进程
	if(pid != 0) {
		int status;
		pid = wait(&status);
		cout << "进程" << pid;
		if(WIFEXITED(status)) cout << "正常终止" << endl;
		else cout << "被" << WTERMSIG(status) << "信号异常终止" << endl;
	} else sleep(100);


	return 0;
}
//	当使用fork创建子进程时，子进程会继承父进程的资源
/*
	1. **文件描述符**：子进程会继承父进程打开的所有文件描述符。这意味着子进程可以访问父进程打开的文件和设备。
	2. **环境变量**：子进程继承父进程的环境变量，包括语言设置、路径变量等。
	3. **内存空间**：子进程会复制父进程的地址空间，包括代码段、数据段和堆栈。但是，子进程的堆栈是独立的，这意味着局部变量和函数调用栈是分开的。
	4. **信号处理器**：子进程继承父进程的信号处理器设置。
	5. **挂起信号集**：子进程继承父进程的挂起信号集。
	6. **资源限制**：子进程继承父进程的资源限制，如CPU时间、文件大小限制等。
	7. **进程组ID**：子进程继承父进程的进程组ID。
	8. **用户ID和组ID**：子进程继承父进程的用户ID和组ID。
	9. **工作目录**：子进程继承父进程的工作目录。
	10. **根目录**：子进程继承父进程的根目录。
	11. **能力**：子进程继承父进程的文件系统能力。
	12. **内核定时器**：如果父进程有设置内核定时器，子进程也会继承。
	13. **锁**：子进程继承父进程持有的文件锁。
	14. **共享内存段**：如果父进程使用了共享内存，子进程也会继承这些共享内存段。
	然而，有一些资源是独立的，例如：
	- **进程ID**：子进程有自己的唯一进程ID。
	- **线程特定数据**：每个线程有自己的线程特定数据，子进程不会继承父进程的线程特定数据。
	- **CPU寄存器**：除了程序计数器和其他一些寄存器外，子进程的CPU寄存器状态是复制自父进程的，但子进程可以独立修改它们。
*/
