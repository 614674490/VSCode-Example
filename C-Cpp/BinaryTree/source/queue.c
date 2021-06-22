#include "queue.h"
/**
 * @brief   初始化循环队列
 * @param[in]   循环队列指针
 * @retval  Status
 **/
Status InitQueue(Queue *queue)
{
    queue->base=(BinaryTreePtr *)malloc(sizeof(BinaryTreePtr)*MAXLEN);
    if(!(queue->base))
    {
        printError("内存溢出");
        return OVERFLOW;
    }
    queue->front = 0;
    queue->rear = 0;
    return OK;
}
/**
 * @brief   求队列长度
 * @param[in]   循环队列指针
 * @retval  队列长度
 **/
int getLength(Queue *queue)
{
    return (queue->rear - queue->front + MAXLEN) % MAXLEN;;
}
/**
 * @brief   判队满
 * @param[in]   循环队列指针
 * @retval  队满返回TRUE FALSE
 **/
Status  QueueuIsFull(Queue *queue)
{
     if((queue->rear+1%MAXLEN) == queue->front)
        return TRUE;
     else
        return FALSE;
}
/**
 * @brief   判队空
 * @param[in]   循环队列指针
 * @retval  队空返回TRUE 否则返回FALSE
 **/
Status  QueueuIsEmpty(Queue *queue)
{
    if(queue->front==queue->rear)
        return TRUE;
     else
        return FALSE;
}
/**
 * @brief   入队
 * @param[in]   循环队列指针 二叉树
 * @retval  Status
 **/
Status EnQueue(Queue *queue,BinaryTreeTp *T)
{
    if(QueueuIsFull(queue))
    {
        printError("队列已满");
        return ERROR;
    }
    else
    {
        queue->rear = (queue->rear+1)%MAXLEN;
        queue->base[queue->rear] = T;
        return OK;
    }
}
/**
 * @brief   出队
 * @param[in]   循环队列指针 出队元素
 * @retval  Status
 **/
Status DeQueue(Queue *queue,BinaryTreePtr *T)
{
    if(QueueuIsEmpty(queue))
    {
        printError("队列为空");
        return ERROR;
    }
    else
    {
        queue->front = (queue->front + 1) % MAXLEN;
        *T = queue->base[queue->front];
        return OK;
    }
}
