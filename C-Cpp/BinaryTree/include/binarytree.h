#ifndef _binarytree_h
#define _binarytree_h
#include "config.h"
#include "math.h"
#define END '#'
typedef char DataType; //定义数据类型
typedef struct treenode
{
    DataType data;                    //数据域
    struct treenode *lchild, *rchild; //指针域 左孩子 右孩子
} BinaryTreeTp, *BinaryTreePtr;
typedef enum
{
    PreOrder = 1,
    InOrder = 2,
    PostOrder = 3,
    LevelOrder = 4
} TraversalMethod;


Status funPrint(BinaryTreePtr *T);

Status InitBinaryTree(BinaryTreePtr *T);
Status CreatBinaryTree(BinaryTreePtr *T, TraversalMethod Order);

Status DestroyTree(BinaryTreePtr T);
Status ClearTree(BinaryTreePtr T);

Status PreOrderCreat(BinaryTreePtr *T);
Status LevelOrderCreat(BinaryTreePtr *T);
Status PostOrderCreat(BinaryTreePtr *T);

Status PreOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));
Status InOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));
Status PostOrderTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));
Status LevelOrderTraverse_Queue(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));

Status PreOrderLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));
Status InOrederLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));
Status PostOrderLoopTraverse(BinaryTreePtr T, Status (*Visit)(BinaryTreePtr *));

Status PrintBinaryTree(BinaryTreePtr T, TraversalMethod Order);
Status PrintLoopBinaryTree(BinaryTreePtr T);

int getBinaryTreeLeafNum(BinaryTreePtr T);
int getBinaryTreeNodeNum(BinaryTreePtr T);
int getBinaryTreeDepth(BinaryTreePtr T);
void printBinaryTreeMes(BinaryTreePtr T);
#endif
