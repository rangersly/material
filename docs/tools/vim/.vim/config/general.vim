"使用utf-8字符编码
set encoding=utf-8  
set fileencoding=utf-8


set autoindent      " 自动缩进
set nocompatible    " 关闭与Vi的兼容,以支持Vim的特性
set wrap            " 自动折行
set incsearch       " 搜索模式下，每输入一个字符，就跳到对应结果
set ignorecase      " 忽略搜索大小写
set iskeyword+=_,-  " 把 - 和 _ 也看作单词的一部分


" 格式设置
set expandtab       " tab to space
set ts=4            " 设置一个Tab的宽度
set softtabstop=4   " 编辑时退格键删除的空格数
set shiftwidth=4    " 自动缩进使用的空格数
set smarttab        " 行首使用Tab时,插入shiftwidth指定的空格数

" 在编写makefile文件时使用tab
autocmd FileType make setlocal noexpandtab


augroup numbertoggle 	"智能切换绝对行号和相对行号
  autocmd!
  autocmd BufEnter,FocusGained,InsertLeave,WinEnter * if &nu && mode() != "i" | set rnu   | endif
  autocmd BufLeave,FocusLost,InsertEnter,WinLeave   * if &nu                  | set nornu | endif
augroup END
