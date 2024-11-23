#include "tn.h"
using namespace std;

TN::TN() {
	iofd = listenfd = 0;
}
TN::~TN() {
	close(listenfd);	//关闭连接
	close(iofd);	//关闭连接
}

int TN::server(const char *open_port, int connections) {
	// 创建服务端socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
		return -1;

	// 向客户端请求连接
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(atoi(open_port));	//指定连接端口

	// 解决端口重用问题
	int opt = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

	// 绑定服务端IP及端口
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
 		return -1;	// 绑定失败

	// 把端口设为监听
	if(listen(listenfd, connections) != 0)	//第二个参数+1为已连接队列(已三次握手但没有accept)
		return -1;
	return s_accept();
}
int TN::client(const char *ip, const char *port) {
	// 创建客户端socket
	iofd = socket(AF_INET, SOCK_STREAM, 0);
	if(iofd == -1)
		return -1;

	// 向服务端请求连接
	if( (h = gethostbyname(ip)) == 0)		// 指定ip地址
		return -1;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(port));	//指定连接端口
	memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
	if(connect(iofd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)		//发起连接请求
		return -1; 	//连接失败
	return 0;
}

int TN::s_accept() {
	// 受理客户端连接请求, accept()阻塞等待
	signal(SIGINT, TN_exit);signal(SIGTERM, TN_exit);
	while(true) {
		iofd = accept(listenfd, 0, 0);
		if(iofd == -1) {
			close(iofd); return -1;	// 连接失败
		}
		int pid = fork();
		if(pid == 0) {	// 创建子进程处理连接
			signal(SIGINT, SIG_IGN); signal(SIGTERM, SIG_DFL);
			close(listenfd); 
			break;
		}
		else if(pid < 0) return -1;
		else close(iofd);
	}
	return 0;
}

int TN::out(char *str) {
	if(send(iofd, str, strlen(str), 0) <= 0)	// 发送报文
		return -1;	// 报文发送不成功
	return 0;
}
int TN::in(char *str) {
	//接收报文， recv()将阻塞等待
	memset(str, 0, sizeof(str)); 
	if(recv(iofd, str, sizeof(str), 0) <= 0)
		return -1;	// 未成功接收报文
	return 0;
}
int TN::out(void *str, size_t fsize) {
	if(send(iofd, str, fsize, 0) <= 0)	// 发送报文
		return -1;	// 报文发送不成功
	return 0;
}
int TN::in(void *str, size_t fsize) {
	//接收报文， recv()将阻塞等待
	memset(str, 0, fsize); 
	if(recv(iofd, str, fsize, 0) <= 0)
		return -1;	// 未成功接收报文
	return 0;
}

socklen_t TN::bufsize(size_t buf_send, size_t buf_recv) {
	socklen_t optlen = sizeof(buf_send);
	// 接收缓冲区大小
	getsockopt(iofd, SOL_SOCKET, SO_SNDBUF, &buf_send, &optlen);
	// 发送缓冲区大小
	getsockopt(iofd, SOL_SOCKET, SO_RCVBUF, &buf_recv, &optlen);
	return optlen;
}

int TN::nagle_off() {
	int opt = 1;
	setsockopt(iofd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
	return 0;
}

void TN_exit(int sig) {
	signal(SIGTERM, SIG_IGN); signal(SIGINT, SIG_IGN); //避免再次干扰
	kill(0, SIGTERM);	// 通知所有子进程退出
	exit(0);
}
