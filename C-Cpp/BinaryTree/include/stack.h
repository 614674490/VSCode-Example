#ifndef _statck_h
#define _statck_h
#include "binarytree.h"
#include "config.h"
//堆栈采用链式存储结构
typedef struct StackNode{
	BinaryTreePtr elem;
	struct StackNode *next;
} stackNode, *stackNodePtr;
typedef struct LinkStack{
	stackNodePtr top; //栈顶指针 始终指向栈顶元素
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
