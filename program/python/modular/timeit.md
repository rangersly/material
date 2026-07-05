# timeit

计时工具

## 核心API

|名称|作用|
|---|---|
|`timeit.timeit()`|精确测量一段语句的执行时间,返回总耗时|
|`timeit.repeat()`|多次调用`timeit`,返回耗时列表|
|`timeit.Timer`|面向对象接口|
|`timeit.default_timer`|当前平台最高精度计时器|

## 用例

**`timeit.timeit()`**

```
import timeit

t = timeit.timeit("sum(range(10000))", number=100000)
print(f'耗时{t:.4f}秒')

# or

def test():
    return sum(range(10000))
t = timeit.timeit(test, number=1000000)
print(f'耗时{t:.4f}秒')
```

**`timeit.repeat()`**

```
results = timeit.repeat("sum(range(100))", repeat=5, number=10000)
print(results)           # [0.023, 0.022, 0.023, ...]
```
