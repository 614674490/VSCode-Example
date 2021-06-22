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
 * @brief   ����һ��KeyType���͵Ĳ��ظ������
 * @param[in]   seed:��������� 0->time range : 0-range-1 key:������� num:Ԫ�ظ���
 * @retval  Status
 **/
NodeType *_random(int seed, int num, int range)
{
    int i;
    int rand_num;
    if(range<num)
    {
        printError("Ԫ�ظ������ó����������Χ");
        num = range;
    }
    NodeType *key = (NodeType *)malloc(sizeof(NodeType)*num);
    key[0].Key = 0;
    if(!key)
    {
        printError("�ڴ����!");
        return NULL;
    }
    int temp[range];
    for (i = 0; i < range;i++)
    {
        temp[i] = 0;
    }
    if(seed <= 0)
        srand( (unsigned)time( NULL ) );  //��ʱ����Ϊ����
    else
        srand(seed);
    if(num<=(RAND_MAX+1))
        for (i = 1; i <=num; i++)
        {
            key[i].Key =rand()%range; //0-range
            if(!temp[key[i].Key])  //���ݲ��ظ�
            {
                key[0].Key++;
                temp[key[i].Key] = 1;
            }
            else //�����ظ�
                i--;
        }
    else
    {
        if(!(num==range&&num>=33000))
        {
            for (i = 1; i <=num; i++)
            {
                key[i].Key = (rand() + (i / (RAND_MAX + 1)) * (RAND_MAX + 1)) % range;
                if(!temp[key[i].Key])  //���ݲ��ظ�
                {
                    key[0].Key++;
                    temp[key[i].Key] = 1;
                }
                else //�����ظ�
                    i--;
            }
        }
        else
        {
            for (i = 1; i <=num-1; i++)
            {
                key[i].Key = (rand() + (i / (RAND_MAX + 1)) * (RAND_MAX + 1)) % range;
                if(!temp[key[i].Key])  //���ݲ��ظ�
                {
                    key[0].Key++;
                    temp[key[i].Key] = 1;
                }
                else //�����ظ�
                    i--;
            }
            for (i = 0; i < range;i++)
            {
                if(!temp[i])  //�ֶ�Ѱ�����һ�������
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
 * @param[in]   SerTable Struct , SeqTable_Length(������0��ַ)
 * @retval  Status
 * @note    ���������,0��ַ��Ų��ҹؼ���
 **/
Status Init_SeaTable(PtrSeaTable ST,int SeqTable_Length)
{
    if(SeqTable_Length>Random_Range)
    {
        printError("��ѯ�����ó����������Χ!");
        SeqTable_Length = Random_Range;
    }
    if(ST->elem = (NodeType *)malloc((SeqTable_Length+1) * sizeof (NodeType)))
    {
        ST->length = SeqTable_Length+1;
        ST->elem[0].Key = 0;  //0��ַ����ֵ
        return OK;
    }
    else
    {
        printError("�ڴ����");
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
 * @brief       ������ұ�
 * @param[in]   SerTable Struct Key
 * @retval      NULL
 * @note        ѡ������
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
 * @brief       ˳����ұ�
 * @param[in]   SerTable Struct Key
 * @retval      Key Pos 0��ʾδ�ҵ�
 **/
int SeqSearch_SeaTable(SeaTable ST,KeyType Key)
{
    int i;
    ST.elem[0].Key = Key;
    for (i = ST.length-1; ST.elem[i].Key != Key;i--); //�Ӻ���ǰ��
    return  i;                      //һֱ�ҵ���ͷ��0��ַ���˳�����������޴˹ؼ���
}
/**
 * @brief       �۰���ұ�
 * @param[in]   SerTable Struct Key
 * @retval      Key Pos 0��ʾδ�ҵ�
 **/
int BinSearch_SeaTable(SeaTable ST,KeyType Key)
{
    int low = 1, high = ST.length, mid;
    while(low<=high)
    {
        mid = (low + high) / 2;
        if(ST.elem[mid].Key==Key)   //�ҵ�����Ԫ��
            return mid;
        else if(Key<ST.elem[mid].Key)   //������ǰ�������ڲ���
            high = mid - 1;
        else                            //�����ں�������ڲ���
            low = mid + 1;
    }
    return 0;                           //˳����в����ڴ�����Ԫ��
}
/**
 * @brief       ������ұ�����
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
 * @brief       ��ȡ��ѯ���ѯʱ��
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
        strcpy(str,(char *)"�۰�\0");
        t_start = clock();
        Sort_SeaTable(ST);
        t_end = clock();
        printf("ѡ������ʱ����%dms\n", t_end - t_start);
    }
    else if(Search == SeqSearch_SeaTable)
        strcpy(str,(char *)"˳��\0");
    t_start  = clock();
    for (i = 0; i < data_length; i++)
    {
       if(Search(ST, Key[i].Key))
            num++;
    }
    t_end = clock();
    printf("%s����ʱ��\t��%dms\t�ɹ����ҵ�%d��Ԫ��\n",str,(int)(t_end - t_start),num);
    return t_end - t_start;
}
/**
 * @brief   ����ն���������
 * @param[in]   �����������ṹ��ָ��
 * @retval  Status
 **/
Status Init_BSTree(BSTree *BST)
{
    *BST = (BSTree)malloc(sizeof(BSTNode)); //�����ڴ�
    if (!*BST)
    {
        printError("�ڴ����");
        return OVERFLOW;
    }
    else
    {
        (*BST)->nodeNumber = 0;
        (*BST)->lchild = NULL;
        (*BST)->rchild = NULL;
        return OK; //����ɹ�����OK
    }
}
/**
 * @brief       �����������Ĳ��Ҳ���
 * @param[in]   �����������ṹ��ָ�� ����Ԫ�صĹؼ���
 * @retval      BSTree�����ҳɹ��򷵻ؽ��ָ�� ���򷵻ؿ�ָ��
 * @note        �����ǲ���
 **/
BSTNode *Search_BST(BSTree BST,KeyType Key)
{
    if((!BST)||(BST->elem.Key == Key))
        return BST;
    else if(Key<BST->elem.Key)
        return Search_BST(BST->lchild, Key);  //Key�ȸ��ڵ�ֵС������������������
    else
        return Search_BST(BST->rchild, Key);  //����������������
}
/**
 * @brief       �����������Ĳ��Ҳ���
 * @param[in]   �����������ṹ��ָ�� ����Ԫ�صĹؼ��� ��ǰ�ڵ��˫�׽�� ����Ԫ�����ڽ��
 * @retval      Status ���ҳɹ�����TRUE ����ʧ�ܷ���FALSE
 * @note        �����ǲ���
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
 * @brief   �����������Ĳ������
 * @param[in]   �����������ṹ��ָ�� ����Ԫ��
 * @retval  Status
 **/
Status Insert_BST(BSTree *BST,NodeType elem)
{
    BSTNode *f, *p = *BST ;//fָ��Ҫ�����˫�׽�� pָ��ǰ�ڵ�
    if(!SearchBST(*BST,elem.Key,NULL,&p))   //�����Һ�����ͬԪ������pָ��Ľ��ĺ��ӽ��λ�ò���Ԫ��
    {
        BSTNode *s;
        Init_BSTree(&s);
        s->elem = elem;
        if(!p)  //��������Ԫ��
            *BST = s;
        else if(elem.Key<p->elem.Key)
             p->lchild = s;     //s��Ϊ����
        else
             p->rchild = s;     //s��Ϊ�Һ���
        (*BST)->nodeNumber++;
        return TRUE;
    }
    else  //����������ͬԪ�� ���ٲ���
        return FALSE;
}
/**
 * @brief   �����������Ĵ�������
 * @param[in]   �����������ṹ��ָ�� ������
 * @retval  Status
 **/
Status Creat_BSTree(BSTree *BST,int nodeNumber)
{
    int i;
    *BST = NULL;
    if(nodeNumber>Random_Range)
    {
        printError("���������������ó����������Χ!");
        nodeNumber = Random_Range;
    }
    NodeType *elem = random(Table_Random_Seed, nodeNumber, );
    for (i = 1; i <= nodeNumber;i++)
        Insert_BST(BST, *(elem+i));
    return OK;
}
/**
 * @brief:        ������������ɾ������
 * @param[in]:    ���������� ɾ���ؼ���
 * @return:       Status
 * @note:         null
 */
Status _Del_BSTree(BSTree *BST,KeyType Key)
{
    if(!*BST)
        return FALSE;
    else if(Key==(*BST)->elem.Key)
        return Delete(BST);     //�ҵ��ؼ�������λ����ɾ��
    else if(Key<(*BST)->elem.Key)
        return _Del_BSTree(&(*BST)->lchild, Key);    //������еݹ���� �ҵ���ɾ��
    else
        return _Del_BSTree(&(*BST)->rchild, Key);
}
/**
 * @brief:        �����������Ľ��ɾ������
 * @param[in]:    ����������
 * @return:       Status
 * @note:         �Ӷ�����������ɾ����㣬���ؽ���������������
 */
Status Delete(BSTree *BST)
{
    BSTree temp;
    BSTree s;
    if(!(*BST)->rchild)  //������Ϊ��
    {
        temp = *BST;
        *BST = (*BST)->lchild;
        free(temp);
    }
    else if(!(*BST)->lchild)  //������Ϊ��
    {
        temp = *BST;
        *BST = (*BST)->rchild;
        free(temp);
    }
    else    //������������Ϊ��
    {
        temp = *BST;
        s = (*BST)->lchild;
        while(s->rchild)    //ת�������ߵ���ͷѰ��ɾ������ֱ��ǰ��(�������)
        {
            temp = s;       //tempָ��ֱ��ǰ����˫�׽��
            s = s->rchild;
        }
        (*BST)->elem = s->elem; //��ɾ������ֱ��ǰ������ɾ�����
        if(temp!=*BST)   //���BST��ֱ��ǰ������BST��������
            temp->rchild = s->lchild;   //�ؽ�������
        else
            temp->lchild = s->lchild;   //�ؽ�������
        free(s);
    }
    return TRUE;
}
/**
 * @brief   ������������������� �����������
 * @param[in]   �����������ṹ��ָ��
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

