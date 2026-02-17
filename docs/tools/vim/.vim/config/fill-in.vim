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
set completeopt=menuone  " 单行菜单
set shortmess+=c  " 减少补全提示的干扰信息
set pumheight=15  " 补全菜单最大高度

" 根据文件类型设置不同的字典文件
autocmd FileType c setlocal dictionary+=~/.vim/dict/cpp.dict
autocmd FileType cpp setlocal dictionary+=~/.vim/dict/cpp.dict

