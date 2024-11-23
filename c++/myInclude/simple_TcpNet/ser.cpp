// 示例服务端程序
// 一个可以接收文件的服务端程序
#include <iostream>
#include <fstream>
#include "tn.h"
using namespace std;

struct FileStat {	//存放文件信息
	char name[128];		// 文件名
	size_t fsize = 0, read = 0, ssize = 0;	
	//文件大小   文件已读大小  本次发送大小
};

int pton(char *, const char *);
int file_in(TN &, char *);	// 传入一个连接和文件保存目录

int main(int argc, char *argv[]) {
	if(argc != 2 || (argv[1][strlen(argv[1])-1]!='/')) {
		cout << "Using: ./ser.exe [PATH]/" << endl;
		return 0;
	}
	TN test1;
	test1.server("12345", 10);
	cout << "客户端连接成功" << endl;
	cout << file_in(test1, argv[1]) << endl;
	cout << "客户端连接断开" << endl;
	return 0;
}

int pton(char *name, const char *path) {
	int ptr = strlen(path);
	while(ptr!=0 && path[ptr-1]!='/')
		ptr--;
	for(int j=0; ptr<=strlen(path); j++,ptr++)
		name[j]=path[ptr];
	return 0;
}

int file_in(TN &tn, char *path) {		// 传入一个连接和文件保存目录
	const unsigned int BSIZE = 1024;
	char buffer[BSIZE];
	FileStat fs;
	fstream fout;
	memset(buffer, 0, sizeof(buffer));
	strcpy(buffer, path);
	if(tn.in((FileStat *)&fs, sizeof(fs))!=0) return 0;	// 接收文件信息
	strcat(buffer, fs.name);		// 连接字符串
//	strcpy(fs.name, buffer);
	fout.open(buffer, ios::out|ios::trunc|ios::binary);		// 打开保存文件
	if(tn.out((char *)"OK")!=0) return 0;	// 发送确认报文

	while(fout.good() && fs.fsize>fs.read) {
		memset(buffer, 0, sizeof(buffer));
		fs.ssize = (fs.fsize-fs.read)>BSIZE? BSIZE:(fs.fsize-fs.read);
		if(tn.in(buffer, fs.ssize)!=0) return -2;
		fout.write(buffer, fs.ssize);
		fs.read += fs.ssize;
	}
	fout.close();
	return 0;
}
