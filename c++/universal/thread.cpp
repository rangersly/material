#include <iostream>
#include <thread>

using namespace std;
void func(int a) {
	cout << a << endl;
}

mutex mtx;	// 互斥量

int main() {

//	同一个进程的多个线程共享该进程的全部系统资源
//	但各个线程有自己的调用栈，寄存器，本地存储

//	thread类
//	1.
//		thread() noexcept;默认构造函数，不执行任何任务
//	2.
//		template<class Funtion, class ...Args>
//		explicit thread(Function&& fx,Args&&... args);

	thread t1(func, 1);		//用2方法创建线程

//	mtx.lock();
//	mtx.unlock();


	if(t1.joinable())	// 判断能否调用join
		t1.join();		//回收线程t1
//		t1.detach();	//分离线程
	return 0;
}

//	注：g++编译器要加 -pthread -std=c++11选项编译
