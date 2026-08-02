# 自动环境部署

使用`requirements.txt`文件保存当前环境的第三方包,在新环境时可以一键部署

1. `pip freeze > requirements.txt` 保存项目环境
2. 转移到新环境,尽可能在venv虚拟环境中执行
3. `pip install -r requirements.txt` 自动部署环境
