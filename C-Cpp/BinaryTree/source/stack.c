#include "stack.h"
#include "assert.h"
/**
 * @brief   ³õÊ¼»¯¶ÑÕ»
 * @param[in]   ¶ÑÕ»Ö¸Õë
 * @retval  Status
 **/
Status InitStack(linkStackPtr *s)
{
    if(!(*s = (linkStack *)malloc(sizeof(linkStack))))
    {
        printError("ÄÚ´æÒç³ö");
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
 * @brief   ÅĞÕ»¿Õ
 * @param[in]   ¶ÑÕ»Ö¸Õë
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
 * @brief   Ïú»ÙÕ»
 * @param[in]   ¶ÑÕ»Ö¸Õë
 * @retval  Status
 **/
Status freeStack(linkStack* pStackNode)
{
    stackNodePtr p = NULL;
    if(NULL == pStackNode)
        return FALSE;

    assert(NULL != pStackNode->top);
    p = pStackNode->top->next; //±£´æÏÂÒ»¸ö½áµã

    while(pStackNode->count && p){
        p = pStackNode->top->next;//±£´æ
        free(pStackNode->top);
        pStackNode->top = p;//ÖØĞÂ¸³ÖµÕ»¶¥Ö¸Õë
        pStackNode->count--;
    }
    return TRUE;
}
/**
 * @brief   Õ»ÖÃ¿Õ
 * @param[in]   ¶ÑÕ»Ö¸Õë
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
 * @brief   »ñÈ¡Õ»¶¥ÔªËØ
 * @param[in]   ¶ÑÕ»
 * @retval  Status
 **/
BinaryTreeTp *getStackTop(linkStack S)
{
    return S.top->elem;
}
/**
 * @brief   ÈëÕ»
 * @param[in]   ¶ÑÕ»Ö¸Õë ÈëÕ»ÔªËØ
 * @retval  Status
 **/
Status StackPush(linkStack *s, BinaryTreePtr T)
{
    stackNodePtr p;
    if(!(p= (stackNodePtr)malloc(sizeof(stackNode))))
    {
        printError("ÄÚ´æÒç³ö");
        return OVERFLOW;
    }
    p->elem = T;
	p->next = s->top;//ÍùÉÏÈëÕ»
	s->top = p;
    s->count += 1;
    return OK;
}
/**
 * @brief   ³öÕ»
 * @param[in]   ¶ÑÕ»Ö¸Õë ³öÕ»ÔªËØ
 * @retval  Status
 **/
Status StackPop(linkStack *s, BinaryTreePtr *T)
{
    stackNodePtr p;
    if(StackIsEmpty(*s))
    {
        printError("¶ÑÕ»Îª¿Õ");
        return ERROR;
    }
    else
    {
        *T = s->top->elem;
        p = s->top;
        s->top = s->top->next;
        free(p);  //ÊÍ·Å³öÕ»½áµã
        s->count -= 1;
        return OK;
    }
}
