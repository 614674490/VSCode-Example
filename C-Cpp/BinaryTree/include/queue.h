#ifndef _queue_h
#define _queue_h
#include "config.h"
#include "binarytree.h"
//Ë³Ðò´æ´¢
typedef struct{
    BinaryTreePtr *base;
    int front, rear;
} Queue;

Status InitQueue(Queue *queue);
int getLength(Queue *queue);
Status QueueuIsFull(Queue *queue);
Status QueueuIsEmpty(Queue *queue);
Status EnQueue(Queue *queue, BinaryTreeTp *T);
Status DeQueue(Queue *queue, BinaryTreePtr *T);
#endif
