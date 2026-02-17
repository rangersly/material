" Tab转4空格
nnoremap <leader>p :%s/\t/    /g<cr>:wq<cr>

" 去除行末空白字符
nnoremap <Leader>cw :%s/\s\+$//e<CR>

" 替换所有中文字符为英文字符
nnoremap <leader>cc :call ConvertChinesePunctuationEnhanced()<CR>

" 缓冲区操作
nnoremap <space>b :buffers<cr>:b<space>
nnoremap <space>e :b#<cr>

" 页面分割操作
nnoremap <space>s :split<space>
nnoremap <space>v :vsp<space>
nnoremap <space>d <c-w>w

" 保存退出
nnoremap <space>w :wq<cr>
nnoremap <space>q :q<cr>

" 多标签页(使用gt进行标签页间切换)
nnoremap <space>tt :tabedit<space>
nnoremap <space>tm :vert term<cr>

" 操作优化
nnoremap gf <c-w>f<c-w>T
nnoremap <space>r :reg<cr>
inoremap jf <esc>
cnoremap jf <c-c>

" 文件名补全
inoremap jn <c-x><c-f>

" 打开文件树
nnoremap <leader>l :Lex<cr>

" 中文符号转英文符号
inoremap ！ !
inoremap （ (
inoremap ） )
inoremap ‘ '
inoremap “ "
inoremap ， ,
inoremap 。 .
inoremap ？ ?
