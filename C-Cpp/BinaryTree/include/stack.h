#ifndef _statck_h
#define _statck_h
#include "binarytree.h"
#include "config.h"
//��ջ������ʽ�洢�ṹ
typedef struct StackNode{
	BinaryTreePtr elem;
	struct StackNode *next;
} stackNode, *stackNodePtr;
typedef struct LinkStack{
	stackNodePtr top; //ջ��ָ�� ʼ��ָ��ջ��Ԫ��
	int count;
} linkStack,*linkStackPtr;

Status InitStack(linkStackPtr *s);
Status StackIsEmpty(linkStack s);
BinaryTreeTp *getStackTop(linkStack S);
Status freeStack(linkStack *pStackNode);
Status clearStack(linkStack *S);
Status StackPush(linkStack *s, BinaryTreePtr T);
Status StackPop(linkStack *s, BinaryTreePtr *T);

#endif
