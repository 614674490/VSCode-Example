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

#define Random_Range        50000       //������ķ�Χ 0-(Random_Range-1)33000
#define Table_Length        60000       //���ұ���ܳ���
#define Data_Length         100000       //���������ݳ���
#define Table_Random_Seed   629         //���ұ���������������� Ϊ����ʱ����Ϊ����
#define Data_Random_Seed    146         //�������������������������
typedef int KeyType;                    //����ؼ�����������
typedef struct node
{
    KeyType Key;      //���ҹؼ���
    //���⸽����Ϣ
    //InfoType otherInfo
} NodeType, *PtrNodeType;
typedef struct
{
    NodeType *elem;    //����Ԫ�ش洢�ռ��ַ
    int count;         //Ԫ�ظ���
    int length;       //���ұ���
} SeaTable,*PtrSeaTable;
//����������
typedef struct treenode
{
    NodeType elem;
    struct treenode *rchild, *lchild;
    int nodeNumber; //������
} BSTNode, *BSTree;

#define DEFARG(name,defval) ((#name[0])?(name+0):defval)  //������ֿո�
#define random(seed,num,range)   _random(seed,num,DEFARG(range, Random_Range))   //��ӳ�䴫Ĭ��ֵ ǰ������������Ҫ��ͬ
NodeType *_random(int seed, int num, int range);
Status Init_SeaTable(PtrSeaTable ST,int SeqTable_Length);
void Creat_SeaTable(SeaTable *ST, int data_max);
void Sort_SeaTable(SeaTable ST);
int SeqSearch_SeaTable(SeaTable ST, KeyType Key);
int BinSearch_SeaTable(SeaTable ST, KeyType Key);
void print_SeaTable(SeaTable ST);
int getTime_SearchST(SeaTable ST, NodeType *Key, int (*Search)(SeaTable, KeyType));
//������������ز���
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
