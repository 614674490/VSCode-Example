/*
 * @Author: liguiyin
 * @Date: 2019-11-22 11:17:37
 * @LastEditTime: 2019-12-03 19:47:11
 * @Description: README
 * @FilePath: \Schtb\include\schtb.h
 */
#ifndef _schtb_h
#define _schtb_h
#include "config.h"

#define Random_Range        50000       //随机数的范围 0-(Random_Range-1)33000
#define Table_Length        60000       //查找表的总长度
#define Data_Length         100000       //待查找数据长度
#define Table_Random_Seed   629         //查找表随机数发生器种子 为零则将时间作为种子
#define Data_Random_Seed    146         //待查找数据随机数发生器种子
typedef int KeyType;                    //定义关键字数据类型
typedef struct node
{
    KeyType Key;      //查找关键字
    //额外附加信息
    //InfoType otherInfo
} NodeType, *PtrNodeType;
typedef struct
{
    NodeType *elem;    //数据元素存储空间地址
    int count;         //元素个数
    int length;       //查找表长度
} SeaTable,*PtrSeaTable;
//二叉排序树
typedef struct treenode
{
    NodeType elem;
    struct treenode *rchild, *lchild;
    int nodeNumber; //结点个数
} BSTNode, *BSTree;

#define DEFARG(name,defval) ((#name[0])?(name+0):defval)  //切勿出现空格
#define random(seed,num,range)   _random(seed,num,DEFARG(range, Random_Range))   //宏映射传默认值 前后两个参数名要相同
NodeType *_random(int seed, int num, int range);
Status Init_SeaTable(PtrSeaTable ST,int SeqTable_Length);
void Creat_SeaTable(SeaTable *ST, int data_max);
void Sort_SeaTable(SeaTable ST);
int SeqSearch_SeaTable(SeaTable ST, KeyType Key);
int BinSearch_SeaTable(SeaTable ST, KeyType Key);
void print_SeaTable(SeaTable ST);
int getTime_SearchST(SeaTable ST, NodeType *Key, int (*Search)(SeaTable, KeyType));
//二叉排序树相关操作
Status Init_BSTree(BSTree *BST);
BSTNode *Search_BST(BSTree BST, KeyType Key);
Status SearchBST(BSTree BST, KeyType Key, BSTree Parent, BSTree *Keypos);
Status Insert_BST(BSTree *BST, NodeType elem);
Status Creat_BSTree(BSTree *BST, int nodeNumber);
Status _Del_BSTree(BSTree *BST, KeyType Key);
Status Delete(BSTree *BST);
void _print_BSTree(BSTree BST);
#define Del_BSTree(BST, Key) {\
        _Del_BSTree(BST, Key);\
        (*BST)->nodeNumber--;\
    }
#define print_BSTree(BST) {\
        _print_BSTree(BST);\
        putchar('\n');\
    }
#endif
