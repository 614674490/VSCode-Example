/*
 * @Author: liguiyin
 * @Date: 2019-12-03 15:10:01
 * @LastEditTime: 2019-12-06 11:28:12
 * @Description: README
 * @FilePath: \Sort\include\config.h
 */
#ifndef _config_h
#define _config_h

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "math.h"
#define MAXLEN 100
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASLIBLE -1 //不可行的
#define OVERFLOW -2    //溢出
//Status 函数返回值类型
typedef int Status;

void printTip(char *str);
void printError(char *str);

#endif
