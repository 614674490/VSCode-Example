#ifndef _config_h
#define _config_h

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAXLEN 100
//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASLIBLE -1 //�����е�
#define OVERFLOW -2    //���
//Status ��������ֵ����
typedef int Status;

void printTip(char *str);
void printError(char *str);

#endif
