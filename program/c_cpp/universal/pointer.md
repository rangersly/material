# c-cpp的指针问题

## 目录

- [NULL and nullptr](#NULL-nullptr)
- [cpp智能指针](#cpp智能指针)
  - [注意事项](#注意事项)
  - [some example](#some-example)

## NULL-nullptr

在C和CPP中,NULL并不相同

```
#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif
```

由源码可知, C中 `NULL` 为 `(void *)0`, 而cpp中视为整形常量

因此cpp中应使用nullptr,否则函数重载中会出现选择错误问题

## cpp智能指针

1. `std::unique_ptr`

表示独占所有权的指针，即同一时刻只能有一个`unique_ptr`指向某个对象。

 * 不可复制（没有拷贝构造函数和拷贝赋值运算符）。
 * 可以移动（支持移动语义）。
 * 自动释放资源。

**由于不可复制，不能将unique_ptr存储在标准容器中(如std::vector)**

```
std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>(42); // 创建unique_ptr
std::unique_ptr<MyClass> ptr2 = std::move(ptr1); // 移动所有权
ptr1 = nullptr; // ptr1不再指向对象，对象由ptr2管理
```

2. `std::shared_ptr`

表示共享所有权的指针，多个`shared_ptr`可以指向同一个对象

 * 使用引用计数来管理对象的生命周期。
 * 当最后一个`shared_ptr`被销毁时，对象才会被释放。
 * 可以复制
 * 引用计数可能会引入性能开销，尤其是在多线程环境中。
 * 如果存在循环引用（如双向链表），可能导致内存泄漏。需要使用`std::weak_ptr`来解决。

```
std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(42);
std::shared_ptr<MyClass> ptr2 = ptr1; // 复制，引用计数加1
std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; // 输出2
```

3. `std::weak_ptr`

解决`shared_ptr`的循环引用问题

 * 不增加引用计数。
 * 可以通过lock()方法获取一个`shared_ptr`，但需要检查对象是否仍然存在
 * `weak_ptr`不能直接访问对象，需要通过lock()方法转换为`shared_ptr`。
 * 如果对象已经被销毁，lock()会返回一个空的`shared_ptr`

### 注意事项

***循环引用问题***

`std::shared_ptr`通过引用计数来管理对象的生命周期。当最后一个`shared_ptr`被销毁时，引用计数归零，对象才会被释放。然而，如果两个或多个`shared_ptr`相互引用，引用计数将永远不会归零，因为它们相互持有对方的引用。

> example:双向链表中的循环引用
```
struct Node {
    std::shared_ptr<Node> next;  // 指向下一个节点
    std::shared_ptr<Node> prev;  // 指向前一个节点
};
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2;  // node1 持有 node2 的共享所有权
    node2->prev = node1;  // node2 持有 node1 的共享所有权
```

为了解决循环引用问题，C++标准库提供了`std::weak_ptr`。`std::weak_ptr`是一种弱引用，它不会增加引用计数，但可以指向一个由`std::shared_ptr`管理的对象

```
struct Node {
    std::shared_ptr<Node> next;  // 指向下一个节点
    std::weak_ptr<Node> prev;    // 使用 weak_ptr 指向前一个节点
};
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2;  // node1 持有 node2 的共享所有权
    node2->prev = node1;  // node2 使用 weak_ptr 指向 node1
```

如果对象仍然存在，lock()返回一个指向对象的`std::shared_ptr` 如果对象已经被销毁，lock()返回一个空的`std::shared_ptr`


__正确选择智能指针类型__

> 如果对象的所有权是唯一的，使用`std::unique_ptr`
> 如果对象的所有权需要共享，使用`std::shared_ptr`
> 如果需要解决循环引用问题，使用`std::weak_ptr`

### some-example

```
#include <iostream>
#include <memory>
#include <algorithm> // 用于 std::fill
int main() {
    // 使用 std::unique_ptr 管理1000个 int 的内存空间
    std::unique_ptr<int[]> data = std::make_unique<int[]>(1000);

    // 初始化数据
    std::fill(data.get(), data.get() + 1000, 42); // 将所有元素初始化为42
	// data.get()返回底层指针，可以用于标准库算法（如std::fill）

    // 访问并打印部分数据
    for (int i = 0; i < 10; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    // 当 unique_ptr 超出作用域时，内存会自动释放
    return 0;
}
```
```
#include <iostream>
#include <memory>
#include <algorithm> // 用于 std::fill
int main() {
    // 使用 std::shared_ptr 管理1000个 int 的内存空间
    std::shared_ptr<int[]> data(new int[1000]); // 使用 new[] 分配内存
	// ***std::shared_ptr<int[]>需要显式使用new[]分配内存***

    // 初始化数据
    std::fill(data.get(), data.get() + 1000, 42); // 将所有元素初始化为42

    // 访问并打印部分数据
    for (int i = 0; i < 10; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    // 当最后一个 shared_ptr 超出作用域时，内存会自动释放
    return 0;
}
```
