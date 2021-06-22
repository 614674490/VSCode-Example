#include "binarytree.h"
#include "queue.h"
#include "stack.h"
//�������⣺https://blog.csdn.net/Monster_ii/article/details/82115772
/**
 * Example 1
 * ǰ�������ABD##E##CF##G## ABDECFG
 * ���������#D#B#E#A#F#C#G# DBEAFCG
 * ���������##D##EB##F##GCA DEBFGCA
 * ���������ABCDEFG########
 * Example 2
 * ǰ�������ABC###DE#F###
 * �������к�õ���������Ϊ��
 * Ҷ�Ӹ���Ϊ 2,  �ܽ�����Ϊ 6
 * ���������ABCDEF
 * ���������CBAEFD
 * ���������CBFEDA
 * ��α�����ABDCEF
 **/
/**
 * @brief   ��ӡ�������
 * @param[in]   ��ӡ����
 * @retval  Status
 **/
Status funPrint(BinaryTreePtr *T)
{
    if (*T)
        printf("%c", (*T)->data);
}

/**
 * @brief   ����ն�����T
 * @param[in]   �������ṹ��ָ��
 * @retval  Status
 **/
Status InitBinaryTree(BinaryTreePtr *T)
{
    *T = (BinaryTreePtr)malloc(sizeof(BinaryTreeTp)); //�����ڴ�
    if (!*T)
    {
        printError("�ڴ����");
        return OVERFLOW;
    }
    return OK; //����ɹ�����OK
}

/**
 * @brief   �����������������
 * @param[in]   �������ṹ��ָ��
 * @retval  Status
 **/
Status PreOrderCreat(BinaryTreePtr *T)
{
    DataType data;                 //����char����
    if ((data = getchar()) == END) //��ָ���ԡ�#���ַ����棬�ַ��������룬�԰��س�����ʾ������
    {
        *T = NULL;
        return OK;
    }
    else
    {
        if (InitBinaryTree(T)!=OK)
        {
            printError("�ڴ����");
            return OVERFLOW;
        }
        (*T)->data = data;
        PreOrderCreat(&((*T)->lchild));
        PreOrderCreat(&((*T)->rchild));
    }
    return OK;
}

/**
 * @brief   ��α�������������
 * @param[in]   �������ṹ��ָ��
 * @retval  Status
 * @note ������������ ��������չ����ʱ��Ҫ�ٲ���һ��
 **/
Status LevelOrderCreat(BinaryTreePtr *T)
{
    DataType data;
    Queue queue;
    if(InitQueue(&queue)!=OK)
        return OVERFLOW;
    BinaryTreeTp *p;
    if ((data = getchar()) == END)
    {
        *T = NULL;
        return OK;
    }
    else
    {
        if(InitBinaryTree(T)!=OK)
            return OVERFLOW;
        (*T)->data = data;                  //��Ӹ��ڵ�
        EnQueue(&queue, *T);
    }
    while (!QueueuIsEmpty(&queue)) //���зǿ� ִ��ѭ��
    {
        DeQueue(&queue, &p);
        if ((data = getchar()) == END) //���������ӵ�ֵ���������Һ���ֵ
            p->lchild = NULL;
        else
        {
            if (InitBinaryTree(&(p->lchild)) == OK)
            {
                p->lchild->data = data;
                EnQueue(&queue, p->lchild);
            }
            else
                return OVERFLOW;
        }
        if ((data = getchar()) == END)
        {
            p->rchild = NULL;
        }
        else
        {
            if (InitBinaryTree(&(p->rchild)) == OK)
            {
                p->rchild->data = data;
                EnQueue(&queue, p->rchild);
            }
            else
                return OVERFLOW;
        }
    }
    free(((&queue)->base)); //ʹ������ʱ���к��ͷ��ڴ�
    return OK;
}
/**
 * @brief   ���ٶ�����
 * @param[in]   �������ṹ��ָ��
 * @retval  Status
 **/
Status DestroyTree(BinaryTreePtr T)
{
	if (T)
	{
		DestroyTree(T->lchild);
		DestroyTree(T->rchild);
		free(T);
	}
	return OK;
}
/**
 * @brief   �ÿն�����
 * @param[in]   �������ṹ��ָ��
 * @retval  Status
**/
Status ClearTree(BinaryTreePtr T)
{
	if (T)
		T = NULL;
	return OK;
}
/**
 * @brief   �������������
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 **/
Status PreOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    static int count = 0; //��¼��ջ����ջ ��ջ+1 ��ջ-1
    if (T)
    {
        count++;
        if (Visit(&T))
            if (PreOrderTraverse(T->lchild, Visit))
                if (PreOrderTraverse(T->rchild, Visit))
                    return OK;
        return ERROR;
    }
    else
    {
        count--; //�ݹ�������� countΪ-1
        if (count == -1)
        {
            printf("\n");
            count = 0; //�ϴεݹ������� count���� ��ӡ����
        }
        return OK;
    }
}
/**
 * @brief   �������������
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 **/
Status InOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    static int count = 0;
    if (T)
    {
        count++;
        if (InOrderTraverse(T->lchild, Visit))
            if (Visit(&T))
                if (InOrderTraverse(T->rchild, Visit))
                    return OK;
        return ERROR;
    }
    else
    {
        count--; //�ݹ�������� countΪ-1
        if (count == -1)
        {
            printf("\n");
            count = 0; //�ϴεݹ������� count���� ��ӡ����
        }
        return OK;
    }
}
/**
 * @brief   �������������
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 **/
Status PostOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    static int count = -2;
    DataType root; //��¼�������ĸ����
    if (T)
    {
        if (count == -2)
        {
            root = T->data;
            count = 0;
        }

        count++;
        PostOrderTraverse(T->lchild, Visit);
        PostOrderTraverse(T->rchild, Visit);
        Visit(&T);
        if (count == -1 && T->data == root)
        {
            printf("\n");
            count = -2; //�����´α���
        }
    }
    else
    {
        count--;
        return OK;
    }
}
/**
 * @brief   ��α��������� ����ʵ��
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 * @note    ����һ�����У��Ƚ����ڵ㣨A����ӣ�Ȼ����frontָ�뽫���ڵ��������
 * �ٽ����ڵ���ӣ���������front�ڵ㣨Ҳ���Ǹղŵĸ��ڵ㣩��û�����ӻ��Һ��ӣ�
 * ����У�����B�����ң�C����ӣ�������front�ڵ��ֵ��ֻҪ���л���Ϊ�գ�
 * ��˵����û�б����꣬�ͽ�����һ��ѭ������ʱ�Ķ�ͷԪ�أ�front����Ϊ�ղ���ӵ����ӣ�B����
 * Ȼ��front���ӣ��ٰ��������Һ���������������У�����Ϊ���е��Ƚ��ȳ����ʣ�
 * B�����Һ���DE������C����ģ�Ȼ�����B����һ��ѭ����������C�����Һ���FG��
 * �����ΪFGû�����Һ��ӣ�һֱ���ӣ�û�����Ԫ�أ�
 * ���г�����Ϊ�գ�������Ϊ��ʱ���������Ͳ����������ˣ�����ѭ��
 **/
Status LevelOrderTraverse_Queue(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    Queue queue;
    InitQueue(&queue);
    BinaryTreeTp *p = T;         //ָ����ڵ�
    EnQueue(&queue, p);//���ڵ����
    while (QueueuIsEmpty(&queue)) //���зǿ� ִ��ѭ��
    {
        DeQueue(&queue, &p);
        Visit(&p);
        if (p->lchild) //��������� �����
            EnQueue(&queue, p->lchild);
        if (p->rchild) //������Һ��� �����
            EnQueue(&queue, p->rchild);
    }
    printf("\n");
    free(((&queue)->base)); //ʹ������ʱ���к��ͷ��ڴ�
    return OK;
}
/**
 * @brief   ����ǵݹ����
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 **/
Status PreOrderLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    linkStackPtr s;
    InitStack(&s);
    BinaryTreeTp *cur = T;
    StackPush(s, cur); //��ָ���ջ
    while(!StackIsEmpty(*s))
    {
        while(cur) //ֻҪ��ǰ���ǿձ��ӡ��ѹջ ��ָ������
        {
            Visit(&cur);
            StackPush(s, cur);
            cur = cur->lchild;
        }
        //���򵯳�
        if(!StackIsEmpty(*s))
        {
            StackPop(s,&cur);
            cur = cur->rchild; //������������ɺ󣬷��ر���������
        }
    }
    printf("\n");
    return OK;
}
/**
 * @brief   ����ǵݹ����
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 **/
Status InOrederLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    linkStackPtr s;
    InitStack(&s);
    BinaryTreeTp *cur = T;
    while(!StackIsEmpty(*s)||cur)
    {
        while(cur) //�Ƚ���������������ͷ
        {
            StackPush(s, cur);
            cur = cur->lchild;
        }
        //���򵯳�
        if(!StackIsEmpty(*s))
        {
            StackPop(s,&cur);
            Visit(&cur);
            cur = cur->rchild; //Ȼ�����������(->������)
        }

    }
    printf("\n");
    return OK;
}
/**
 * @brief   ����ǵݹ����
 * @param[in]   �������ṹ��ָ�� ��������ָ��
 * @retval  Status
 * @note:��������ķǵݹ�ͬ��Ҫ����һ��ջ������Ԫ�أ�
 * @note:ջ�б����Ԫ��������������������û�б��������Ľڵ㣬
 * @note:�����������ͬ�����ȷ������������ڻ�����ʱ����������ڵ��ֵ��
 * @note:��Ҫ��һ��lastָ��ָ����һ�η��ʵ��Ľڵ㣬
 * @note:����ȷ���ǴӸ��ڵ�����������صĻ��Ǵ����������صġ�
 **/
Status LevelOrederLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    linkStackPtr s;
    InitStack(&s);
    BinaryTreeTp *cur = T;
    BinaryTreeTp *top=NULL;
    BinaryTreeTp *pre=NULL; //��¼��һ�η��ؽ��
    while(!StackIsEmpty(*s)||cur)
    {
        while(cur) //�Ƚ���������������ͷ
        {
            StackPush(s, cur);
            cur = cur->lchild;
        }
        //��ջ�п�һ��ջ��Ԫ�أ�ֻ��һ�ۣ���topָ����£��Ȳ���ջ����
        //���top�ڵ�û��������������last����top���Һ��ӣ�
        //˵��top�������������ڻ��߱������ˣ������top�ڵ��ֵ��
        //����ջ��Ԫ��pop������ջ������֮���Ǵ��������ص����ڵ�ģ�
        //������Ҫȥ��������
        top = getStackTop(*s);
        if(top->rchild == NULL || top->rchild == pre)
        {//�Һ���Ϊ�� �����Һ����Ѿ�������� �������ӡ
            Visit(&top);
            StackPop(s,&pre);
        }
        else
            cur = top->rchild;
    }
    printf("\n");
    return OK;
}
/**
 * @brief   �ݹ鴴��������
 * @param[in]   �������ṹ��ָ�� ������ʽ(���� ���� ����)
 * @retval  Status
**/
Status CreatBinaryTree(BinaryTreePtr *T, TraversalMethod Order)
{
    switch (Order)
    {
    case PreOrder:
        printTip("���򴴽�������");
        return PreOrderCreat(T);
    case LevelOrder:
        printTip("��δ���������");
        return LevelOrderCreat(T);
    }
}
/**
 * @brief   �����������ӡ
 * @param[in]   �������ṹ��ָ�� ��ӡ��ʽ(���� ���� ����)
 * @retval  Status
 **/
Status PrintBinaryTree(BinaryTreePtr T, TraversalMethod Order)
{
    switch (Order)
    {
    case PreOrder:
        printTip("�����ӡ������");
        return PreOrderTraverse(T, funPrint);
    case InOrder:
        printTip("�����ӡ������");
        return InOrderTraverse(T, funPrint);
    case PostOrder:
        printTip("�����ӡ������");
        return PostOrderTraverse(T, funPrint);
    case LevelOrder:
        printTip("��δ�ӡ������");
        return LevelOrderTraverse_Queue(T, funPrint);
    }
}
/**
 * @brief   �������ǵݹ������ӡ
 * @param[in]   �������ṹ��ָ�� ��ӡ��ʽ(���� ���� ����)
 * @retval  Status
 **/
Status PrintLoopBinaryTree(BinaryTreePtr T)
{
    printTip("�����ӡ������");
    PreOrderLoopTraverse(T,funPrint);
    printTip("�����ӡ������");
    InOrederLoopTraverse(T, funPrint);
    printTip("�����ӡ������");
    LevelOrederLoopTraverse(T, funPrint);
}
/**
 * @brief   ��Ҷ�ӽ���������
 * @param[in]   �������ṹ��ָ��
 * @retval  Ҷ�ӽ�����
 * @note �ݹ�ʵ��
**/
int getBinaryTreeLeafNum(BinaryTreePtr T)
{
    int lnum, rnum;
    if (!T) //���� Ҷ�ӽڵ���ĿΪ0
        return 0;
    else if (!T->lchild && !T->rchild) //ֻ�и��ڵ� Ҷ�ӽڵ���ĿΪ1
        return 1;
    else //������һ������ ����Ҷ����=������Ҷ����+������Ҷ���� ���еݹ�
    {
        lnum = getBinaryTreeLeafNum(T->lchild);
        rnum = getBinaryTreeLeafNum(T->rchild);
        return lnum + rnum;
    }
}
/**
 * @brief   ������������
 * @param[in]   �������ṹ��ָ��
 * @retval  �������
 * @note �ݹ�ʵ��
 **/
int getBinaryTreeNodeNum(BinaryTreePtr T)
{
    int lnum, rnum;
    if (!T)
        return 0; //����������
    else
    {
        lnum = getBinaryTreeNodeNum(T->lchild);
        rnum = getBinaryTreeNodeNum(T->rchild);
        return lnum + rnum + 1;
    }
}
/**
 * @brief   ���������
 * @param[in]   �������ṹ��ָ��
 * @retval  �������
 * @note depth=[log2n��+1(nΪ�������Ľ�� ȡ������)
 **/
int getBinaryTreeDepth(BinaryTreePtr T)
{
    int LD, RD;
    if (!T)
        return 0;
    else
    {
        LD = getBinaryTreeDepth(T->lchild);
        RD = getBinaryTreeDepth(T->rchild);
        return ((LD > RD ? LD : RD) + 1);
    }
}
/**
 * @brief   ��ӡ��������Ϣ
 * @param[in]   �������ṹ��ָ��
 * @retval  null
 **/
void printBinaryTreeMes(BinaryTreePtr T)
{
    printTip("Ҷ�ӽ����Ŀ");
    printf("LeafNum=%d\n", getBinaryTreeLeafNum(T));
    printTip("�����Ŀ");
    printf("NodeNum=%d\n", getBinaryTreeNodeNum(T));
    printTip("�������");
    printf("Depth=%d\n", getBinaryTreeDepth(T));
}
