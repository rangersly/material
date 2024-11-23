// 示例客户端程序
// 发送文件到服务端
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
int file_out(TN &, char *);	// 传入一个连接和文件路径

int main(int argc, char *argv[]) {
	if(argc != 2) {
		cout << "Using: ./cli.exe 文件名" << endl;
		return 0;
	}
	TN test1;
	if(test1.client("127.0.0.1","12345")!=0)
		return 0;
	cout << "连接已成功" << endl;
	cout << file_out(test1, argv[1]) << endl;
	cout << "连接断开" << endl;
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

int file_out(TN &tn, char *path) {	// 传入一个连接和文件路径
	const unsigned int BSIZE = 1024;
	char buffer[BSIZE];
	FileStat fs;
	fstream fin(path, ios::in|ios::binary);
	pton(fs.name, (const char *)path);
	fin.seekg(0, ios::end);
	fs.fsize = fin.tellg();
	fin.seekg(0, ios::beg);

	// 发送信息
	if(tn.out((FileStat *)&fs, sizeof(fs))!=0) return 0;
	if(tn.in((char *)buffer)!=0) return 0;		// 接收确认报文

	// 正式发送文件
	while(fin.good() && fs.fsize>fs.read) {
		memset(buffer, 0, sizeof(buffer));
		fs.ssize = (fs.fsize-fs.read)>BSIZE? BSIZE:(fs.fsize-fs.read);
		fin.read(buffer, fs.ssize);
		if(tn.out(buffer, fs.ssize)!=0) return -1;
		fs.read += fs.ssize;
	}
	fin.close();
	return 0;
}
