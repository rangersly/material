" 编码
set encoding=utf-8  "使用utf-8字符编码
set fileencoding=utf-8


" 优化设置
syntax on
set number          " 显示行号
set autoindent      " 自动缩进
set nocompatible    " 关闭与Vi的兼容,以支持Vim的特性
set wrap            " 自动折行
"set cursorline     " 光标行高亮
set hlsearch        " 高亮显示搜索结果
set incsearch       " 搜索模式下，每输入一个字符，就跳到对应结果
set ignorecase      " 忽略搜索大小写
set iskeyword+=_,-    " 把 - 和 _ 也看作单词的一部分


" 格式设置
set expandtab       " tab to space
set ts=4
set softtabstop=4   " 编辑时退格键删除的空格数
set shiftwidth=4    " 自动缩进使用的空格数
set smarttab
" Tab转4空格
nnoremap <leader>p :%s/\t/    /g<cr>:wq<cr>
" 在编写makefile文件时使用tab
autocmd FileType make setlocal noexpandtab

" 去除行末空白字符
nnoremap <Leader>cw :%s/\s\+$//e<CR>

" 缓冲区操作
nnoremap <space>b :buffers<cr>:b<space>
nnoremap <space>e :b#<cr>

" 页面分割操作
nnoremap <space>s :split<space>
nnoremap <space>v :vsp<space>
nnoremap <space>d <c-w>w

" 保存退出
nnoremap <space>q :wq<cr>
nnoremap <space>f :q<cr>

" 多标签页(使用gt进行标签页间切换)
nnoremap <space>tt :tabedit<space>
nnoremap <space>tm :vert term<cr>

" 操作优化
nnoremap gf <c-w>f<c-w>T
nnoremap <space>r :reg<cr>
inoremap jf <esc>:w<cr>
cnoremap jf <c-c>


" 中文符号转英文符号
inoremap ！ !
inoremap （ (
inoremap ） )
inoremap ‘ '
inoremap “ "
inoremap ， ,
inoremap 。 .
inoremap ？ ?

" 修复版中文符号转换函数
function! ConvertChinesePunctuationEnhanced() range
    " 保存光标位置
    let save_cursor = getpos(".")
    let save_view = winsaveview()

    " 判断是否在可视化模式下调用
    let visual_mode = (a:firstline != a:lastline) || (mode() =~# '[vV]')

    " 确定操作范围
    if visual_mode
        " 可视化模式：使用传递的范围
        let range = a:firstline . ',' . a:lastline
        let range_desc = '选中区域'
    else
        " 普通模式：转换整个文件
        let range = '%'
        let range_desc = '整个文件'
    endif

    " 执行符号转换
    execute 'silent! ' . range . 's/，/,/ge'
    execute 'silent! ' . range . 's/。/./ge'
    execute 'silent! ' . range . 's/；/;/ge'
    execute 'silent! ' . range . 's/：/:/ge'
    execute 'silent! ' . range . 's/？/?/ge'
    execute 'silent! ' . range . 's/！/!/ge'
    execute 'silent! ' . range . 's/"/"/ge'
    execute 'silent! ' . range . 's/」/"/ge'
    execute 'silent! ' . range . 's/‘/''/ge'
    execute 'silent! ' . range . 's/’/''/ge'
    execute 'silent! ' . range . 's/（/(/ge'
    execute 'silent! ' . range . 's/）/)/ge'
    execute 'silent! ' . range . 's/【/[/ge'
    execute 'silent! ' . range . 's/】/]/ge'
    execute 'silent! ' . range . 's/《/</ge'
    execute 'silent! ' . range . 's/》/>/ge'
    execute 'silent! ' . range . 's/……/.../ge'
    execute 'silent! ' . range . 's/——/--/ge'

    " 恢复状态
    call setpos('.', save_cursor)
    call winrestview(save_view)

    echo "已转换" . range_desc . "的中文符号为英文符号"
endfunction

" 映射快捷键
nnoremap <leader>cc :call ConvertChinesePunctuationEnhanced()<CR>


"自动补全
set complete=.,w,b,k,d,i
" 补全时忽略大小写
set infercase
" 设置补全延迟（毫秒）
set updatetime=300
" 延迟重绘屏幕,在宏、脚本、函数执行期间不更新屏幕,执行完一次性更新
set lazyredraw
" 允许递归扫描 include 目录
set path=.,/usr/include,**

" 设置补全菜单行为
set completeopt=menuone,noselect,noinsert  " 单行菜单、不自动选择、不自动插入
set shortmess+=c  " 减少补全提示的干扰信息
set pumheight=15  " 补全菜单最大高度

" 文件名补全
inoremap jn <c-x><c-f>

" 启用字典补全（Ctrl-X Ctrl-K）
" 根据文件类型设置不同的字典文件
autocmd FileType c setlocal dictionary+=~/.vim/dict/cpp.dict
autocmd FileType cpp setlocal dictionary+=~/.vim/dict/cpp.dict


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
