#include "log.h"

#ifdef NDEBUG
    #define POINT_STR(str)
    #define PERROR(str)
#else
    #define POINT_STR(str) for(int i = 0; i < strlen(str); i++) { \
        printf("%c --- %d\n", (char)str[i], (int)str[i]);}
    #define PERROR(str) printf(str);return
#endif

static int low_show_level                           = LOG_INFO;
static int log_number                               = 1;
static FILE *log_out_fp                             = NULL;
static char log_head_format[LOG_HEAD_MAX_FORMAT]    = "[%y-%m-%d-%n]";
static char log_head[LOG_HEAD_MAX_FORMAT << 3];


static int
get_loghead(void);
// 根据 log_head_format 生成日志头 log_head
// 有无法识别的符号返回 -1 成功返回0

static void
int_to_str(int num, char *restrict str);
// 将int 型数据转换成str
// 需要注意 str 要大于 int 的位数,否则将溢出


void
log_setoutfile(const char *restrict filename) {
    if((log_out_fp = fopen(filename, "w")) == NULL)
        PERROR("LOG: log_setoutfile open file fail !\n");
    return;
}

void
log_setlevel(int level) {
    if(level < LOG_INFO || level > LOG_FATAL) {  // 检测最低日志等级
        low_show_level = LOG_INFO;
        PERROR("LOG: log_setlevel level is > LOG_FATAL or < LOG_INFO\n");
    }
    low_show_level = level;
    return;
}

void
log_sethead(const char *restrict head) {
    if(strlen(head) >= LOG_HEAD_MAX_FORMAT)
        PERROR("LOG: log_sethead  head so long!\n");
    strncpy(log_head_format, head, LOG_HEAD_MAX_FORMAT);
    if(get_loghead())
        PERROR("LOG: log_sethead  have fail char !\n");
    return;
}

void
log_print(int level, const char *restrict message) {
    if(log_out_fp == NULL)              // 未设置输出文件
        log_out_fp = stdout;
    if(level < LOG_INFO || level > LOG_FATAL)  // 日志等级不在范围内
        PERROR("LOG: log_print level out of range !\n");
    if(level < low_show_level)  // 低于最低等级的log不进行打印
        return;

    if(get_loghead() != 0)      // 生成日志头
        PERROR("LOG: log_print get_loghead error\n");
    if(!fputs(log_head, log_out_fp))    // 打印日志头
        PERROR("LOG: log_print fputs_head error\n");

    switch(level) {    // 打印错误等级
        case LOG_INFO: 
            if(fputs("INFO:", log_out_fp))
                break;
        case LOG_WARNING: 
            if(fputs("WARNING:", log_out_fp))
                break;
        case LOG_ERROR: 
            if(fputs("ERROR:", log_out_fp))
                break;
        case LOG_FATAL: 
            if(fputs("FATAL:", log_out_fp))
                break;
        default:
            PERROR("LOG: log_print out level is untrue !\n");
    }
    
    if(!fputs(message, log_out_fp))     // 打印message
        PERROR("LOG: log_head fputs fail !\n");
    fputc('\n', log_out_fp);
    log_number++;                   // 日志计数++
    return;
}    

int
get_loghead(void) {
    char buf[64];
    time_t now_time = time(NULL);
    clock_t core_time = clock() / CLOCKS_PER_SEC;  // 以 s 为单位的 cpu 时间
    struct tm *tm_time = localtime(&now_time);
    int temp;

    memset(log_head, '\0', sizeof(log_head));           // 重置日志头

    for(int i = 0; i < strlen(log_head_format); i++) {
        if(log_head_format[i] != '%') {                 // 非特殊字符则按正常复制
            log_head[strlen(log_head)] = log_head_format[i];
            continue;
        }

        i++;
        switch(log_head_format[i]) {        // 特殊字符转换
            case 'y' :
                strftime(buf, 64, "%Y", tm_time);
                break;
            case 'm' :
                strftime(buf, 64, "%m", tm_time);
                break;
            case 'd' :
                strftime(buf, 64, "%d", tm_time);
                break;
            case 'h' :
                strftime(buf, 64, "%H", tm_time);
                break;
            case 'M' :
                strftime(buf, 64, "%M", tm_time);
                break;
            case 's' :
                strftime(buf, 64, "%S", tm_time);
                break;
            case 'n' :
                int_to_str(log_number, buf);
                break;
            case 'c' :
                int_to_str(core_time, buf);
                break;
            default: 
                return -1;
        }
        strcat(log_head, buf);
    }
    return 0;
}

void
int_to_str(int num, char *restrict str) {
    if(num < 0)
        return;      // 日志编号不可能小于 0

    // 逐位提取数字（反向存储）
    int start = 0;
    do {
        str[start++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    str[start] = '\0';

    // 反转数字部分
    char buf[16];
    strncpy(buf, str, 16);
    for(int i = 0; i < strlen(buf); i++)
        str[--start] = buf[i];
    return;
}

#undef POINT_STR
#undef PERROR
