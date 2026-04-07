" === 自动补全 ===

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
set completeopt=menu,menuone,noselect,noinsert,popup
set shortmess+=c  " 减少补全提示的干扰信息
set pumheight=15  " 补全菜单最大高度
set wildoptions+=fuzzy

" 增强命令行补全
set wildmenu
set wildmode=full
set path+=**

" 根据文件类型设置不同的字典文件
autocmd FileType c setlocal dictionary+=~/.vim/dict/cpp.dict
autocmd FileType cpp setlocal dictionary+=~/.vim/dict/cpp.dict

" 状态标记：当前连续非空字符序列是否已触发过补全
let g:auto_comp_triggered = 0

function! s:TriggerComplete()
    if pumvisible() | return | endif

    " 获取光标前的所有字符
    let before = getline('.')[0 : col('.')-2]
    " 获取光标前尾部连续非空字符（\S 匹配非空白）
    let tail = matchstr(before, '\w\+$')

    if len(tail) >= 3 && !g:auto_comp_triggered
        call feedkeys("\<C-n>", 'n')
        let g:auto_comp_triggered = 1
    elseif len(tail) == 0
        " 遇到空字符（空格、回车等），重置标记
        let g:auto_comp_triggered = 0
    endif
endfunction

" 监听插入模式每次文本变化
augroup AutoComplete
    autocmd!
    autocmd TextChangedI * call s:TriggerComplete()
    " 补全完成后重置标记，允许下一次连续输入重新触发
    autocmd CompleteDone * let g:auto_comp_triggered = 0
augroup END

" Tab 键智能映射
inoremap <expr> <Tab>   pumvisible() ? "\<C-n>" : "\<Tab>"
