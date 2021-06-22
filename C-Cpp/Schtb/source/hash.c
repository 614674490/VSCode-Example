/*
 * @Author: liguiyin
 * @Date: 2019-11-26 22:17:43
 * @LastEditTime: 2019-11-29 21:12:22
 * @Description: README
 * @FilePath: \Schtb\source\hash.c
 */
#include "hash.h"
#include "math.h"
//ȫ����������
int *hashsize;
/**
 * @brief:        �ж�ĳ�����Ƿ�Ϊ����
 * @param[in]:    Ҫ�жϵ�Ԫ��
 * @return:       Status
 * @note:         null
 */
Status isPrime(int key)
{
    int i;
    int k = sqrt(key);
    for (i = 2; i < k;i++)
    {
        if(!(key%i))
            return FALSE;
    }
    if(i>=k)
        return TRUE;
}
/**
 * @brief:        ����һ������
 * @param[in]:    a[]:������������� n=������Χ
 * @return:       ������ ��һ��Ԫ��Ϊ��������
 * @note:         ɸѡ������������
 */
int *prime(int n)
{
    int *a=(int *)malloc(sizeof(int)*n);
    int i,j,k,x,num,*b,*temp;
    n++;
    n/=2;
    b=(int *)malloc(sizeof(int)*(n+1)*2);  //���ù�ϣ���� �±�ֱ�Ӷ�Ӧ��ֵ
    a[1]=2;  //��һ������
    a[2]=3;  //�ڶ�������
    a[0] = 2;
    for (i=1;i<=2*n;i++)  //ż��λ���� ��2��������ż������������
        b[i]=0;           //����������Ϊfalse ����a[]����������
    for (i=3;i<=n;i+=3)
    {
        for (j=0;j<2;j++)
        {
            x=2*(i+j)-1;  // 5 7    11 13   17 19   23
            while (b[x]==0)
            {
                a[++a[0]]=x; //true���������
                for (k=x;k<=2*n;k+=x)  //��������Ӧ�ı�����false����Щ������������
                    b[k]=1;            //��ӵ�a[]�е�����λҲ��false����ֹ�ظ����
            }
        }
    }
    int *ans = (int *)malloc(sizeof(int)*(a[0]+1));
    ans[0] = a[0];
    for (i = 1; i <= a[0];i++)
        ans[i] = a[i];
    free(b);
    free(a) ;  //�ͷŶ�����ڴ�ռ�
    return ans;
}

/**
 * @brief:        ��ʼ����ϣ��
 * @param[in]:    ��ϣ��ṹ��ָ�� ��������������ֵ
 * @return:       Status
 * @note:         null
 */
Status Init_HashTable(HashTable *H,int sizeindex)
{
    int i;
    if(sizeindex>hashsize[hashsize[0]])  //����ֵ��Ӧ�����ݲ��ó������ֵ
        sizeindex = hashsize[0];
    if(H->elem = (NodeType *)malloc((hashsize[sizeindex]) * sizeof (NodeType)))
    {
        H->sizeindex = sizeindex;
        if(hashsize[sizeindex]>Random_Range)
        {
            printError("����ֵ���󣬹�ϣ�����ó����������Χ!");
            while(hashsize[--sizeindex]>Random_Range)
                ;
            H->sizeindex = sizeindex;
        }
        H->count = 0;
        H->length=hashsize[H->sizeindex];
        for (i = 0; i < H->length;i++)
        {
            H->elem[i].Key = NULLKEY;
        }
        H->mod = hashsize[sizeindex-1];
        return OK;
    }
    else
    {
        printError("�ڴ����");
        return ERROR;
    }
}
/**
 * @brief:        ��ϣ����
 * @param[in]:     �ؼ��� ģֵ(ӦΪ�����ڱ����������ǲ�����20���µ�������)
 * @return:       �±�ֵ
 * @note:         ����������
 */
int Hash(HashTable H,KeyType key)
{
    return key % H.mod;
}
/**
 * @brief:        ���ŵ�ַ��
 * @param[in]:    ��ϣ��  ��ͻԪ��  ��ͻ����
 * @return:       ̽���ַ
 * @note:         null
 */
int collision(HashTable H,KeyType Key,int dupcount)
{
    return (Hash(H,Key)+dupcount)%H.length;
}
/**
 * @brief:        ��ϣ����Ҳ���
 * @param[in]:    ��ϣ��ṹ�� �ؼ��� λ��ָ�� ��ͻ����
 * @return:       Status
 * @note:         ���ڴ�����ϣ��
 */
Status _Search_Hash(HashTable H,KeyType Key,int *pos,int *c)
{
    *pos = Hash(H,Key);    //��ȡ��ϣ��ַ
    while(H.elem[*pos].Key != NULLKEY&&Key != H.elem[*pos].Key)  //��ͻ
    {
        *pos=collision(H,Key, ++(*c));  //�����һ̽���ַ
        if(*c>Duplivate_Threshold)
            return UNSUCCESS;
    }
    if(Key==H.elem[*pos].Key)
        return SUCCESS;
    else
        return UNSUCCESS;
}
/**
 * @brief:        ��ϣ�����
 * @param[in]:    ��ϣ�� ����Ԫ��
 * @return:       Status
 * @note:         ���_Search_Hash���в���
 */
Status Insert_HashTable(HashTable *H,NodeType e)
{
    int c = 0;    //��¼��ͻ����
    int p = 0;    //��¼Ԫ��λ��
    if(_Search_Hash(*H,e.Key,&p,&c))
        return DUPLICATE;
    else if(c<=Duplivate_Threshold) //��ͻ����δ��ﵽ����
    {
        H->elem[p]=e;
        H->count++;
        return OK;
    }
    else
    {
        //printf("%d  ����ʧ��,��ͻ�����ﵽ���ޣ����ع���ϣ����\n", e.Key);
        return ERROR;
    }
}
/**
 * @brief:        ���ݹ�ϣ���� ���������ϣ��
 * @param[in]:    ��ϣ��ṹ��
 * @return:       Status
 * @note:         null
 */
Status Creat_HashTable(HashTable *H)
{
    int i = 0;
    NodeType *n = (random(Table_Random_Seed, (*H).length, )+1);
    while(i<(*H).length)
    {
        Insert_HashTable(H, n[i]);
        i++;
    }
    return OK;
}
/**
 * @brief:        ��ϣ�����
 * @param[in]:    ��ϣ�� ����Ԫ��
 * @return:       Ԫ��λ��
 * @note:         ���ڲ���Ԫ��
 */
int Search_Hash(HashTable H,KeyType Key)
{
    int pos = Hash(H, Key);
    int c = 0;
    while (H.elem[pos].Key != NULLKEY&&Key != H.elem[pos].Key) //��ͻ
    {
        pos=collision(H,Key, ++c);  //�����һ̽���ַ
        if(c>Duplivate_Threshold)   //��ͻ�����ﵽ���� ����ʧ��
            return -1;
    }
    if(Key==H.elem[pos].Key)
        return pos;
    else
        return -1;
}
/**
 * @brief:        �����ӡ��ϣ��
 * @param[in]:    ��ϣ��
 * @return:       null
 * @note:         null
 */
void print_HashTable(HashTable H)
{
    int i;
    int num = 0;
    for (i = 0; i < hashsize[H.sizeindex]; i++)
    {
        if(H.elem[i].Key!=NULLKEY)
        {
            printf("%6d", H.elem[i].Key);
            num++;
             if(!(num%20))
                printf("\n");
        }
    }
    printf("\n");
}
/**
 * @brief:        ��ϣ��ɾ������
 * @param[in]:    ��ϣ�� ɾ���ؼ���
 * @return:       Status
 * @note:         null
 */
Status Del_HashTable(HashTable H,KeyType Key)
{
    int pos;
    if((pos=Search_Hash(H,Key))>=0)
    {
        H.elem[pos].Key = NULLKEY;
        H.count--;
        return OK;
    }
    else
    {
        printError("�ؼ��ֲ�����!");
        return ERROR;
    }
}
