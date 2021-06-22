/*
 * @Author: liguiyin
 * @Date: 2019-11-26 22:17:43
 * @LastEditTime: 2019-11-29 21:12:22
 * @Description: README
 * @FilePath: \Schtb\source\hash.c
 */
#include "hash.h"
#include "math.h"
//全局数容量表
int *hashsize;
/**
 * @brief:        判断某个数是否为素数
 * @param[in]:    要判断的元素
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
 * @brief:        产生一组素数
 * @param[in]:    a[]:存放素数的数组 n=素数范围
 * @return:       素数组 第一个元素为素数个数
 * @note:         筛选法快速求素数
 */
int *prime(int n)
{
    int *a=(int *)malloc(sizeof(int)*n);
    int i,j,k,x,num,*b,*temp;
    n++;
    n/=2;
    b=(int *)malloc(sizeof(int)*(n+1)*2);  //采用哈希表存放 下标直接对应数值
    a[1]=2;  //第一个素数
    a[2]=3;  //第二个素数
    a[0] = 2;
    for (i=1;i<=2*n;i++)  //偶数位置零 除2以外所有偶数均不是素数
        b[i]=0;           //不是素数设为false 方便a[]遍历求素数
    for (i=3;i<=n;i+=3)
    {
        for (j=0;j<2;j++)
        {
            x=2*(i+j)-1;  // 5 7    11 13   17 19   23
            while (b[x]==0)
            {
                a[++a[0]]=x; //true则添加素数
                for (k=x;k<=2*n;k+=x)  //把素数对应的倍数置false，这些不可能是素数
                    b[k]=1;            //添加到a[]中的素数位也置false，防止重复添加
            }
        }
    }
    int *ans = (int *)malloc(sizeof(int)*(a[0]+1));
    ans[0] = a[0];
    for (i = 1; i <= a[0];i++)
        ans[i] = a[i];
    free(b);
    free(a) ;  //释放多余的内存空间
    return ans;
}

/**
 * @brief:        初始化哈希表
 * @param[in]:    哈希表结构体指针 素数容量表索引值
 * @return:       Status
 * @note:         null
 */
Status Init_HashTable(HashTable *H,int sizeindex)
{
    int i;
    if(sizeindex>hashsize[hashsize[0]])  //索引值对应的内容不得超过最大值
        sizeindex = hashsize[0];
    if(H->elem = (NodeType *)malloc((hashsize[sizeindex]) * sizeof (NodeType)))
    {
        H->sizeindex = sizeindex;
        if(hashsize[sizeindex]>Random_Range)
        {
            printError("索引值错误，哈希表长不得超过随机数范围!");
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
        printError("内存溢出");
        return ERROR;
    }
}
/**
 * @brief:        哈希函数
 * @param[in]:     关键字 模值(应为不大于表长的素数或是不包含20以下的质因子)
 * @return:       下标值
 * @note:         除留余数法
 */
int Hash(HashTable H,KeyType key)
{
    return key % H.mod;
}
/**
 * @brief:        开放地址法
 * @param[in]:    哈希表  冲突元素  冲突计数
 * @return:       探测地址
 * @note:         null
 */
int collision(HashTable H,KeyType Key,int dupcount)
{
    return (Hash(H,Key)+dupcount)%H.length;
}
/**
 * @brief:        哈希表查找操作
 * @param[in]:    哈希表结构体 关键字 位置指针 冲突次数
 * @return:       Status
 * @note:         用于创建哈希表
 */
Status _Search_Hash(HashTable H,KeyType Key,int *pos,int *c)
{
    *pos = Hash(H,Key);    //获取哈希地址
    while(H.elem[*pos].Key != NULLKEY&&Key != H.elem[*pos].Key)  //冲突
    {
        *pos=collision(H,Key, ++(*c));  //求得下一探测地址
        if(*c>Duplivate_Threshold)
            return UNSUCCESS;
    }
    if(Key==H.elem[*pos].Key)
        return SUCCESS;
    else
        return UNSUCCESS;
}
/**
 * @brief:        哈希表插入
 * @param[in]:    哈希表 插入元素
 * @return:       Status
 * @note:         结合_Search_Hash进行插入
 */
Status Insert_HashTable(HashTable *H,NodeType e)
{
    int c = 0;    //记录冲突次数
    int p = 0;    //记录元素位置
    if(_Search_Hash(*H,e.Key,&p,&c))
        return DUPLICATE;
    else if(c<=Duplivate_Threshold) //冲突次数未达达到上限
    {
        H->elem[p]=e;
        H->count++;
        return OK;
    }
    else
    {
        //printf("%d  插入失败,冲突次数达到上限，请重构哈希函数\n", e.Key);
        return ERROR;
    }
}
/**
 * @brief:        根据哈希函数 随机创建哈希表
 * @param[in]:    哈希表结构体
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
 * @brief:        哈希表查找
 * @param[in]:    哈希表 查找元素
 * @return:       元素位置
 * @note:         用于查找元素
 */
int Search_Hash(HashTable H,KeyType Key)
{
    int pos = Hash(H, Key);
    int c = 0;
    while (H.elem[pos].Key != NULLKEY&&Key != H.elem[pos].Key) //冲突
    {
        pos=collision(H,Key, ++c);  //求得下一探测地址
        if(c>Duplivate_Threshold)   //冲突次数达到上限 查找失败
            return -1;
    }
    if(Key==H.elem[pos].Key)
        return pos;
    else
        return -1;
}
/**
 * @brief:        输出打印哈希表
 * @param[in]:    哈希表
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
 * @brief:        哈希表删除操作
 * @param[in]:    哈希表 删除关键字
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
        printError("关键字不存在!");
        return ERROR;
    }
}
