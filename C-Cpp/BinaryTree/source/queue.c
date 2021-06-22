#include "queue.h"
/**
 * @brief   ��ʼ��ѭ������
 * @param[in]   ѭ������ָ��
 * @retval  Status
 **/
Status InitQueue(Queue *queue)
{
    queue->base=(BinaryTreePtr *)malloc(sizeof(BinaryTreePtr)*MAXLEN);
    if(!(queue->base))
    {
        printError("�ڴ����");
        return OVERFLOW;
    }
    queue->front = 0;
    queue->rear = 0;
    return OK;
}
/**
 * @brief   ����г���
 * @param[in]   ѭ������ָ��
 * @retval  ���г���
 **/
int getLength(Queue *queue)
{
    return (queue->rear - queue->front + MAXLEN) % MAXLEN;;
}
/**
 * @brief   �ж���
 * @param[in]   ѭ������ָ��
 * @retval  ��������TRUE FALSE
 **/
Status  QueueuIsFull(Queue *queue)
{
     if((queue->rear+1%MAXLEN) == queue->front)
        return TRUE;
     else
        return FALSE;
}
/**
 * @brief   �жӿ�
 * @param[in]   ѭ������ָ��
 * @retval  �ӿշ���TRUE ���򷵻�FALSE
 **/
Status  QueueuIsEmpty(Queue *queue)
{
    if(queue->front==queue->rear)
        return TRUE;
     else
        return FALSE;
}
/**
 * @brief   ���
 * @param[in]   ѭ������ָ�� ������
 * @retval  Status
 **/
Status EnQueue(Queue *queue,BinaryTreeTp *T)
{
    if(QueueuIsFull(queue))
    {
        printError("��������");
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
 * @brief   ����
 * @param[in]   ѭ������ָ�� ����Ԫ��
 * @retval  Status
 **/
Status DeQueue(Queue *queue,BinaryTreePtr *T)
{
    if(QueueuIsEmpty(queue))
    {
        printError("����Ϊ��");
        return ERROR;
    }
    else
    {
        queue->front = (queue->front + 1) % MAXLEN;
        *T = queue->base[queue->front];
        return OK;
    }
}
