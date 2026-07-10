# ssh

远程连接工具

- [快捷连接配置](#config)
- [隧道转发](#隧道转发)
- [密钥登录](#密钥登录)

## 隧道转发


### 远程隧道转发

SSH的 **远程隧道转发** ,俗称反向隧道,作用是让远程服务器访问到本地电脑上的某个服务

#### 核心语法
```
ssh -R [远端绑定地址:]远端端口:本地地址:本地端口 用户名@远端服务器IP
```
#### 内网穿透案例

假设在本地电脑运行一个服务在8080端口上,想要让没有公网IP的它可以通过一台公网VPS被外界访问

```bash
ssh -R 9090:localhost:8080 root@1.2.3.4
```

执行后建立了 **服务器** 到 **本地电脑** 的隧道,服务器可以通过`curl localhost:9090`访问到服务

但这一步并没有开放服务器的对外监听,需要启动服务器对外开放

解决方案 : 在服务器的`/etc/ssh/sshd_config`中添加`GatewayPorts yes`,重启服务

或者显式绑定到监听地址 : `ssh -R 0.0.0.0:9090:localhost:8080 root@1.2.3.4`

#### 进阶参数

|参数|作用|
|`-N`|不远程登录,仅做转发|
|`-f`|认证通过后转后台运行|

## 密钥登录

SSH免密登录是一种使用SSH协议进行身份验证的方法，它允许用户在不输入密码的情况下登录远程服务器。以下是实现SSH免密登录的基本步骤：
1. **生成密钥对**：
   - 使用`ssh-keygen`命令生成一对公钥和私钥。例如：
	ssh-keygen -t rsa -b 4096
2. **复制公钥到远程服务器**：
   - 使用`ssh-copy-id`命令将公钥复制到远程服务器。例如：
		     `ssh-copy-id user@remote_host`
     - 这将自动将你的公钥添加到远程服务器的`~/.ssh/authorized_keys`文件中。
3. **配置SSH客户端**：
   - 确保你的SSH客户端配置文件`~/.ssh/config`正确设置，以便使用私钥进行身份验证。例如：
4. **禁用密码登录**:
   - `/etc/ssh/sshd_config`
   - 设置PasswordAuthentication no
5. **测试免密登录**：
6. **注意事项**：
   - 确保远程服务器的SSH服务配置允许密钥认证。通常在`/etc/ssh/sshd_config`文件中设置。
   - 确保本地和远程的SSH配置文件没有错误，并且权限设置正确。

遇到任何问题，可以查看SSH的日志文件或使用`-v`参数进行调试
- `ssh -v user@remote_host`

## config

放在客户端的`.ssh/config`,可以实现以别名快速连接

```
Host iaalai
 HostName api.iaalai.cn			#连接地址
 User e0x1a						#连接用户名
 Port 20022						#连接端口
 IdentityFile ~/.ssh/id_rsa		#密钥地址
 IdentitiesOnly yes				#仅使用密钥
 ServerAliveInterval 60 		#每60s发一个空包保持连接
 ServerAliveCountMax 3			#3次未响应断开
```
