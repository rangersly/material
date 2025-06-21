# git
工作树  --  暂存区  --  本地仓库  --  远端仓库

## index
- [config](#config)
- [status]() : 查看当前仓库状态
- [init](#init) : 创建仓库
- [add](#add) : 加入文件到暂存区
- [commit](#commit) : 提交
- [log](#log) : 日志
- [diff]() : 对比差异
- [reflog]() : 历史操作
- [branch](#branch) : 分支
- [switch](#switch) : 切换分支
- [merge](#merge) : 合并
- [reset](#reset) : 回滚
- [revert]() : 反commit
- [rebase](#rebase) : 变基
- [stash](#stash) : 暂存
- [clone]()
- [remote](#remote) : 远程仓库
- [pull](#pull) : 拉取并覆盖
- [fetch](#fetch) : 拉取不覆盖
- [tag](#tag) : 打标签
- [worktree](#worktree) : 签出多个分支
- [](#)

---

## config
- `git config --global` : 配置全局环境
  - `user.name` : 用户名
  - `user.email` : 用户邮箱
  - `core.editor "vim"` : 设置全局编辑器为vim

---

## init
- `--bare <code.git>` : 创建没有工作树的仓库

---

## commit
- `类型(模块):主题`

|类型|说明|
|----|------|
|feat|新功能|
|fix|Debug|
|refactor|重构|
|docs|改文档|
|style|改风格|
|test|加改测试|
|chore|杂项|
|perf|性能优化|
|build|改构建|
|revert|回滚|

---

## add
- `-n` : 演习
- `*` :	所有 新建的，删除的，修改的
- `.` :	新建的，修改的
- `-u` : 更新已追踪
- `-f` : 允许添加忽略的文件
- `-A, --all` : 添加所有已跟踪和未跟踪

---

## log
- `-a`查看所有分支的提交记录
- `--stat`详细	
- `--pretty=[short/oneline]`特殊显示
- `--graph`更直观
- `--after="YYYY-MM-DD"`指定日期
- `--before="YYYY-MM-DD"`指定日期
- `--author="xxx"`特定作者提交
- `origin/master`远端仓库日志
- `文件/目录`单独追踪

---

## branch
- `-avv`查看全部分支信息
- `-d/D`删除分支
- `-m/M`修改主分支
- `-u <remote>/<branch>`设置追踪关系
- `--merged`列出所有已合并到当前分支的分支
- `--no-merged`未合并

---

## switch
- `-c`创建并切换分支

---

## merge
- `--no-ff`记录合并
- `--squash`分支合并为一个提交进行合并
- `--abort`出现冲突，终止合并
- `-m <message>`提交信息
- `--edit`合并提交前，允许编辑提交信息

---

## reset
- `--hard HEAD~1`撤销最后一次commit 本地仓库 and 暂存区 and 工作树
- `HEAD~1`撤销最后一次commit 仅本地仓库 and 暂存区
- `--soft HEAD~1`撤销最后一次commit 仅本地仓库

---

## rebase
- `<basebranch>`					#将当前分支更改应用到<basebranch>分支上
- `-i` 								#压缩历史 交互式变基
- `# -i HEAD~N`						#回退N次提交
- `--onto <newbase> <branch>`		#将<branch>分支变基到<newbase>上
- `--abort`							#当冲突时撤销合并
- `--continue`						#继续合并

---

## stash
- `list`查看存储状态
- `pop`将最新一次记录恢复并删除
- `clear`清除所有记录
- `show`看当前与栈顶差异
- `save xxx`提交注释

---

## remote
		add	origin URL					#添加远程仓库
		rm origin URL					#删除远程仓库
		-v 								#显示详细信息

---

## push
- `-u origin xxx`推送同时，尝试将origin 的 xxx 设置为上游
- `origin xxx --delete`删除远端的xxx分支
- `--tags`推送全部标签
- `-f`强制提交

---

## pull
- `origin xxx`覆盖当前工作树
- `--rebase`本地分支的提交应用到拉取的提交之上，保持历史线性
- `--no-commit`拉取并合并，但不自动提交
- `--edit`创建合并提交前，允许编辑提交信息

---

## fetch
- `--all`获取所有远端仓库更新
- `--prune`拉取更新时，清理已删除的分支

---

## tag
- `无`查看所有标签
- `[tag]`
- `-a`设置标签名
- `-m`填写标签说明
- `git tag v1.0.0`轻量标签,适用于临时标记
- `git tag -a v1.0.0 abc123d -m "tag"`附注标签,正式发布
- `git push origin --tags`推送所有标签
- `git push origin --follow-tags`推送所有附注标签

---

## worktree
允许在同一个仓库中同时签出多个分支,每个分支位于各自独立的工作目录(工作树)中
- 核心概念:
  - 主工作树:最初的仓库目录
  - 链接工作树:`worktree add`创建的新工作目录,链接到主目录`.git`
  - 共享存储库:被所有存储库共享的主目录`.git`
- 主要优势
  - 并行工作流
  - 避免切换成本
  - 隔离环境
  - 长期任务
- 命令详解
  - `git worktree add ../hotfix-bug-123 hotfix/bug-123`
    - `-b`创建一个新分支并签出它,等同于在新目录`git checkout -b`
    - `--detach`让新工作树处于"分离头指针"状态
  - `git worktree list`列出所有关联到当前仓库的工作树
  - `git worktree remove`删除一个链接工作树及其目录
  - `git worktree prune`清理失效记录


-----------------------------------------------------------------------------

.gitignore						#此文件中可放置不想追踪的文件


1.
	搭建git服务器
	1 + install git/openssh
	2 + useradd git
	3 + 创建证书登陆
		用户: .ssh/id.rsa.pub -> 服务器:`.ssh/authorized_keys` 一行一个
	4 + 创建仓库并移交权限给git用户
	5 + 禁用登陆shll usermod -s /bin/git-shell git

2.
	工作流参考
	1 + git clone 到本地仓库 
	2 + git checkout -b feature 创建新分支
	3 + git commit -am	提交
	4 + git push origin feature
	当遇到主分支更新时
	1 + git checkout main					切换到主分支
	2 + git pull origin main				拉取最新更新
	3 + git checkout feature				切换到特性分支
	4 + git rebase main						尝试变基合并
	5 + git push -f origin feature			强制提交特性分支
	6 + Pull Request   Squash and merge		合并到主分支
	7 + git checkout main					切换回主分支
	8 + git branch -D feature				删除特性分支
	9 + git pull origin main				拉取最新主分支
