a1 = int(input("input:"))		#	input
print('%8d'%a1, '\n')					#	print
# print(objects, sep=' ', wnd='\n')


# 数据类型
x1 = 123
x2 = 123.123
x3 = True
x4 = "True"

print(x1, "   ", type(x1))
print(x2, "   ", type(x2))
print(x3, "   ", type(x3))
print(x4, "   ", type(x4))
print()


# 运算符
"""
	1.	**
	2.	*  /  %  //
	3.	+  -
	4.	<=  <  >  >=
	5.	<>	==  !=
	6.	=  %=  /=  //=  -=  +=  *=  **=
	7.	not  or  and
"""

# 条件判断
if (x1==a1) and (x3==True):
	print("OK!!!")
elif x3==False:
	print("x3==False")
else:
	print("x1:", x1)
	print("a1:", a1)
print()


# 循环控制
for i in range(10):			# 逐一访问序列中的元素	
	while i>=9 and i<13:	# 通过条件控制
		print(i)
		i+=1
		continue
		break

# range()	函数  创建一个整数列表
"""
	# 基本格式
	range(start, stop,[step])
	# 开始  结束  步长
	range(5, 1, -1)			# 可做到倒序输出
"""
