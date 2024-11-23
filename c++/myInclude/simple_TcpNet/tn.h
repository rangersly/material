// Copyright (c) 2024 ely. All rights reserved.
// simple_TcpNet
// 宗旨:简单易用，且尽可能的自由
// versions 1.0.2
//	 大版本 小版本 修订版本
#ifndef TCPNET
#define TCPNET

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netinet/tcp.h>

class TN {	// tcp socker net
	private:
		int iofd, listenfd;
		struct hostent* h;
		struct sockaddr_in servaddr;
		int s_accept();	
	public:
		TN();
		~TN();
		int server(const char *, int);
		// 服务端的初始化函数	
		// 传入一个使用的端口号(请尽量用大于1024的值)和最大等待连接数
		// 服务端受理并处理连接,使用多进程以连接多个客户端
		// 若返回0表示成功与一个客户端建立连接

		int client(const char *, const char *);	
		// 客户端的初始化函数
		// 参数为服务端ip和端口
		// 若返回0表示成功与一个服务端建立连接

		// 网络I/O函数  在连接建立后即可使用此组函数进行通信
		int out(char *);
		int in(char *);
		// 重载的任意类型IO函数，第二个参数是类型大小
		int out(void *, size_t);
		int in(void *, size_t);

		// 查看socket发送和接收缓冲区的大小
		socklen_t bufsize(size_t buf_send, size_t buf_recv);

		// 禁用Nagle算法,可以减少延迟,但是带宽利用不充分
		int nagle_off();
};
void TN_exit(int sig);
#endif

/*
	HISTORY
		1.0.1 调整注释和服务端端口重用问题
		1.0.2 加入bufsize函数查看缓冲区大小 加入nagle_off开关

	PLAN
		编写高并发的封装类
*/
