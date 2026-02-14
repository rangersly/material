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

