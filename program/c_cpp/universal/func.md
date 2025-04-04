# c-cpp function

## 目录
- [extern](#extern)
- [noexcept](#noexcept)
- [重载](#)
- [often](#often)

## extern

`exterm` 表明函数在外部定义,在链接期才去查找
`extern "C"` 表明以C的方式查找外部函数

## noexcept

```cpp
void myFunction() noexcept {
    // 这个函数不会抛出异常
}
```
noexcept 的一个重要用途是优化性能，特别是在移动语义中。当一个函数被标记为 noexcept 时，编译器可以更积极地优化代码

## 重载
只要特征标不同就可以重载
**特征标**:原型除去返回值都是

+ 左值：优先选择T&，如果不可用则选择const T&。
+ const左值：选择const T&。
+ 右值：优先选择T&&, else const T&
+ 字面量或临时对象：选择T&&。

## often

```
abs(x);		//求x的绝对值	e.g.abs(-5)=5
fabs()		//实数绝对值
exp(x);		//求x的自然指数e^x	e.g.exp(1)=2.718282
floor(x);	//向下取整
ceil(x);	//向上取整
log(x);		//求实数x的自然数对数 	e.g.log(1)=0
pow(x,y);	//计算x^y,输出为双精度实数		e.g.pow(2,3)=8
sqrt(x);	//求x的平方根	e.g.sqrt(25)=5
strlen(str);获取字符数组长度(只能用在字符数组）。
max(a,b)	//两数中最大
min(a,b)	//两数中最小
swap(a,b)	//交换两个类型相同的变量
```
