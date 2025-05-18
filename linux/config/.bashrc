# ~/.bashrc

# 如果未交互运行则退出（避免非交互式shell加载）
[[ $- != *i* ]] && return

# 历史记录配置
HISTSIZE=10000                   # 内存中保存的历史记录数量
HISTFILESIZE=10000              # 历史文件最大行数
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


# PS1提示符

# Git状态集成（需安装git）
parse_git_branch() {
    git branch 2>/dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
}

# 在 ~/.bashrc 中添加以下内容

# 首先确保 parse_git_branch 函数存在（用于显示 Git 分支）
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

# 设置自定义提示符
 PROMPT_COMMAND='__prompt_command'
 __prompt_command() {
     local EXIT="$?"
 
     # 颜色定义
     local Reset='\[\033[00m\]'
     local TimeColor='\[\033[03;33m\]'  # 青色时间
     local UserColor='\[\033[01;32m\]'  # 绿色用户
     local HostColor='\[\033[01;32m\]'  # 绿色主机
     local PathColor='\[\033[01;34m\]'  # 蓝色路径
     local GitColor='\[\033[01;31m\]'   # 红色 Git 分支
     local ExitColor='\[\033[01;33m\]'  # 黄色退出状态
 
     # 获取当前时间
     local TIME=$(date +"%H:%M:%S")
 
     # 处理路径：长路径时只保留每级目录首字母
     local DIR=${PWD/#$HOME/\~}
     if [ ${#DIR} -gt 30 ]; then
         DIR=$(echo $DIR | awk -F '/' '{
             if (length($0) > 30) {
                 for (i=1; i<=NF; i++) {
                     if (i == NF) printf "%s", $i;
                     else printf "%.3s/", $i;
                 }
             }
             else print $0;
         }')
     fi
 
     # 构建提示符
     PS1="${TimeColor}[${TIME}] ${UserColor}\u${HostColor}@\h${Reset}:"
     PS1+="${PathColor}${DIR}${GitColor}$(parse_git_branch)${Reset}"
 
     # 添加上一个命令的退出状态（非零时显示）
     if [ $EXIT != 0 ]; then
         PS1+="${ExitColor}[${EXIT}]${Reset}"
     fi
 
     PS1+="\$ ${Reset}"
 }
 
# 如果 PROMPT_COMMAND 设置失败，回退到原始提示符
# 自定义PS1提示符（带颜色和Git分支）
PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;31m\]$(parse_git_branch)\[\033[00m\]\$ '

# 彩色输出
alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'

# ls别称
alias l='ls -alFh --group-directories-first'
alias ll='ls -A'
# alias l='ls -CF'

# 安全操作确认
alias rr='rm -i'
#alias cp='cp -i'
#alias mv='mv -i'

# 快速导航
alias ..='cd ..'
alias ...='cd ../..'
alias ~='cd ~'

# 网络相关
alias myip='curl ifconfig.me'           # 获取公网IP

# 快速重载
alias reload='source ~/.bashrc'

# 快速使用 systemctl
alias sscl='sudo systemctl'

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
echo -e "\e[1;32mWelcome to My Linux, \e[1;35m$USER!\e[0m"
echo -e "\e[1;34mversion:1.0\e[0m"
