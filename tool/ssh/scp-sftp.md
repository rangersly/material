# **scp-sftp**

---

## **scp**

- `-r` 递归复制目录
- `-p` 保留文件属性
- `-C` 压缩传输
- `-P` 指定端口
- `-l` 限速传输(Kbit.s)

---

## **sftp**

- `-P` 端口

### **交互命令**

|命令|说明|
|----|----|
|`ls`|远端ls|
|`lls`|本地ls|
|`cd`|同|
|`lcd`|同|
|`pwd`||
|`lpwd`||
|`get`|下载文件|
|`put`|上传文件|
|`mkdir`||
|`rmdir`||
|`rm`||
|`chmod`||
|`chown`||
|`exit`||
|`mget`|多个文件|
|`reget`|断点续传|
|`reput`||
