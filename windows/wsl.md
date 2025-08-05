# **wsl使用记录**

---

## **开始之前**

1. **启用wsl**

```powershell
# 启用 WSL
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

# 启用虚拟机平台
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# 更新wsl
wsl --update
```


2. **wsl2为默认版本**

```powershell
wsl --set-default-version 2
```


3. **导入镜像**

```powershell
wsl --import Ubuntu-22.04 C:\WSL\Ubuntu2204 ubuntu-22.04-server-cloudimg-amd64-wsl.rootfs.tar.gz
```

---

## **配置**

1. wsl.conf
```
# 设置默认登录用户
[user]
default = username

# 网络配置
[network]
hostname = MyWSL

# 避免windows和wsl互干扰
[interop]
enabled = false
appendWindowsPath = false
```

---

## **选项**

- `--list --online` - 查找可用的分发版
- `-l -v` - 列出已安装的分发版
- `--set-version <name> <Number>` - 设置wsl版本
- `--status` - 状态
- `--export <Name> <FileName>` - 导出
- `--import <Name> <InstallLocation> <FileName>` - 导入
- `--unregister <Name>` - 注销,以便清理
- `-d <Name> -u <user_name>` - 启动
