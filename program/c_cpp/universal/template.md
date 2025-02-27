# 模板

## 函数模板

### 基本格式

```cpp
template <typename T>
void swap(T &a, T &b) {
	T temp;
	temp = b;
	b = a;
	a = temp;
}
```
__函数模板必须放在头文件里，因为它不是函数实体，只能算编译指令__

###	模板的几个术语
+	**隐式实例化**
```cpp
int a=0, b=3;
swap<int>(a, b);
```
+	**显式实例化**
```cpp
template void swap<int>(int&, int&);	// 使用模板生成int类型的函数定义
```
+	**显式具体化**
```cpp
template <> void swap<int>(int&, int&);
```
__这个可以放到其他文件里，因为是有实体的__

###	类型推导
+	decltype()
```cpp
int a;
decltype(a) var;
```

##	类模板

+	同样没有实体，包括类成员方法等都要写成模板的格式
