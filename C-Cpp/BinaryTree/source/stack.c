#include "stack.h"
#include "assert.h"
/**
 * @brief   ��ʼ����ջ
 * @param[in]   ��ջָ��
 * @retval  Status
 **/
Status InitStack(linkStackPtr *s)
{
    if(!(*s = (linkStack *)malloc(sizeof(linkStack))))
    {
        printError("�ڴ����");
        return OVERFLOW;
    }
    else
    {
        (*s)->top=NULL;
        (*s)->count = 0;
        return OK;
    }

}
/**
 * @brief   ��ջ��
 * @param[in]   ��ջָ��
 * @retval  Status
 **/
Status StackIsEmpty(linkStack s)
{
    if(s.top==NULL)
        return TRUE;
    else
        return FALSE;
}
/**
 * @brief   ����ջ
 * @param[in]   ��ջָ��
 * @retval  Status
 **/
Status freeStack(linkStack* pStackNode)
{
    stackNodePtr p = NULL;
    if(NULL == pStackNode)
        return FALSE;

    assert(NULL != pStackNode->top);
    p = pStackNode->top->next; //������һ�����

    while(pStackNode->count && p){
        p = pStackNode->top->next;//����
        free(pStackNode->top);
        pStackNode->top = p;//���¸�ֵջ��ָ��
        pStackNode->count--;
    }
    return TRUE;
}
/**
 * @brief   ջ�ÿ�
 * @param[in]   ��ջָ��
 * @retval  Status
 **/
Status clearStack(linkStack* S)
{
    if(!StackIsEmpty(*S))
        return ERROR;
    S->top = NULL;
    S->count = 0;
    S->top = NULL;
    return OK;
}
/**
 * @brief   ��ȡջ��Ԫ��
 * @param[in]   ��ջ
 * @retval  Status
 **/
BinaryTreeTp *getStackTop(linkStack S)
{
    return S.top->elem;
}
/**
 * @brief   ��ջ
 * @param[in]   ��ջָ�� ��ջԪ��
 * @retval  Status
 **/
Status StackPush(linkStack *s, BinaryTreePtr T)
{
    stackNodePtr p;
    if(!(p= (stackNodePtr)malloc(sizeof(stackNode))))
    {
        printError("�ڴ����");
        return OVERFLOW;
    }
    p->elem = T;
	p->next = s->top;//������ջ
	s->top = p;
    s->count += 1;
    return OK;
}
/**
 * @brief   ��ջ
 * @param[in]   ��ջָ�� ��ջԪ��
 * @retval  Status
 **/
Status StackPop(linkStack *s, BinaryTreePtr *T)
{
    stackNodePtr p;
    if(StackIsEmpty(*s))
    {
        printError("��ջΪ��");
        return ERROR;
    }
    else
    {
        *T = s->top->elem;
        p = s->top;
        s->top = s->top->next;
        free(p);  //�ͷų�ջ���
        s->count -= 1;
        return OK;
    }
}
