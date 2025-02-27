#	有关ioctl的使用

`#include <sys/ioctl.h>`

##	查询当前终端的长宽大小
```cpp
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	printf("%d\n%d\n", w.ws_col, w.ws_row);
```
