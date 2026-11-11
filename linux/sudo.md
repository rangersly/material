# sudo 与 sudoers 配置

`sudo` 让普通用户以其他用户(默认 root)的身份执行命令,权限由 `/etc/sudoers` 控制. 相比 `su` 切换到 root,它使用自己的密码、按命令授权,并留下日志.

## 常用命令

```bash
sudo <命令>              # 以 root 执行
sudo -u <用户> <命令>    # 以指定用户执行
sudo -i                  # 进入 root 登录 shell
sudo -l                  # 查看自己可执行的命令
sudo -k                  # 立即清除密码缓存
sudo -e <文件>           # 安全编辑文件(等价 sudoedit)
```

| 选项 | 作用 |
|---|---|
| `-u <用户>` | 指定执行身份,默认 root |
| `-g <组>` | 指定执行组 |
| `-i` | 登录 shell,加载完整环境 |
| `-s` | 非登录 shell |
| `-l` | 列出可用权限 |
| `-k` | 使密码时间戳失效 |
| `-e <文件>` | 安全编辑文件 |
| `-n` | 需要密码时直接失败,适合脚本 |
| `-E` | 保留当前环境变量 |

## sudoers 配置

**始终用 `visudo` 编辑**,它会在保存时检查语法,避免写坏导致 sudo 不可用.

```bash
sudo visudo                # 编辑 /etc/sudoers
sudo visudo -f /etc/sudoers.d/myconf   # 编辑指定文件
sudo visudo -c             # 检查语法
```

### 基本语法

```
用户 主机=(运行身份:组) 命令
```

```
root    ALL=(ALL:ALL) ALL
alice   ALL=(ALL) ALL
%wheel  ALL=(ALL) ALL          # 组要加 % 前缀
```

- 命令必须写绝对路径,如 `/usr/bin/systemctl`.
- 别名可简化重复配置:

```
User_Alias ADMINS = alice, bob
Cmnd_Alias SERVICES = /usr/bin/systemctl start nginx, /usr/bin/systemctl restart nginx

ADMINS ALL=(root) SERVICES
```

### 免密与常用 Defaults

```
alice ALL=(root) NOPASSWD: /usr/bin/systemctl restart nginx
```

```
Defaults timestamp_timeout=15          # 密码缓存分钟数,0 为每次都要
Defaults passwd_tries=3                # 密码尝试次数
Defaults secure_path="..."             # sudo 使用的 PATH
Defaults:alice timestamp_timeout=0     # 只对某个用户生效
```

> [!IMPORTANT]
> 通配符 `*` 可能匹配空格和路径分隔符,容易被绕过;能用 `sudoedit` 就不要用 `sudo vim`. 不要把 `NOPASSWD` 给 `ALL`.

### sudoers.d

推荐把自定义配置放到 `/etc/sudoers.d/`,主文件通过 `#includedir /etc/sudoers.d` 加载.

```bash
sudo visudo -f /etc/sudoers.d/deploy
sudo chmod 0440 /etc/sudoers.d/deploy
```

文件名不要带 `.` 或以 `~` 结尾,否则会被忽略.

## 日志

```bash
sudo journalctl _COMM=sudo
sudo journalctl _COMM=sudo --since today
```
