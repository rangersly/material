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
