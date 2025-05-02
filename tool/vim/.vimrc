syntax on  
set number          "显示行号
"set rnu				"相对行号
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
set tags=./tags;,tags "表示从当前文件所在的目录开始查找 tags 文件，如果没有，则向上递归查找

"Tab and Space 
set expandtab       "tab to space
set ts=4        
set softtabstop=4   " 编辑时退格键删除的空格数
set shiftwidth=4    " 自动缩进使用的空格数

"把 - 和 _ 也看作单词的一部分
set iskeyword+=-
set iskeyword+=_

"缓冲区操作
nnoremap <space>b :buffers<cr>:b<space>
nnoremap <space>e :b#<cr>
nnoremap <space>n :bnext<cr>

"页面分割操作
nnoremap <space>s :split<space>
nnoremap <space>v :vsp<space>
nnoremap <space>d <c-w>w

"保存
nnoremap <space>w :w<cr>
nnoremap <space>q :q<cr>
nnoremap <space>fq :q!<cr>
nnoremap <space>pq :%s/\t/    /g<cr>:wq<cr>

"多标签页
nnoremap <space>tt :tabedit<space>
nnoremap <space>tm :vert term<cr>

"操作优化
nnoremap gf <c-w>f<c-w>T
nnoremap gm $
nnoremap <space>r :reg<cr>
inoremap jf <esc>
cnoremap jf <c-c> 
vnoremap gm $
inoremap ！ !
inoremap （ (
inoremap ） )
inoremap 【 [
inoremap 】 ]
inoremap ； ;
inoremap ： :
inoremap ‘ '
inoremap “ "
inoremap ， ,
inoremap 。 .
inoremap ？ ?
inoremap 《 <
inoremap 》 >
inoremap · `

"自动补全
inoremap jl <c-x><c-l>
inoremap jnf <c-x><c-f>
inoremap jk <c-x><c-k>

" 启用字典补全（Ctrl-X Ctrl-K）
set complete+=k
" 加载字典补全功能
" 根据文件类型设置不同的字典文件
autocmd FileType c setlocal dictionary+=~/.vim/dict/cpp.dict
autocmd FileType cpp setlocal dictionary+=~/.vim/dict/cpp.dict
"autocmd FileType python setlocal dictionary+=~/.vim/dict/python.dict
"autocmd FileType javascript setlocal dictionary+=~/.vim/dict/javascript.dict
"autocmd FileType html setlocal dictionary+=~/.vim/dict/html.dict
"autocmd FileType css setlocal dictionary+=~/.vim/dict/css.dict


augroup numbertoggle 	"智能切换绝对行号和相对行号
  autocmd!
  autocmd BufEnter,FocusGained,InsertLeave,WinEnter * if &nu && mode() != "i" | set rnu   | endif
  autocmd BufLeave,FocusLost,InsertEnter,WinLeave   * if &nu                  | set nornu | endif
augroup END



" 总是显示状态栏
set laststatus=2

" 设置状态栏内容
set statusline=
set statusline+=%F\                     " 文件名
set statusline+=%h%m%r%w               " 文件状态标志
set statusline+=[%{&ff}/%Y]            " 文件类型
set statusline+=%=                     " 右对齐
set statusline+=%l/%L\                 " 行号信息
set statusline+=%c%V\                  " 列号
set statusline+=%{&fileencoding?&fileencoding:&encoding} " 添加当前编码
set statusline+=\ %{FileSize()}        " 添加文件大小
set statusline+=\ %P\                  " 文件进度百分比

function! FileSize()
  let bytes = getfsize(expand('%:p'))
  if bytes <= 0
    return ''
  endif
  if bytes < 1024
    return bytes . 'B'
  elseif bytes < 1024 * 1024
    return printf('%.1f', bytes/1024.0) . 'K'
  else
    return printf('%.1f', bytes/1024.0/1024.0) . 'M'
  endif
endfunction

" 设置状态栏颜色
highlight StatusLine ctermfg=159 ctermbg=24 guifg=#d7ffff guibg=#005f87
highlight StatusLineNC ctermfg=152 ctermbg=238 guifg=#d0d0d0 guibg=#444444
