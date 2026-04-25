#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;
int main() {

//	int shmget(key_t key, size_t size, int shmflg); 创建/获取 共享内存
//	key 共享内存的键值	size 待创建的大小	shmflg 访问权限(同文件权限) IPC_CREAT 若无则创建
//	成功返回共享内存的ID
	int shmid;
	shmid = shmget(0x5005, 400, 0666|IPC_CREAT);
	cout << shmid << endl;
	if(shmid == -1) cout << "创建失败" << endl;
//	使用ipcs命令查看系统的共享内存
//	ipcrm -m [id]	删除共享内存

//	void *shmat(int shmid, const void *shmaddr, int shmflg); 连接到当前进程空间
//		shmid  shmget()的返回值
//		shmaddr 连接位置，通常写0，让系统决定
//		shmflg 标志位 0
//		成功时返回地址
//
//	shmdt(const void *shmaddr);	分离共享内存
//
//	shmctl(shmid, IPC_RMID, 0);	删除共享内存

	int *arr;
	arr = (int *)shmat(shmid, 0, 0);
	if(arr == (void *)-1) cout << "shmat error" << endl;
	cout << arr[0] << endl;
	arr[0] = 1234;
	shmdt(arr);

	return 0;
}
