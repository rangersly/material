syntax on           " 开启高亮
set number          " 显示行号
set hlsearch        " 高亮显示搜索结果


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

" 设置状态栏颜色
highlight StatusLine ctermfg=159 ctermbg=24 guifg=#d7ffff guibg=#005f87
highlight StatusLineNC ctermfg=152 ctermbg=238 guifg=#d0d0d0 guibg=#444444
