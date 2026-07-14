# 异常

## 处理异常

- **try-except** 语句

```python
try:
    检测范围
except [异常名expression [as 异常信息identifier]]:
    异常处理代码
[else:
    没有触发异常的]
[finally:
    收尾工作]
```

## 抛出异常

- `raise [异常名expression(异常注释)]`
- 调试期异常 `assert True` 抛出一个 `AssertionError` 异常
