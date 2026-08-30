# ssh

远程连接工具

- [快捷连接配置](#快捷连接配置)
- [密钥登录](#密钥登录)
- [服务端配置](#服务端配置)
- [隧道转发](#隧道转发)

## 快捷连接配置

放在客户端的 `.ssh/config`，可以实现以别名快速连接：

```
Host iaalai
 HostName api.iaalai.cn			# 连接地址
 User e0x1a						# 连接用户名
 Port 20022						# 连接端口
 IdentityFile ~/.ssh/id_rsa		# 密钥地址
 IdentitiesOnly yes				# 仅使用密钥
 ServerAliveInterval 60 		# 每60s发一个空包保持连接
 ServerAliveCountMax 3			# 3次未响应断开
```

## 密钥登录

SSH 免密登录允许用户在不输入密码的情况下登录远程服务器，步骤如下：

1. **生成密钥对**

   ```bash
   ssh-keygen -t rsa -b 4096
   ```

2. **复制公钥到远程服务器**

   ```bash
   ssh-copy-id user@remote_host
   ```

   该命令会自动将公钥添加到远程服务器的 `~/.ssh/authorized_keys` 中。

3. **测试免密登录**

   ```bash
   ssh user@remote_host
   ```

   无需输入密码即登录成功。

4. **禁用密码登录（服务端）**

   编辑 `/etc/ssh/sshd_config`：

   - `PubkeyAuthentication yes` 启用密钥登录
   - `PasswordAuthentication no` 禁用密码登录

   修改后重启 sshd 服务生效。

### 注意事项

- 确保远程服务器 SSH 配置允许密钥认证（`/etc/ssh/sshd_config`）
- 本地与远程 SSH 文件权限需正确：`~/.ssh` 为 `700`，`authorized_keys` 为 `600`
- 排查问题时查看 SSH 日志，或用 `-v` 调试：`ssh -v user@remote_host`

## 服务端配置

服务端配置文件为 `/etc/ssh/sshd_config`，修改后用 `sshd -t` 检查语法，再重启 sshd 生效。

### 安全加固

|配置项|作用|
|---|---|
|`PermitRootLogin no`|禁止 root 直接登录；如需密钥登录可设 `prohibit-password`|
|`PasswordAuthentication no`|禁用密码登录，仅允许密钥认证|
|`PubkeyAuthentication yes`|确保启用公钥认证|
|`PermitEmptyPasswords no`|禁止空密码账户登录|
|`MaxAuthTries 3`|单次连接最多认证尝试次数，防暴力破解|
|`MaxStartups 30`|未认证并发连接数上限，超过后拒绝，防爆破/DoS|
|`LoginGraceTime 60`|认证超时秒数，超时断开连接|
|`AllowUsers user1 user2`|仅允许指定用户登录|
|`AllowGroups sshusers`|仅允许指定组登录|

### 连接空闲与心跳

|配置项|作用|
|---|---|
|`ClientAliveInterval 60`|每隔 60s 发心跳包探测连接是否存活|
|`ClientAliveCountMax 3`|心跳连续 3 次无响应则断开（配合上面可清理僵尸连接）|

### 检查配置与重启

```bash
sshd -t                            # 语法检查
systemctl restart ssh            # 重启 SSH 服务
```

### 注意事项

- 修改配置前先备份：`cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak`
- 禁止 root 登录前务必确保有其他可用账户，否则可能把自己锁在服务器外
- 云服务器需同步在安全组/防火墙放开对应端口

## 隧道转发

### 远程隧道转发

SSH 的**远程隧道转发**，俗称反向隧道，作用是让远程服务器访问到本地电脑上的某个服务。

#### 核心语法

```
ssh -R [远端绑定地址:]远端端口:本地地址:本地端口 用户名@远端服务器IP
```

#### 内网穿透案例

假设本地电脑在 8080 端口运行一个服务，想让没有公网 IP 的它通过一台公网 VPS 被外界访问：

```bash
ssh -R 9090:localhost:8080 root@1.2.3.4
```

执行后建立了**服务器**到**本地电脑**的隧道，服务器可通过 `curl localhost:9090` 访问该服务。

但这一步并未开放服务器的对外监听，需要让服务器对外开放：

- 在服务器 `/etc/ssh/sshd_config` 中添加 `GatewayPorts yes`，重启服务
- 或显式绑定监听地址：`ssh -R 0.0.0.0:9090:localhost:8080 root@1.2.3.4`

#### 进阶参数

|参数|作用|
|---|---|
|`-N`|不远程登录，仅做转发|
|`-f`|认证通过后转后台运行|
