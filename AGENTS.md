# AGENTS.md

## 仓库性质

纯文档型中文知识库，不是软件项目。没有构建系统、测试、CI/CD 或 Lint 流程。不要尝试 `npm install`、`make`、`pytest` 等操作。

## 语言

所有内容使用中文。新增或修改文档时保持中文。

## 目录结构

- `linux/` — Linux 系统知识（ELF、proc、根目录结构、Arch Linux）
- `program/` — 编程资料（`c/`、`cpp/`、`python/`、`tool/`、`other/`）
- `tools/` — 第三方工具文档（Docker、Vim、SSH、Git、tmux 等）
- `windows/` — Windows 相关（WSL、快捷键、VBS 脚本）
- `hardware/` — 硬件知识（网线、硬盘）
- `algorithms/` — 算法实现
- `q-a/` — 基于问题的合集
- `other/` — 杂项
- `tmp/` — 未归纳资源暂存区

## 提交规范

使用 Conventional Commits 格式：

```
feat(scope) : 描述
fix(scope) : 描述
restruct(scope) : 描述
```

scope 对应目录名（如 `python`、`ssh`、`commands`）。描述用中文。

## 新增内容

1. 按主题放入对应目录
2. 在 `README.md` 的导航区添加链接
3. 参考同目录下已有文件的风格

## 注意事项

- `program/tool/clang/` 下的 `.clang-format` 和 `.clang-tidy` 是供读者参考的模板，不是本仓库的构建配置
- 代码示例（`.cpp`、`.c`、`.h`）仅用于说明，不属于可构建项目
- 唯一分支：`master`
- 仓库正在重构中，目录结构可能变动
