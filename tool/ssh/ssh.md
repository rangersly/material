# ssh 隧道转发
-	本地转发
	+	本地端口转发到远端服务器
	+	`ssh -L local_port:remote_host:remote_port user@ssh_server`

-	远程转发
	+	远程转发到本地
	+	`ssh -R remote_host:local_host:local_port user@ssh_server`




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

# ssh:  config 文件
```config
Host iaalai
 HostName api.iaalai.cn			#连接地址
 User e0x1a						#连接用户名
 Port 20022						#连接端口
 IdentityFile ~/.ssh/id_rsa		#密钥地址
 IdentitiesOnly yes				#仅使用密钥
 ServerAliveInterval 60 		#每60s发一个空包保持连接
 ServerAliveCountMax 3			#3次未响应断开
```
