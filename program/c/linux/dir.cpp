#include<iostream>
#include<unistd.h>		//目录操作
#include<dirent.h>		//获取目录列表
using namespace std;

int main()
{
	//目录操作

	char *getcwd(char *buf, size_t size);	//获取当前工作目录
	// 函数内用malloc()分配内存，要注意使用free()释放

	int chdir(const char *path);	//切换工作目录

	int mkdir(const char *path_name, mode_t mode);	//创建目录
	//mode为权限，如0775，不可省略0

	int rmdir(const char *path);		//删除目录
	
	
	//获取目录列表
	
	//步骤一
	DIR *opendir(const char *path_name);	//打开文件目录

	//步骤二
	struct dirent *readdir(DIR *dirp);		//返回struct dirent结构体地址,一次只读取一项

	//步骤三
	int closedir(DIR *dirp);				//关闭目录

/*
	DIR *目录指针

	struct dirent {
	 	long d_ino;					//inode number
	 	off_t d_off；				// 在目录文件中的偏移
		unsigned short d_reclen;	//文件名长度
		unsigned char d_type;		//文件类型 8-常规文件 4-目录 
		char d_name[NAME_MAX+1];	//文件名，最长255
	}
*/	

/*
	int access(const char *path_name, int mode);	//可以用来判断用户有没有对文件和目录的权限
	#define R_OK 4		//读
	#define W_OK 4		//写
	#define X_OK 4		//执行
	#define F_OK 4		//存在
*/

// 重命名文件
// int rename(const char *oldpath, const char *newpath)

// 删除文件
// int remove(const char *path_name)

/*
	#include <sys/stat.h>

	struct stat {		//存放文件或目录的信息(不完整)
		dev_t st_dev;	//设备编号
		ino_t st_ino;	//i-node
		mode_t st_mode;	//类型和权限
		uid_t st_uid;	//所有者uid
		gid_t st_gid;	//所有组
		off_t st_size;	//大小
		size_t st_blocks;		//占用文件系统区块数
		time_t st_atime;		//最后一次被存取或执行
		time_t st_mtime;		//最后一次被修改
		time_t st_ctime;		//最后一次属性被更改
	}
	
	S_ISREG(st_mode)	//文件为真
	S_ISDIR(st_mode)	//目录为真

	int stat(const char *path, struct stat *buf);	//获取信息,存到buf中
*/

/*
	示例
	DIR *dir;
	if( (dir=opendir(argv[1])) == nullptr) return -1;
	struct dirent *info=nullptr;

	while(1) {
		if( (info=readdir(dir)) == nullptr) break;
		cout << "d_name" << info->d_name << endl;
		cout << "d_type" << (int)info->d_type << endl;
	}

	closedir(dir);
*/
	return 0;
}
