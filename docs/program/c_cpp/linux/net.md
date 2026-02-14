# net
```cpp
	#include <iostream>
	#include <cstring>
	#include <unistd.h>
	#include <netdb.h>
	#include <cstdlib>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
```

# tips
	+ 所有网络函数失败基本是返回 -1,errno被设置

# socket


	原型:  int socket(int domain, int type, int protocol)

		+ domain 协议族
		 \	PF_INET			# IPv4 互联网协议族
		 \	PF_INET6 		# IPv6 互联网协议族
		 \	PF_LOCAL		# 本地通讯地址族

		+ type 数据传输类型
		 \	SOCK_STREAM		# 面向连接;  数据不丢失;  数据顺序不错乱;  双向通道;
		 \  SOCK_DGRAM		# 无连接;	 数据可能丢;  数据可能错乱;	   效率高;

		+ protocol 最终使用协议
		 \  IPPROTO_TCP
		 \  IPPROTO_UDP
		 \  0				# 编译器自动识别

# 主机字节序和网络字节序
	
	+ 大端序和小端序 (如果数据大于1B,CPU在内存中存放数据的方式)
	 \  大端序	低位字节在高位,高位字节在低位
	 \  小端序	低位字节在低位,高位字节在高位 (INTEL)

	## 字节序不同的系统字节传输数据,可能会出现问题,所以网络字节序约定使用大端序
	+ c提供了4个库用于主机字节序和网络字节序之间的转换
	 \  uint16_t htons(uint16_t hostshort);	// 2字节的整数
	 \  uint32_t htonl(uint32_t hostshort);	// 4字节的整数
	 \  uint16_t ntons(uint16_t netshort);	// 2字节的整数
	 \  uint32_t ntonl(uint32_t netshort);	// 4字节的整数
		// h	host主机
		// to 	转换
		// n 	network网络
		// s	short(2byte)
		// l 	long(4byte)

# IP地址和通讯端口
	+ IPv4(4byte) 端口(2byte)

# 大小端序的处理
	+ 在网络编程中数据收发有自动转换,只有sockaddr_in结构成员变量填充数据时，才需要考虑字节序

# 结构体
	
	## sockaddr
	```cpp
		struct sockaddr { 	// connect() bind() 都需要
			unsigned short sa_family;	// 协议族
			unsigned char sa_data[14];	// 14byte的端口和地址
		}
	```	

	## sockaddr_in
	```cpp
		struct sockaddr {	// 为了方便操作，大小与sockaddr相同，可以强制转换
			unsigned short sin_family;	// 协议族
			unsigned short sin_port;	// 2byte端口号
			//struct in_addr sin_addr;	// 4byte地址
			unsigned int sin_addr;		// 4byte地址
			unsigned char sin_zero[8];	// 保留，长度对齐
		}
	```

# gethostbyname函数
	
	+ 用 域名/主机名/字符串IP 转换成大端序
	```cpp
		struct hostent *gethostbyname(const char *name);
		struct hostent {
			char *h_name;				// 主机名
			char **h_aliases;			// 主机所有别名的字符串数组
			short h_addrtype;			// 主机IP类型,IPv4或IPv6
			short h_length;				// 主机IP长度
			char **h_addr_list;			// 主机IP地址,以网络字节序存储
		}
		#define h_addr h_addr_list[0]

		// 转换后，用 memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
	```

# 字符串IP和大端序IP的转换
	## atoi() 把字符串IP转换成大端序
	```cpp
		typedef unsigned int in_addr_t;	//4byte大端序IP

		// 字符串转大端序IP,转换后IP赋给sockaddr_in.in_addr.s_addr
		in_addr_t inet_addr(const char *cp);

		// 字符串转大端序IP,转换后IP赋给sockaddr_in.in_addr
		int inet_aton(const char *cp, struct in_addr *inp);

		//大转字符串,用于服务端解析IP
		char *inet_ntoa(struct in_addr in);
	```

