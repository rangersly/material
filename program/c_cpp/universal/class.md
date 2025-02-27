#	对象和类

##	访问控制
```cpp
class demo {
public:		// 公有接口
private:	// 私有成员
protected:	// 保护
};
```
##	作用域运算符(::)
可用于在类体外指出函数所属的类(命名空间)

##	成员函数的参数名不可与类成员相同

##	类的六大特殊成员函数(未定义时编译器提供默认版本)
```cpp
demo::demo();							// 默认构造函数
demo::~demo();							// 默认析构函数
demo::demo(const demo&);				// 复制构造函数
demo& demo::operator = (const demo&);	// 赋值构造函数
demo::demo(demo&&);						// 移动复制构造函数
demo& demo::operator = (demo&&);		// 移动赋值构造函数
```

##	const 成员函数	适合的成员函数要尽可能用，以帮助规避错误
`void show() const;`			声明
`void demo::show() const;`		定义
表明函数不会修改调用对象

##	this指针
	成员函数引用整个调用对象，可以使用 *this

##	作用域为类的常量(无法用const)
	因为声明类只是描述了对象的形式，没有创建对象
+	在类中声明一个枚举
```cpp
	class const_demo {
	private:
		enum {Pi = 3.1415);
		double s = 2*Pi;
	};
```
+	使用关键字 static
	与其他静态常量存储在一起
`	class demo {static const int Months=12};`

##	作用域内枚举
	`enum class egg {small, large};`
	使用后需要通过枚举名限定枚举量
	`egg demo1 = egg::large;`
	并且关闭了隐式转换的特性

##	友元
+	友元函数
+	友元类
+	友元成员函数
将函数声明放在类体内,public private 内都无所谓
在声明前面加上friend关键字

##	类的自动转换和强制类型转换
当类有仅一个参数的构造函数时
遇到合适的会进行自动转换
explicit 	禁止单个参数构造函数导致的隐式自动类型转换
仍然可以使用显式强制转换(当不存在二义性时)

###	转换函数
`int aaa = int(demo);`
operator typeName();
+	必须是类成员
+	不能有参数
+	不能指定返回类型
