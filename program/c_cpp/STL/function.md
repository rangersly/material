# function 包装器

提供更加一致的接口，避免多次实例化

对于调用特征标(call signature)一样的函数，使用function进行包装

```cpp
std::function<double(int)> fun1;
```
+	可接受任何函数指针，函数对象，lambda表达式

```cpp
template <typename T>
void print(T f, int a) {
	std::cout << f(a) << std::endl;
}

double f1(int a) {
	return a/1.0;
}

std::function<double(int)> fun1=f1;
print(fun1, 10);
```
