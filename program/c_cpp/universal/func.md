# c-cpp function

## 目录
- [extern](#extern)
- [noexcept](#noexcept)
- [重载](#)

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
