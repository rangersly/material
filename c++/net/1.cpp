#include <iostream>
#include <cstring>
//#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
using namespace std;

int net_send(char *argv[], char *buffer) {
	if(strlen(buffer) > 1024) {
		cout << "字符串长度超出限制" << endl; return -1;
	}

	// 创建客户端socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		cout << "socket创建失败" << endl; return -1;
	}
	// 向服务端请求连接
	struct hostent* h;
	if( (h = gethostbyname(argv[1])) == 0) {
		cout << "地址不正确" << endl; close(sockfd); return -1;
	}
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));	//指定连接端口
	memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {		//发起连接请求
		cout << "连接失败" << endl; close(sockfd); return -1;
	}

	// 客户端通信
	if(send(sockfd, buffer, strlen(buffer), 0) <= 0) {  //发送请求报文
		cout << "请求报文发送不成功" << endl; return -1;
	}

	//接收服务端回应报文， recv()将阻塞等待
	memset(buffer, 0, sizeof(buffer)); 
	if(recv(sockfd, buffer, sizeof(buffer), 0) <= 0) {
		cout << "服务器断开--未成功接收回应报文" << endl; return -1;
	}
	// 回应报文
	cout << buffer << endl;

	//关闭连接
	close(sockfd);
	return 0;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		cout << "参数不正确" << endl; return -1;
	}

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	cout << "input data : ";
	fgets(buffer, sizeof(buffer), stdin);
	net_send(argv, buffer);

	return 0;
}
