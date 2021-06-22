#include "binarytree.h"
#include "queue.h"
#include "stack.h"
//遍历讲解：https://blog.csdn.net/Monster_ii/article/details/82115772
/**
 * Example 1
 * 前序遍历：ABD##E##CF##G## ABDECFG
 * 中序遍历：#D#B#E#A#F#C#G# DBEAFCG
 * 后序遍历：##D##EB##F##GCA DEBFGCA
 * 层序遍历：ABCDEFG########
 * Example 2
 * 前序遍历：ABC###DE#F###
 * 程序运行后得到的输出结果为：
 * 叶子个数为 2,  总结点个数为 6
 * 先序遍历：ABCDEF
 * 中序遍历：CBAEFD
 * 后序遍历：CBFEDA
 * 层次遍历：ABDCEF
 **/
/**
 * @brief   打印输出函数
 * @param[in]   打印数据
 * @retval  Status
 **/
Status funPrint(BinaryTreePtr *T)
{
    if (*T)
        printf("%c", (*T)->data);
}

/**
 * @brief   构造空二叉树T
 * @param[in]   二叉树结构体指针
 * @retval  Status
 **/
Status InitBinaryTree(BinaryTreePtr *T)
{
    *T = (BinaryTreePtr)malloc(sizeof(BinaryTreeTp)); //分配内存
    if (!*T)
    {
        printError("内存溢出");
        return OVERFLOW;
    }
    return OK; //分配成功返回OK
}

/**
 * @brief   先序遍历创建二叉树
 * @param[in]   二叉树结构体指针
 * @retval  Status
 **/
Status PreOrderCreat(BinaryTreePtr *T)
{
    DataType data;                 //定义char变量
    if ((data = getchar()) == END) //空指针以‘#’字符代替，字符连续输入，以按回车键表示结束。
    {
        *T = NULL;
        return OK;
    }
    else
    {
        if (InitBinaryTree(T)!=OK)
        {
            printError("内存溢出");
            return OVERFLOW;
        }
        (*T)->data = data;
        PreOrderCreat(&((*T)->lchild));
        PreOrderCreat(&((*T)->rchild));
    }
    return OK;
}

/**
 * @brief   层次遍历创建二叉树
 * @param[in]   二叉树结构体指针
 * @retval  Status
 * @note 对于满二叉树 在输入扩展序列时，要再补齐一级
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
        (*T)->data = data;                  //添加根节点
        EnQueue(&queue, *T);
    }
    while (!QueueuIsEmpty(&queue)) //队列非空 执行循环
    {
        DeQueue(&queue, &p);
        if ((data = getchar()) == END) //先输入左孩子的值，再输入右孩子值
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
    free(((&queue)->base)); //使用完临时队列后释放内存
    return OK;
}
/**
 * @brief   销毁二叉树
 * @param[in]   二叉树结构体指针
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
 * @brief   置空二叉树
 * @param[in]   二叉树结构体指针
 * @retval  Status
**/
Status ClearTree(BinaryTreePtr T)
{
	if (T)
		T = NULL;
	return OK;
}
/**
 * @brief   先序遍历二叉树
 * @param[in]   二叉树结构体指针 操作函数指针
 * @retval  Status
 **/
Status PreOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    static int count = 0; //记录堆栈进出栈 进栈+1 出栈-1
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
        count--; //递归遍历完后后 count为-1
        if (count == -1)
        {
            printf("\n");
            count = 0; //上次递归遍历完成 count置零 打印换行
        }
        return OK;
    }
}
/**
 * @brief   中序遍历二叉树
 * @param[in]   二叉树结构体指针 操作函数指针
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
        count--; //递归遍历完后后 count为-1
        if (count == -1)
        {
            printf("\n");
            count = 0; //上次递归遍历完成 count置零 打印换行
        }
        return OK;
    }
}
/**
 * @brief   后序遍历二叉树
 * @param[in]   二叉树结构体指针 操作函数指针
 * @retval  Status
 **/
Status PostOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    static int count = -2;
    DataType root; //记录二叉树的根结点
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
            count = -2; //用于下次遍历
        }
    }
    else
    {
        count--;
        return OK;
    }
}
/**
 * @brief   层次遍历二叉树 队列实现
 * @param[in]   二叉树结构体指针 操作函数指针
 * @retval  Status
 * @note    创建一个队列，先将根节点（A）入队，然后用front指针将根节点记下来，
 * 再将根节点出队，接下来看front节点（也就是刚才的根节点）有没有左孩子或右孩子，
 * 如果有，先左（B）后右（C）入队，最后输出front节点的值，只要队列还不为空，
 * 就说明还没有遍历完，就进行下一次循环，这时的队头元素（front）则为刚才入队的左孩子（B），
 * 然后front出队，再把它的左右孩子拉进来（如果有），因为队列的先进先出性质，
 * B的左右孩子DE是排在C后面的，然后输出B，下一次循环将会拉人C的左右孩子FG，
 * 最后因为FG没有左右孩子，一直出队，没有入队元素，
 * 队列迟早会变为空，当队列为空时，整颗树就层序遍历完成了，结束循环
 **/
Status LevelOrderTraverse_Queue(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    Queue queue;
    InitQueue(&queue);
    BinaryTreeTp *p = T;         //指向根节点
    EnQueue(&queue, p);//根节点入队
    while (QueueuIsEmpty(&queue)) //队列非空 执行循环
    {
        DeQueue(&queue, &p);
        Visit(&p);
        if (p->lchild) //如果有左孩子 则入队
            EnQueue(&queue, p->lchild);
        if (p->rchild) //如果有右孩子 则入队
            EnQueue(&queue, p->rchild);
    }
    printf("\n");
    free(((&queue)->base)); //使用完临时队列后释放内存
    return OK;
}
/**
 * @brief   先序非递归遍历
 * @param[in]   二叉树结构体指针 操作函数指针
 * @retval  Status
 **/
Status PreOrderLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    linkStackPtr s;
    InitStack(&s);
    BinaryTreeTp *cur = T;
    StackPush(s, cur); //根指针进栈
    while(!StackIsEmpty(*s))
    {
        while(cur) //只要当前结点非空便打印并压栈 再指向左孩子
        {
            Visit(&cur);
            StackPush(s, cur);
            cur = cur->lchild;
        }
        //否则弹出
        if(!StackIsEmpty(*s))
        {
            StackPop(s,&cur);
            cur = cur->rchild; //左子树遍历完成后，返回遍历右子树
        }
    }
    printf("\n");
    return OK;
}
/**
 * @brief   中序非递归遍历
 * @param[in]   二叉树结构体指针 操作函数指针
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
        while(cur) //先将左子树遍历到尽头
        {
            StackPush(s, cur);
            cur = cur->lchild;
        }
        //否则弹出
        if(!StackIsEmpty(*s))
        {
            StackPop(s,&cur);
            Visit(&cur);
            cur = cur->rchild; //然后遍历右子树(->左子树)
        }

    }
    printf("\n");
    return OK;
}
/**
 * @brief   后序非递归遍历
 * @param[in]   二叉树结构体指针 操作函数指针
 * @retval  Status
 * @note:后序遍历的非递归同样要借助一个栈来保存元素，
 * @note:栈中保存的元素是它的右子树和自身都没有被遍历到的节点，
 * @note:与中序遍历不同的是先访问右子树，在回来的时候再输出根节点的值。
 * @note:需要多一个last指针指向上一次访问到的节点，
 * @note:用来确认是从根节点的左子树返回的还是从右子树返回的。
 **/
Status LevelOrederLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *))
{
    if(!T)
        return OK;
    linkStackPtr s;
    InitStack(&s);
    BinaryTreeTp *cur = T;
    BinaryTreeTp *top=NULL;
    BinaryTreeTp *pre=NULL; //记录上一次返回结点
    while(!StackIsEmpty(*s)||cur)
    {
        while(cur) //先将左子树遍历到尽头
        {
            StackPush(s, cur);
            cur = cur->lchild;
        }
        //从栈中看一下栈顶元素（只看一眼，用top指针记下，先不出栈），
        //如果top节点没有右子树，或者last等于top的右孩子，
        //说明top的右子树不存在或者遍历过了，就输出top节点的值，
        //并将栈顶元素pop掉（出栈），反之则是从左子树回到根节点的，
        //接下来要去右子树。
        top = getStackTop(*s);
        if(top->rchild == NULL || top->rchild == pre)
        {//右孩子为空 或者右孩子已经遍历完成 则输出打印
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
 * @brief   递归创建二叉树
 * @param[in]   二叉树结构体指针 创建方式(先序 中序 后序)
 * @retval  Status
**/
Status CreatBinaryTree(BinaryTreePtr *T, TraversalMethod Order)
{
    switch (Order)
    {
    case PreOrder:
        printTip("先序创建二叉树");
        return PreOrderCreat(T);
    case LevelOrder:
        printTip("层次创建二叉树");
        return LevelOrderCreat(T);
    }
}
/**
 * @brief   二叉树输出打印
 * @param[in]   二叉树结构体指针 打印方式(先序 中序 后序)
 * @retval  Status
 **/
Status PrintBinaryTree(BinaryTreePtr T, TraversalMethod Order)
{
    switch (Order)
    {
    case PreOrder:
        printTip("先序打印二叉树");
        return PreOrderTraverse(T, funPrint);
    case InOrder:
        printTip("中序打印二叉树");
        return InOrderTraverse(T, funPrint);
    case PostOrder:
        printTip("后序打印二叉树");
        return PostOrderTraverse(T, funPrint);
    case LevelOrder:
        printTip("层次打印二叉树");
        return LevelOrderTraverse_Queue(T, funPrint);
    }
}
/**
 * @brief   二叉树非递归输出打印
 * @param[in]   二叉树结构体指针 打印方式(先序 中序 后序)
 * @retval  Status
 **/
Status PrintLoopBinaryTree(BinaryTreePtr T)
{
    printTip("先序打印二叉树");
    PreOrderLoopTraverse(T,funPrint);
    printTip("中序打印二叉树");
    InOrederLoopTraverse(T, funPrint);
    printTip("后序打印二叉树");
    LevelOrederLoopTraverse(T, funPrint);
}
/**
 * @brief   求叶子结点个数操作
 * @param[in]   二叉树结构体指针
 * @retval  叶子结点个数
 * @note 递归实现
**/
int getBinaryTreeLeafNum(BinaryTreePtr T)
{
    int lnum, rnum;
    if (!T) //空树 叶子节点数目为0
        return 0;
    else if (!T->lchild && !T->rchild) //只有根节点 叶子节点数目为1
        return 1;
    else //至少有一个孩子 子树叶子数=左子树叶子数+右子树叶子数 进行递归
    {
        lnum = getBinaryTreeLeafNum(T->lchild);
        rnum = getBinaryTreeLeafNum(T->rchild);
        return lnum + rnum;
    }
}
/**
 * @brief   求结点总数操作
 * @param[in]   二叉树结构体指针
 * @retval  结点总数
 * @note 递归实现
 **/
int getBinaryTreeNodeNum(BinaryTreePtr T)
{
    int lnum, rnum;
    if (!T)
        return 0; //空树返回零
    else
    {
        lnum = getBinaryTreeNodeNum(T->lchild);
        rnum = getBinaryTreeNodeNum(T->rchild);
        return lnum + rnum + 1;
    }
}
/**
 * @brief   求树的深度
 * @param[in]   二叉树结构体指针
 * @retval  树的深度
 * @note depth=[log2n」+1(n为二叉树的结点 取下整数)
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
 * @brief   打印二叉树信息
 * @param[in]   二叉树结构体指针
 * @retval  null
 **/
void printBinaryTreeMes(BinaryTreePtr T)
{
    printTip("叶子结点数目");
    printf("LeafNum=%d\n", getBinaryTreeLeafNum(T));
    printTip("结点数目");
    printf("NodeNum=%d\n", getBinaryTreeNodeNum(T));
    printTip("树的深度");
    printf("Depth=%d\n", getBinaryTreeDepth(T));
}
