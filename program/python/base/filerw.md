# 文件读写

## 打开文件

- `open('文件名', '文件模式'[, encoding='utf-8'])`

|文件模式|含义|
|---|---|
|r|只读,文件必须存在|
|w|写入,清空已有内容,不存在创建|
|a|追加,不清空|
|x|新建写入,存在报错|
|b|二进制模式,如`rb` `wb`|

> [!WARNING]
> 不安全的打开文件,容易产生资源泄露和文件锁定

```python
f = open('filename')
f.readline()
f.close()
```

> [!IMPORTANT]
> 安全的方式,自动管理,抛异常也能正常关闭

```python
with open('filename') as f:
    content = f.read()
```

## 写入文件

- `f.write(text, /)` 将字符串写入文件对象中
- `f.writable()` 判断对象是否具有写入功能

## 读取文件

- `f.read(size=-1, /)` 读取指定数量的字符,EOF停止, 未指定时读取所有字符
- `f.readable()` 是否有读取能力

## 其他文件对象的方法

- `f.tell()` 返回文件指针在文件对象中的位置
- `f.seek(offset, whence=0, /)` 修改文件指针的位置,从 `whence` 指定的位置(0-起始, 1-当前, 2-末尾) 偏移 `offset` 个字节,返回新的索引位置

## pickle

将python对象序列化(转换为二进制流)

- 使用 `import pickle` 导入
- 保存的文件后缀使用`.pkl`, 必须使用二进制模式打开

```python
import pickle
with open('data.pkl', 'wb') as f:
    pickle.dump([2,6,7,1,0], f)  # 写入内容 
    x = pickle.load(f)  # 读取内容
```
