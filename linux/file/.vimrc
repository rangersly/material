syntax on  
set number          "显示行号
"set rnu				"相对行号
set ts=4        
"set expandtab       "tab to space
set autoindent      "自动缩进
set encoding=utf-8  "使用utf-8字符编码
set fileencoding=utf-8
"set cindent
set nocompatible    "?
"set guifont=consolas:h14
set wrap            "自动折行
set cursorline      "光标行高亮
set hlsearch        "高亮显示搜索结果
set incsearch       "搜索模式下，每输入一个字符，就跳到对应结果
set ignorecase      "忽略搜索大小写


nnoremap <space>b :buffers<cr>:b<space>
nnoremap <space>e :b#<cr>
nnoremap <space>n :bnext<cr>
nnoremap <space>s :split<space>
nnoremap <space>v :vsp<space>
nnoremap <space>d <c-w>w
nnoremap <space>w :w<cr>
nnoremap <space>q :q<cr>
nnoremap <space>tt :tabedit<space>
nnoremap <space>to :tabonly<cr>
inoremap jf <esc>
inoremap jq <esc>:wq<cr>
inoremap jw <c-x><c-n>
inoremap jl <c-x><c-l>
cnoremap jf <c-c> 

augroup numbertoggle 智能切换绝对行号和相对行号
  autocmd!
  autocmd BufEnter,FocusGained,InsertLeave,WinEnter * if &nu && mode() != "i" | set rnu   | endif
  autocmd BufLeave,FocusLost,InsertEnter,WinLeave   * if &nu                  | set nornu | endif
augroup END

" vim笔记
"	使用 q[Key] 开始录制宏,再次点击q结束录制
"	@[Key]	调用宏
"	
"	# 键向上查找当前单词
