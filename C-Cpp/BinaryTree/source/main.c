/*
 * @Author: Ken Kaneki
 * @Date: 2019-10-20 09:19:39
 * @LastEditTime: 2020-04-07 16:51:57
 * @Description: README
 * @FilePath: \BinaryTree\source\main.c
 */
#include "binarytree.h"
//����������1.ABD##E##CF##G##   2.ABC###DE#F###
void main()
{
    BinaryTreePtr T;
    TraversalMethod creatOrder, printOrder;
    InitBinaryTree(&T); //��ʼ��������
    printTip("����������");
    printf("������ݹ鴴����ʽ(1->����,4->���):");
    scanf("%d", &creatOrder);
    getchar(); //������뻺��
    CreatBinaryTree(&T, creatOrder);

    printTip("��������ӡ");
    printTip("�ݹ������ӡ");
    PrintBinaryTree(T, PreOrder);
    PrintBinaryTree(T, InOrder);
    PrintBinaryTree(T, PostOrder);
    printTip("�ǵݹ������ӡ");
    PrintLoopBinaryTree(T);
    PrintBinaryTree(T, LevelOrder);
    printTip("�����������Ϣ");
    printBinaryTreeMes(T);
    printTip("���ٶ�����");
    DestroyTree(T);
    system("pause");
}
