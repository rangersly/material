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


" 获取文件大小并智能选择单位
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
