#include <stdio.h>
#include <ncurses.h>

char fastRead();

int main() {
	char ch;
	printf("Please down any key\n");
	ch = fastRead();
	printf("down : %c --- %d\n", ch, (int)ch);
	return 0;
}
char fastRead() {
	char ch;
	filter();     // 阻止initscr 清空屏幕
	initscr();	  // 初始化
	cbreak();	  // 禁用缓冲区
	noecho();     // 禁用回显
	keypad(stdscr, TRUE);
	ch = getchar();
	refresh();	  // 刷新
	endwin();     // 关闭
	return ch;
}
