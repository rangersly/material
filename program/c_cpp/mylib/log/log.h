// Copyright(c)  2025  Rangersly  All rights reserved.
//
// function :
//  Output log
//
// Author:
//  Rangersly
//
// Versions:
//  - 1.0   base function

#pragma once

#include <stdio.h>
#include <string.h>
#include <time.h>

#define   LOG_INFO              0
#define   LOG_WARNING           1
#define   LOG_ERROR             2
#define   LOG_FATAL             3

#define LOG_HEAD_MAX_FORMAT     32

// 如果未定义 NDEBUG 宏,错误发生时将打印错误信息

extern void
log_setoutfile(const char *restrict filename);
// 设置输出文件
// 默认输出为 stdout

extern void
log_setlevel(int level);
// 设置最低输出日志等级,低于最低等级的日志将忽略
  
extern void
log_sethead(const char *restrict head);
// 设置日志头,最大不可超过15个字符
// 符号表
//  %y      year
//  %m      month
//  %d      day
//  %h      hour
//  %M      minute
//  %s      second
//  %n      number
//  %c      core time .3f

extern void
log_print(int level, const char *restrict message);
// 输出日志              ^---等级           ^---输出信息



// EXAMPLE
/*
#include <stdio.h>
#include "log.h"

int main(void) {
    log_setoutfile("log.out");
    log_setlevel(LOG_ERROR);
    log_sethead("#%d-%h-%M-%s-%n-%c#");

    log_print(LOG_INFO, " hello");
    log_print(LOG_WARNING, " hello");
    log_print(LOG_ERROR, " hello");
    log_print(LOG_FATAL, " hello");
    return 0;
}
*/
