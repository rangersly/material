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



# 列表
li1 = []			# 创建空列表
li2 = list()	
li3 = list(s)		# 转换字符串成列表
li3.index('H')		# 返回对应值的下标	反查
li4 = s.split(' ')	# 通过空格分割字符串成列表
# li1[start:end:step]

for i,t in enumerate(li3):		# 同时输出索引和值(列表本身也可以直接作为循环的序列)
	print(i,t)

# 列表的更新与排序
li1.append([26,71])				# [26,71]作为一个元素追加到末尾
li1.extend([26,71])				# 将[26,71]每一项合并到末尾
li1.insert(1,520)				# 将520插入位置1
li1[0] = 1314					# so easy
li1.remove(3)					# 删除指定位置元素
li1.pop()						# 默认删除-1位置的元素
li1.sort()						# 对列表本身排序
li1.sort(reverse=True)			# 对列表本身排序(倒序)
li2 = sorted.(li1)				# 返回一个排序完的列表


# 元组tuple		元素不可修改的列表
t1 = ()
t1 = tuple(li1)


# 集合 set
set1 = {4,3,2,1}
set2 = set(li1)
set3 = set1 & set2		# 交集
set3 = set1 | set2		# 并集
set3 = set1 - set2		# 差集
set3.add(123)			# 添加
set3.remove(123)		# 删除
sum(set3)				# 求总个数


# 字典 dict
dict1 = {'你好':'Hello'}
dict2 = zip(li1,li2)		# 通过两个列表创建字典
del dict1['你好']			# 删除元素
dict1['再见'] = 'bey'		# 存在更新,不存在添加
dict1.setdefault('好','OK')	# 存在不修改,不存在添加

s = dict1.get('好','NO')	# 不存在追加,存在返回原值不修改

for i,t in dict1.items():	# 遍历所有键值对
	print(i,t)
for i in dict1.keys():		# 遍历所有键
	print(i)
for i in dict1.values():	# 遍历所有值
	print(i)


# 函数
def jc(n):
	ans = 1;
	for i in range(n):
		ans *= i
	return ans
