#include "config.h"
#include "stdio.h"
/**
 * @brief   ��ʾ��Ϣ���
 * @param[in]   ��ʾ��Ϣ
 * @retval  null
 **/
void printTip(char *str)
{
    printf("��_��\t%s\t��_��\n", str);
}
/**
 * @brief   ������Ϣ����
 * @param[in]   ��ʾ��Ϣ
 * @retval  null
 **/
void printError(char *str)
{
    printf("ERROR:%s\n",str);
}
