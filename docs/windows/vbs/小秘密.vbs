text()
function text()
dim a
a=InputBox("做我女朋友吧！")
if a="好的"then
Msgbox"臭宝，真乖！",0,"恭喜"
else
Msgbox"臭宝，不同意还想跑！",0,"再来一次"
text()
end if
end function