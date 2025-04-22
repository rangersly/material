# 动态内存分配

---

## INDEX

- [C](# C)
  - [malloc](# malloc)
  - [calloc](# calloc)
  - [realloc](# realloc)
  - [free](#) : 传入动态分配的指针地址,记得释放完赋NULL
- [CPP](# CPP)
  - [new](# new)
  - [delete](# delete)

---

## C

所有的函数声明于`<stdlib.h>`头文件中

---

### **malloc**

- 原型 `void *malloc(size_t size);`
- 功能 : 用于分配指定字节数的内存块
- 特点
  - 分配的内存是未初始化的，内容随机
  - 返回指向分配内存起始地址的void指针
  - 如果分配失败，返回NULL

---

### **calloc**

- 原型 `void *calloc(size_t num, size_t size);`
- 特点
  - 比起 `malloc` 多了自动初始化

---

### **realloc**

- 原型 `void *realloc(void *ptr, size_t new_size);`
- 功能 : 用于调整之前分配的内存块的大小
- 特点
  - 可以扩大或缩小内存块
  - 新增部分不初始化
  - 如果ptr为NULL，等同于malloc
  - 可能返回新的指针地址（内存块可能被移动到新位置）
  - 如果`new_size`为0且ptr不为NULL，等同于free
