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
set tags=./tags;,tags "表示从当前文件所在的目录开始查找 tags 文件，如果没有，则向上递归查找

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
inoremap jbf <c-x><c-f>
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


