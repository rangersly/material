# 模板

## index
- [函数模板](#)
  - [生成](#)
- [类模板](#)
- [完美转发](#)
- [可变参数](#可变参数)

## 函数模板
```cpp
template <typename T>
void swap(T &a, T &b);
```
__函数模板必须放在编译器可见的地方里，因为不是函数实体，只能算编译指令__

### 生成
**隐式实例化**
```cpp
int a=0, b=3;
swap<int>(a, b);
```
**显式实例化**
```cpp
template void swap<int>(int&, int&);	// 使用模板生成int类型的函数定义
```
**显式具体化** 这个可以放到其他文件里，因为是有实体的
```cpp
template <> void swap<int>(int&, int&);
```

###	类型推导
+	decltype()
```cpp
int a;
decltype(a) var;
```

##	类模板
同样没有实体，包括类成员方法等都要写成模板的格式

## 完美转发
- [右值引用](./class.md#):有关完美转发的基础
完美转发允许模板函数将参数原封不动地转发给另一个函数，保留其左值或右值的性质。这在编写通用代码时非常有用，例如模板库或函数包装器

完美转发的核心是std::forward，它根据模板参数T的类型（左值引用或右值引用）来决定如何转发参数

```
template <typename T>
void wrapper(T&& arg) {
    // 转发 arg 到另一个函数，保留其左值或右值性质
    targetFunction(std::forward<T>(arg));
}
```

## 可变参数

```
void print() {}   // 终止递归
template <typename T, typename... Types)
void print(const T& firstArg, const Types&... args) {
	std::cout << firstArg << std::endl;
	print(args...);
}
```
