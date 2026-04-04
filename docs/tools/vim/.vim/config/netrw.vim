" === 目录树 ===

" 树形显示
let g:netrw_liststyle = 3

" 隐藏帮助横幅
let g:netrw_banner = 0

" 设置窗口占比
let g:netrw_winsize = 20

" 在当前窗口打开文件
let g:netrw_browse_split = 4

" 核心功能：仅在无启动参数时，以侧边栏方式打开 Netrw
let g:netrw_browse_split = 4
augroup InitNetrw
    autocmd!
    autocmd VimEnter * if argc() == 0 | Lexplore! | endif
augroup END
