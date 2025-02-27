# 字符串
s = str("Hello world")

print(s[3])		
print(s[-3])
print(s[0:3])	# 字符串切片
print(s[3:])
print(s[:5])
print(s[:-5])
print(s[::-1])	# 倒序
len(s)		# 计算长度

# 字符串查询
s.find('w')
s.count('l')

s.replace('H','h') # H变成h
s.casefold()		# 大写转小写
s.upper()			# 小写转大写
s.swapcase()		# 转换大小写
eval('12+3')		# 计算值 返回15


