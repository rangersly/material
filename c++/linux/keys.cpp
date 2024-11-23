#include <iostream>
#include <unistd.h>
#include <termio.h>

using namespace std;

int key() {
	//  struct termios
	//    {
	//      tcflag_t c_iflag;		/* input mode flags */
	//      tcflag_t c_oflag;		/* output mode flags */
	//      tcflag_t c_cflag;		/* control mode flags */
	//      tcflag_t c_lflag;		/* local mode flags */
	//      cc_t c_line;			/* line discipline */
	//      cc_t c_cc[NCCS];		/* control characters */
	//      speed_t c_ispeed;		/* input speed */
	//      speed_t c_ospeed;		/* output speed */
	//  #define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
	//  #define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
	//    };
	unsigned char in;
	struct termios new_settings, old_settings;
	tcgetattr(STDIN_FILENO,&old_settings); //获得stdin 输入
	new_settings = old_settings;
	new_settings.c_lflag &= (~ICANON);
//	new_settings.c_cc[VTIME] = 0;
//	tcgetattr(STDIN_FILENO,&old_settings); //获得stdin 输入
//	new_settings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO,TCSANOW,&new_settings); //
	
	in = getchar();
	
	tcsetattr(STDIN_FILENO,TCSANOW,&old_settings);
	return in;
}

int main() {
	while(1)
		printf(" %d \n", key());
	return 0;
}
