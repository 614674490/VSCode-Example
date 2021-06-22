#include "config.h"
#include "stdio.h"
/**
 * @brief   提示信息输出
 * @param[in]   提示信息
 * @retval  null
 **/
void printTip(char *str)
{
    printf("→_→\t%s\t←_←\n", str);
}
/**
 * @brief   错误信息输入
 * @param[in]   提示信息
 * @retval  null
 **/
void printError(char *str)
{
    printf("ERROR:%s\n",str);
}
