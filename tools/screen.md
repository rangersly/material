# screen 终端复用工具

保持会话在后台运行，断开连接后任务不中断；功能更强的现代替代品是 [tmux](./tmux.md)。

## 会话

- `screen -S name` 新建命名会话
- `Ctrl+A D` 分离会话，任务继续运行
- `screen -ls` 列出会话
- `screen -r name` 恢复会话；状态为 Attached 时用 `screen -d -r name` 强制接管

## 窗口与分屏

前置键均为 `Ctrl+A`：`c` 新建窗口，`n`/`p` 或数字切换；`S` 水平分屏，`|` 垂直分屏，`Tab` 切屏，`Q` 关闭分屏；`k` 关闭窗口。

## 其他

- `Ctrl+A [` 进入复制模式，方向键选择，`Enter` 复制
- 配置文件为 `~/.screenrc`
