#include <iostream>
#include <unistd.h>
#include <termio.h>

static struct termios original;

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

int kbhit() {
    char ch;
    int n = read(STDIN_FILENO, &ch, 1);
    if (n == 1) return ch;
    return -1;
}

int main() {
    enable_raw_mode();
    atexit(disable_raw_mode); // 确保程序退出时恢复终端

    printf("Press 'q' to quit\n");
    while (1) {
        int key = kbhit();
        if (key != -1) {
            printf("Key: %c (0x%02x)\n", key, key);
            if (key == 'q') break;
        }

        // 在这里添加逻辑
        usleep(10000); // 10ms延迟减少CPU占用
    }

    return 0;
}
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


