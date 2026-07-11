# opencode

智能体编程工具

- [安装](#安装)

## 安装

### npm

- 先安装 `npm`
- `sudo npm i -g opencode-ai` 安装opencode

### archlinux

- `sudo pacman -S opencode` (Stable)
- `paru -S opencode-bin` (Latest from AUR)

## 常用命令

|命令|作用|
|---|---|
|`/init`|初始化项目,创建`AGENTS.md`|
|`/undo`|撤销修改|
|`/redo`|重做修改|
|`/share`|分享对话(链接自动复制到粘贴板)|
|`/new`|开始一个新的会话|
|`/sessions`|列出并切换不同的会话|
|`/export`|将对话导出成Markdown文件|
|`/models`|列出可用的模型|
|`/compact`|压缩上下文|
|`/connect`|配置服务提供商和API|

## 使用技巧

按`<TAB>`可以切换计划模式 (只给出建议不修改), 可以补充一些细节

可以拖拉图片到终端中即可添加到提示词中
