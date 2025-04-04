# cpp多线程
C++11引入了标准的线程库 `<thread>`，使得多线程编程更加方便和标准化

## 目录
- [创建线程](#)
- [线程的分离和结合](#)
- [传递参数给线程函数](#)
- [线程的同步](#)
  - [互斥锁](#mutex)
  - [lock-guard](#)
- [条件变量](#)
- [原子操作](#atomic)
- [高级接口](#高级接口)
- [线程池](#)

## 创建线程
通过 `std::thread` 类来创建和管理线程
```
    std::thread t(thread_function);  // 创建线程并执行 thread_function
    t.join();  // 等待线程结束
```

## 线程的分离和结合
+ `join()`：主线程等待子线程执行完毕。
+ `detach()`：将子线程与主线程分离，子线程在后台独立运行。

## 传递参数给线程函数
可以通过 `std::thread` 的构造函数传递参数给线程函数

`std::thread t(thread_function, 10, "Hello");`

## 线程的同步
多个线程访问共享资源时，可能会出现竞争条件（Race Condition）。为了避免这种情况，可以使用互斥锁（Mutex）来同步线程

### 互斥锁
`std::mutex` 用于保护共享资源，确保同一时间只有一个线程可以访问,`<mutex>`

```
std::mutex mtx; // 互斥量
void print_block() {
    mtx.lock();  // 锁定互斥锁
	// ...
    mtx.unlock();  // 解锁互斥锁
}
// in main ->
    std::thread t1(print_block, 50, '*');
    std::thread t2(print_block, 50, '$');
    t1.join();
    t2.join();
```

### lock-guard
`std::lock_guard` 是一个 RAII 风格的互斥锁管理类，它在构造时锁定互斥锁，在析构时自动解锁0

```
std::mutex mtx;
std::lock_guard<std::mutex> lock(mtx);
```

## 条件变量
条件变量用于线程间的同步，允许线程在某些条件不满足时等待，直到其他线程通知条件满足

`<condition_variable>`
```cpp
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready) {
        cv.wait(lock);  // 线程等待条件变量
    }
    std::cout << "thread " << id << '\n';
}
void go() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();  // 通知所有等待的线程
}
// main
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(print_id, i);
    }
    go();
    for (auto& th : threads) {
        th.join();
    }
```

## atomic
`std::atomic` 提供了原子操作，确保对共享变量的操作是不可分割的

## 高级接口

```cpp
void wait_s(time_t sec) {  // 延时函数
	std::cout << "BEGIN" << std::endl;
	time_t begin = time(0);
	while((time(0) - begin) < sec);
}
int main() {
	std::future<void> r1(std::async(wait_s, 10));
	// async let `a piece of functionality` run in alone thread

	wait_s(10);
	r1.get();  // 获得返回值,确保必将被调用

	std::cout << "END" << std::endl;
	return 0;
}
```

## 线程池
通过 `std::thread` 和任务队列来实现一个简单的[线程池](../library/thread-pool.cpp)

//	thread类
//	1.
//		thread() noexcept;默认构造函数，不执行任何任务
//	2.
//		template<class Funtion, class ...Args>
//		explicit thread(Function&& fx,Args&&... args);

	if(t1.joinable())	// 判断能否调用join
		t1.join();		//回收线程t1
//		t1.detach();	//分离线程
	return 0;
}

__注：g++编译器要加 -pthread -std=c++11选项编译__
