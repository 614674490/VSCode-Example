/*
 * @Author: Ken Kaneki
 * @Date: 2019-10-20 09:19:39
 * @LastEditTime: 2020-04-07 16:51:57
 * @Description: README
 * @FilePath: \BinaryTree\source\main.c
 */
#include "binarytree.h"
//测试样例：1.ABD##E##CF##G##   2.ABC###DE#F###
void main()
{
    BinaryTreePtr T;
    TraversalMethod creatOrder, printOrder;
    InitBinaryTree(&T); //初始化二叉树
    printTip("二叉树创建");
    printf("请输入递归创建方式(1->先序,4->层次):");
    scanf("%d", &creatOrder);
    getchar(); //清除输入缓存
    CreatBinaryTree(&T, creatOrder);

    printTip("二叉树打印");
    printTip("递归遍历打印");
    PrintBinaryTree(T, PreOrder);
    PrintBinaryTree(T, InOrder);
    PrintBinaryTree(T, PostOrder);
    printTip("非递归遍历打印");
    PrintLoopBinaryTree(T);
    PrintBinaryTree(T, LevelOrder);
    printTip("二叉树相关信息");
    printBinaryTreeMes(T);
    printTip("销毁二叉树");
    DestroyTree(T);
    system("pause");
}
