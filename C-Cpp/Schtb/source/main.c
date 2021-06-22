/*
 * @Author: liguiyin
 * @Date: 2019-11-22 10:01:27
 * @LastEditTime: 2019-12-02 15:50:37
 * @Description: README
 * @FilePath: \Schtb\source\main.c
 */
#include "time.h"
#include "stdlib.h"
#include "hash.h"
void main()
{
    printf("***************************** 查找程序测试 *****************************\n");
    printf("随机数范围    :[0,%d]\t待查找元素种子  :%d\t查找表种子  :%d\n",Random_Range-1,Data_Random_Seed,Table_Random_Seed);
    double t_start, t_end;
    int num = 0;
    int i;
    int data_length = Data_Length > Random_Range ? Random_Range : Data_Length;
    //创建查找元素
    NodeType *k;
    k = random(Data_Random_Seed, Data_Length, );
    //创建查找表
    SeaTable ST;
    Init_SeaTable(&ST,Table_Length);
    Creat_SeaTable(&ST, Random_Range);
    //创建二叉排序
    BSTree BST,p;
    Init_BSTree(&BST);
    Creat_BSTree(&BST,Table_Length);
     //创建哈希容量递增表和哈希表
    HashTable HT;
    hashsize=prime(Table_Length);
    Init_HashTable(&HT, hashsize[0]);
    Creat_HashTable(&HT);
    //功能测试
    printf("查找表元素个数  :%d\t待查找元素个数  :%d\t随机数范围    :[0,%d]\n",  ST.count, k[0].Key, Random_Range-1);
    printf("二叉树元素个数  :%d\t哈希表元素个数  :%d\t冲突次数上限  :%d\n", BST->nodeNumber, HT.count, Duplivate_Threshold);
    printTip("删除二叉树根节点");
    Del_BSTree(&BST, BST->elem.Key); //删除根节点
    printf("查找表元素个数  :%d\t待查找元素个数  :%d\t随机数范围    :[0,%d]\n", ST.count,  k[0].Key, Random_Range-1);
    printf("二叉树元素个数  :%d\t哈希表元素个数  :%d\t冲突次数上限  :%d\n", BST->nodeNumber, HT.count, Duplivate_Threshold);
    printTip("顺序查找");
    getTime_SearchST(ST, k, SeqSearch_SeaTable);
    printTip("折半查找");
    getTime_SearchST(ST, k, BinSearch_SeaTable);
    printTip("二叉排序树查找");
    t_start  = clock();
    for (i = 0; i < data_length; i++)
       if(Search_BST(BST, k[i].Key)!=NULL)
            num++;
    t_end = clock();
    printf("二叉树查找时间\t：%dms\t成功查找到%d个元素\n",(int)(t_end - t_start),num);
    num = 0;
    printTip("哈希表查找");
    t_start  = clock();
    for (i = 0; i < data_length; i++)
       if(Search_Hash(HT, k[i].Key)>=0)
           num++;
    t_end = clock();
    printf("哈希表查找时间\t：%dms\t成功查找到%d个元素\n",(int)(t_end - t_start),num);
    num = 0;
    printf("***************************** 程序测试结束 *****************************\n");
    system("pause");
}
