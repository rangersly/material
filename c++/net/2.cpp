#include <iostream>
#include <cstring>
//#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
using namespace std;
int handling(char *buffer) {		// 数据处理函数
	if(strcmp(buffer, "off\n") == 0) {
		cout << "服务端指令关闭服务器" << endl; return -1;
	}
	cout << "成功接收" << endl << buffer << endl;
	return 0;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		cout << "参数不正确" << endl; return -1;
	}

	// 创建服务端socket
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1) {
		cout << "socket创建失败" << endl; return -1;
	}

	// 向客户端请求连接
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));	//指定连接端口
	// 绑定服务端IP及端口
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		cout << "端口未成功绑定" << endl; close(listenfd); return -1;
	}
	
	// 把端口设为监听
	if(listen(listenfd, 5) != 0) {
		cout << "端口无法监听" << endl; close(listenfd);  return -1;
	}

	// 受理客户端连接请求, accept()阻塞等待
	int clistenfd;
	while(true) {
		clistenfd = accept(listenfd, 0, 0);
		if(clistenfd == -1) {
			cout << "未正常受理连接" << endl; close(listenfd); return -1;
		}
		cout << "客户端已连接" << endl;
	
		//与客户端通信
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		if(recv(clistenfd, buffer, sizeof(buffer), 0) <= 0) { 	// 接受服务端报文
			cout << "客户端连接已断开" << endl; break;
		}
		if(handling(buffer) == -1) break;		//对接受数据进行处理

		// 发送回应报文	
		strcpy(buffer, "OK");	
		if(send(clistenfd, buffer, strlen(buffer), 0) <= 0) {
			cout << "发送回应报文失败" << endl; break;
		}
	}

	//关闭连接
	close(clistenfd);
	close(listenfd);
	return 0;
}
