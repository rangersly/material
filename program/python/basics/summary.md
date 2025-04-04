# python基础合集

## 目录

- [程序之始](#run)
- [IO](#IO)
  - [格式化输出](#)
- [字符串](#string)
- [DEBUG](#Debug)
- [变量](#)
  - [数值类型](#)

## run

`if __name__ == '__main__'` 判断程序是否在主函数内(区别与模块等)

## IO

`print(values, sep, end)` 值, 分割符, 结尾符
> `print("hello", sep=',', end='_')`
> `print('%8d'%a1, '\n')`

a1 = int(input("input:"))        #    input
a, b = map(int, input().split()) # 读取输入分割并转化

### 格式化输出
1. 占位符
+ `%`
+ `format()`
+ `格式化f`

> example
`print("%4d" % a)`


## string

字符串可以用单引号或者双引号

三引号可以跨行

> example
```python
print('''Hello
world''')
```

```
s = str("Hello world")
print(s[3])        
print(s[-3])
print(s[0:3])    # 字符串切片
print(s[3:])
print(s[:5])
print(s[:-5])
print(s[::-1])    # 倒序
len(s)        # 计算长度

s.find('w')
s.count('l')

s.replace('H','h') # H变成h
s.casefold()        # 大写转小写
s.upper()            # 小写转大写
s.swapcase()        # 转换大小写
eval('12+3')        # 计算值 返回15
```

## Debug

1. pdb
`import pdb; pdb.set_trace()` 程序运行到这行代码时会进入调试模式
 + n（next）：执行下一行代码。
 + c（continue）：继续运行直到遇到下一个断点。
 + q（quit）：退出调试。
 + p <变量>：打印变量的值。
 + l（list）：显示当前代码上下文。
 + b <行号>：设置断点。
 + cl（clear）：清除断点。
```
def add(a, b):
    import pdb; pdb.set_trace()    # 从这里进入断点调试
    return a + b
print(add(3,5))
```

## 变量
name = value

### 数值类型
+ int
+ float
+ bool  True = 1   False = 0
+ complex
+ [str](#string)

type()
