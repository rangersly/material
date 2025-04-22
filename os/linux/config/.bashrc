# ~/.bashrc

# 如果未交互运行则退出（避免非交互式shell加载）
[[ $- != *i* ]] && return

# 历史记录配置
HISTSIZE=5000                   # 内存中保存的历史记录数量
HISTFILESIZE=5000              # 历史文件最大行数
HISTCONTROL=ignoreboth          # 忽略重复命令和空格开头的命令
shopt -s histappend             # 追加历史而不是覆盖

# 默认编辑器
export EDITOR=vim
export VISUAL=vim

# 设置语言（解决可能的中文乱码）
export LANG=en_US.UTF-8
export LC_ALL=en_US.UTF-8

# 自定义PATH
export PATH=$PATH:$HOME/.local/bin:$HOME/bin

# 彩色输出
alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'

# 更详细的ls别称
alias ll='ls -alFh --group-directories-first'
alias la='ls -A'
alias l='ls -CF'

# Git状态集成（需安装git）
parse_git_branch() {
    git branch 2>/dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
}

# 自定义PS1提示符（带颜色和Git分支）
PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;31m\]$(parse_git_branch)\[\033[00m\]\$ '

# 安全操作确认
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

# 快速导航
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'
alias ~='cd ~'

# 网络相关
alias myip='curl ifconfig.me'           # 获取公网IP

# 解压快捷方式
extract() {
    if [ -f "$1" ]; then
        case "$1" in
            *.tar.bz2) tar xvjf "$1" ;;
            *.tar.gz)  tar xvzf "$1" ;;
            *.bz2)     bunzip2 "$1" ;;
            *.rar)     unrar x "$1" ;;
            *.gz)      gunzip "$1" ;;
            *.tar)     tar xvf "$1" ;;
            *.tbz2)    tar xvjf "$1" ;;
            *.tgz)     tar xvzf "$1" ;;
            *.zip)     unzip "$1" ;;
            *.Z)      uncompress "$1" ;;
            *.7z)      7z x "$1" ;;
            *)        echo "不支持的文件格式: $1" ;;
        esac
    else
        echo "文件不存在: $1"
    fi
}

# 快速重载
alias reload='source ~/.bashrc'

# 快速查看电池信息
alias bat='upower -i /org/freedesktop/UPower/devices/battery_BAT0'

# 错误纠正
shopt -s cdspell                     # 自动纠正cd命令的目录名拼写错误

# 启用补全功能
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# 终端启动时显示消息
echo -e "\e[1;34m$(date +'%A, %B %d %Y %H:%M:%S')\e[0m"
echo -e "\e[1;32mWelcome to My Linux, \e[1;35m$USER!\e[0m"
