# 虚拟环境

使用python自带的虚拟环境管理工具`venv`

虚拟环境可以创造互不干扰的运行环境,独立的解释器,独立的第三方模块等

## 使用方法

确保安装了`python`和`pip`

`python -m venv .venv` 创建一个虚拟环境(在工作目录下运行)

安装`direnv` 用于自动激活虚拟环境

```
# 在指定项目下输入虚拟环境指令
cd ~/my_stc_project
echo "source .venv/bin/activate" > .envrc
# 授权
direnv allow
```

之后每一次进入该目录底下时都会自动启动虚拟环境
