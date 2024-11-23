#include <stdio.h>
int main(int argv, char *argc[]) {
	printf("传入了 %d 个参数\n",argv);
	for(int i = 0; i < argv; i++) 
		printf("第%d个参数: %s\n",i+1,argc[i]);
	return 0;
}
