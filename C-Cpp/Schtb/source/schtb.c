/*
 * @Author: liguiyin
 * @Date: 2019-11-22 11:18:21
 * @LastEditTime: 2019-12-02 16:11:44
 * @Description: README
 * @FilePath: \Schtb\source\schtb.c
 */
#include "schtb.h"
#include "time.h"
/**
 * @brief   产生一组KeyType类型的不重复随机数
 * @param[in]   seed:随机数种子 0->time range : 0-range-1 key:存放数组 num:元素个数
 * @retval  Status
 **/
NodeType *_random(int seed, int num, int range)
{
    int i;
    int rand_num;
    if(range<num)
    {
        printError("元素个数不得超过随机数范围");
        num = range;
    }
    NodeType *key = (NodeType *)malloc(sizeof(NodeType)*num);
    key[0].Key = 0;
    if(!key)
    {
        printError("内存溢出!");
        return NULL;
    }
    int temp[range];
    for (i = 0; i < range;i++)
    {
        temp[i] = 0;
    }
    if(seed <= 0)
        srand( (unsigned)time( NULL ) );  //将时间作为种子
    else
        srand(seed);
    if(num<=(RAND_MAX+1))
        for (i = 1; i <=num; i++)
        {
            key[i].Key =rand()%range; //0-range
            if(!temp[key[i].Key])  //数据不重复
            {
                key[0].Key++;
                temp[key[i].Key] = 1;
            }
            else //数据重复
                i--;
        }
    else
    {
        if(!(num==range&&num>=33000))
        {
            for (i = 1; i <=num; i++)
            {
                key[i].Key = (rand() + (i / (RAND_MAX + 1)) * (RAND_MAX + 1)) % range;
                if(!temp[key[i].Key])  //数据不重复
                {
                    key[0].Key++;
                    temp[key[i].Key] = 1;
                }
                else //数据重复
                    i--;
            }
        }
        else
        {
            for (i = 1; i <=num-1; i++)
            {
                key[i].Key = (rand() + (i / (RAND_MAX + 1)) * (RAND_MAX + 1)) % range;
                if(!temp[key[i].Key])  //数据不重复
                {
                    key[0].Key++;
                    temp[key[i].Key] = 1;
                }
                else //数据重复
                    i--;
            }
            for (i = 0; i < range;i++)
            {
                if(!temp[i])  //手动寻找最后一个随机数
                {
                    key[num].Key = i;
                    key[0].Key++;
                }
            }
        }
    }
    return key;
}
/**
 * @brief   Init SeqTable
 * @param[in]   SerTable Struct , SeqTable_Length(不包括0地址)
 * @retval  Status
 * @note    加入监视哨,0地址存放查找关键字
 **/
Status Init_SeaTable(PtrSeaTable ST,int SeqTable_Length)
{
    if(SeqTable_Length>Random_Range)
    {
        printError("查询表长不得超过随机数范围!");
        SeqTable_Length = Random_Range;
    }
    if(ST->elem = (NodeType *)malloc((SeqTable_Length+1) * sizeof (NodeType)))
    {
        ST->length = SeqTable_Length+1;
        ST->elem[0].Key = 0;  //0地址赋初值
        return OK;
    }
    else
    {
        printError("内存溢出");
        return ERROR;
    }
}
/**
 * @brief       Random Creat SeqTable
 * @param[in]   SerTable Struct data_max
 * @retval      null
 **/
void Creat_SeaTable(SeaTable *ST,int data_max)
{
    (*ST).elem=random(Table_Random_Seed, (*ST).length - 1,data_max);
    (*ST).count = (*ST).elem[0].Key;
}
/**
 * @brief       排序查找表
 * @param[in]   SerTable Struct Key
 * @retval      NULL
 * @note        选择排序
 **/
void Sort_SeaTable(SeaTable ST)
{
   int i, j, k ;
   for(i=1; i<ST.length-1; i++)
   {
       k = i ;
       for(j=i+1; j<=ST.length-1; j++)
	   if (ST.elem[k].Key>ST.elem[j].Key) k = j ;
       if (k!=i)
       {
	       ST.elem[0] = ST.elem[i];
	       ST.elem[i] =ST.elem[k];
	       ST.elem[k] = ST.elem[0];
       }
   }
}

/**
 * @brief       顺序查找表
 * @param[in]   SerTable Struct Key
 * @retval      Key Pos 0表示未找到
 **/
int SeqSearch_SeaTable(SeaTable ST,KeyType Key)
{
    int i;
    ST.elem[0].Key = Key;
    for (i = ST.length-1; ST.elem[i].Key != Key;i--); //从后往前找
    return  i;                      //一直找到表头的0地址才退出则表明表中无此关键字
}
/**
 * @brief       折半查找表
 * @param[in]   SerTable Struct Key
 * @retval      Key Pos 0表示未找到
 **/
int BinSearch_SeaTable(SeaTable ST,KeyType Key)
{
    int low = 1, high = ST.length, mid;
    while(low<=high)
    {
        mid = (low + high) / 2;
        if(ST.elem[mid].Key==Key)   //找到待查元素
            return mid;
        else if(Key<ST.elem[mid].Key)   //继续在前半区间内查找
            high = mid - 1;
        else                            //继续在后半区间内查找
            low = mid + 1;
    }
    return 0;                           //顺序表中不存在待查找元素
}
/**
 * @brief       输出查找表数据
 * @param[in]   SerTable Struct
 * @retval      null
 **/
void print_SeaTable(SeaTable ST)
{
   int i ;
   for (i = 1; i < ST.length; i++)
   {
        printf("%5d", ST.elem[i].Key) ;
        if(!(i%20))
            printf("\n");
   }
   printf("\n") ;
}
/**
 * @brief       获取查询表查询时间
 * @param[in]   SeqTable NodeType Search_Fun()
 * @retval      time
 **/
int getTime_SearchST(SeaTable ST,NodeType *Key,int (*Search)(SeaTable,KeyType))
{
    int t_start, t_end;
    int i,num=0;
    char str[5];
    int data_length = Data_Length > Random_Range ? Random_Range : Data_Length;
    if(Search == BinSearch_SeaTable)
    {
        strcpy(str,(char *)"折半\0");
        t_start = clock();
        Sort_SeaTable(ST);
        t_end = clock();
        printf("选择排序时长：%dms\n", t_end - t_start);
    }
    else if(Search == SeqSearch_SeaTable)
        strcpy(str,(char *)"顺序\0");
    t_start  = clock();
    for (i = 0; i < data_length; i++)
    {
       if(Search(ST, Key[i].Key))
            num++;
    }
    t_end = clock();
    printf("%s查找时间\t：%dms\t成功查找到%d个元素\n",str,(int)(t_end - t_start),num);
    return t_end - t_start;
}
/**
 * @brief   构造空二叉排序树
 * @param[in]   二叉排序树结构体指针
 * @retval  Status
 **/
Status Init_BSTree(BSTree *BST)
{
    *BST = (BSTree)malloc(sizeof(BSTNode)); //分配内存
    if (!*BST)
    {
        printError("内存溢出");
        return OVERFLOW;
    }
    else
    {
        (*BST)->nodeNumber = 0;
        (*BST)->lchild = NULL;
        (*BST)->rchild = NULL;
        return OK; //分配成功返回OK
    }
}
/**
 * @brief       二叉排序树的查找操作
 * @param[in]   二叉排序树结构体指针 查找元素的关键字
 * @retval      BSTree若查找成功则返回结点指针 否则返回空指针
 * @note        不考虑插入
 **/
BSTNode *Search_BST(BSTree BST,KeyType Key)
{
    if((!BST)||(BST->elem.Key == Key))
        return BST;
    else if(Key<BST->elem.Key)
        return Search_BST(BST->lchild, Key);  //Key比根节点值小则在左子树继续查找
    else
        return Search_BST(BST->rchild, Key);  //在右子树继续查找
}
/**
 * @brief       二叉排序树的查找操作
 * @param[in]   二叉排序树结构体指针 查找元素的关键字 当前节点的双亲结点 查找元素所在结点
 * @retval      Status 查找成功返回TRUE 查找失败返回FALSE
 * @note        不考虑插入
 **/
Status SearchBST(BSTree BST,KeyType Key,BSTree Parent,BSTree *Keypos)
{
    if(!BST)
    {
        *Keypos = Parent;
        return FALSE;
    }
    else if(BST->elem.Key == Key)
    {
        *Keypos = BST;
        return TRUE;
    }
    else if(Key<BST->elem.Key)
        return SearchBST(BST->lchild, Key, BST, Keypos);
    else
        return SearchBST(BST->rchild, Key, BST, Keypos);
}
/**
 * @brief   二叉排序树的插入操作
 * @param[in]   二叉排序树结构体指针 插入元素
 * @retval  Status
 **/
Status Insert_BST(BSTree *BST,NodeType elem)
{
    BSTNode *f, *p = *BST ;//f指向要插入的双亲结点 p指向当前节点
    if(!SearchBST(*BST,elem.Key,NULL,&p))   //经查找后无相同元素则在p指向的结点的孩子结点位置插入元素
    {
        BSTNode *s;
        Init_BSTree(&s);
        s->elem = elem;
        if(!p)  //空树插入元素
            *BST = s;
        else if(elem.Key<p->elem.Key)
             p->lchild = s;     //s作为左孩子
        else
             p->rchild = s;     //s作为右孩子
        (*BST)->nodeNumber++;
        return TRUE;
    }
    else  //树中已有相同元素 不再插入
        return FALSE;
}
/**
 * @brief   二叉排序树的创建操作
 * @param[in]   二叉排序树结构体指针 结点个数
 * @retval  Status
 **/
Status Creat_BSTree(BSTree *BST,int nodeNumber)
{
    int i;
    *BST = NULL;
    if(nodeNumber>Random_Range)
    {
        printError("二叉树结点个数不得超过随机数范围!");
        nodeNumber = Random_Range;
    }
    NodeType *elem = random(Table_Random_Seed, nodeNumber, );
    for (i = 1; i <= nodeNumber;i++)
        Insert_BST(BST, *(elem+i));
    return OK;
}
/**
 * @brief:        二叉排序树的删除操作
 * @param[in]:    二叉排序树 删除关键字
 * @return:       Status
 * @note:         null
 */
Status _Del_BSTree(BSTree *BST,KeyType Key)
{
    if(!*BST)
        return FALSE;
    else if(Key==(*BST)->elem.Key)
        return Delete(BST);     //找到关键字所在位置则删除
    else if(Key<(*BST)->elem.Key)
        return _Del_BSTree(&(*BST)->lchild, Key);    //否则进行递归查找 找到后删除
    else
        return _Del_BSTree(&(*BST)->rchild, Key);
}
/**
 * @brief:        二叉排序树的结点删除操作
 * @param[in]:    二叉排序树
 * @return:       Status
 * @note:         从二叉排序树中删除结点，并重接左子树或右子树
 */
Status Delete(BSTree *BST)
{
    BSTree temp;
    BSTree s;
    if(!(*BST)->rchild)  //右子树为空
    {
        temp = *BST;
        *BST = (*BST)->lchild;
        free(temp);
    }
    else if(!(*BST)->lchild)  //左子树为空
    {
        temp = *BST;
        *BST = (*BST)->rchild;
        free(temp);
    }
    else    //左右子树都不为空
    {
        temp = *BST;
        s = (*BST)->lchild;
        while(s->rchild)    //转左向右走到尽头寻找删除结点的直接前驱(中序遍历)
        {
            temp = s;       //temp指向直接前驱的双亲结点
            s = s->rchild;
        }
        (*BST)->elem = s->elem; //用删除结点的直接前驱代替删除结点
        if(temp!=*BST)   //如果BST的直接前驱不是BST的左子树
            temp->rchild = s->lchild;   //重接右子树
        else
            temp->lchild = s->lchild;   //重接左子树
        free(s);
    }
    return TRUE;
}
/**
 * @brief   二叉排序树的输出操作 采用中序遍历
 * @param[in]   二叉排序树结构体指针
 * @retval  null
 **/
void _print_BSTree(BSTree BST)
{
    static int i = 0;
    if (BST)
    {
        _print_BSTree(BST->lchild);
        printf("%6d", BST->elem.Key);
        _print_BSTree(BST->rchild);
    }
}

