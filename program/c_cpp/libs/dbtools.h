/*
Copyright(c)  2025  Rangersly  All rights reserved.

DEBUG 工具封包

Version: v0.1-Alpha
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
    /* 字符串检查宏,输出字符串的每一位数据*/
    #define POINT_STR(str, len) size_t _len = (size_t)len; \
    printf("%s\033[0m\n", str); \
    for(int i = 0; i < _len; i++) { \
        printf("%d --- %2x \n", i, (char)str[i], (unsigned char)str[i]);}

    /*输出调试错误报错信息,辅助定位错误地点*/
    #define PERROR(str) printf("%s:%d:%s:\n%s\n", __FILE__, __LINE__, __func__, str); exit(0)
#else
    #define POINT_STR(str, len)
    #define PERROR(str)
#endif

