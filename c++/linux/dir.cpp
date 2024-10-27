#include<iostream>
#include<unistd.h>
#include<dirent.h>
using namespace std;

int main()
{
	char buf[255];
	if(getcwd(buf, 255) == NULL)
		cout << "error" << endl;
	else cout << buf << endl;

	DIR *ddir;
	if((ddir = opendir(buf)) == NULL)
		cout << "error" << endl;

	struct dirent* entry;
	while((entry = readdir(ddir)) != NULL)
		cout << entry->d_name << endl;
	closedir(ddir);

	return 0;
}
