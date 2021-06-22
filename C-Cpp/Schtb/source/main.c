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
    printf("***************************** ���ҳ������ *****************************\n");
    printf("�������Χ    :[0,%d]\t������Ԫ������  :%d\t���ұ�����  :%d\n",Random_Range-1,Data_Random_Seed,Table_Random_Seed);
    double t_start, t_end;
    int num = 0;
    int i;
    int data_length = Data_Length > Random_Range ? Random_Range : Data_Length;
    //��������Ԫ��
    NodeType *k;
    k = random(Data_Random_Seed, Data_Length, );
    //�������ұ�
    SeaTable ST;
    Init_SeaTable(&ST,Table_Length);
    Creat_SeaTable(&ST, Random_Range);
    //������������
    BSTree BST,p;
    Init_BSTree(&BST);
    Creat_BSTree(&BST,Table_Length);
     //������ϣ����������͹�ϣ��
    HashTable HT;
    hashsize=prime(Table_Length);
    Init_HashTable(&HT, hashsize[0]);
    Creat_HashTable(&HT);
    //���ܲ���
    printf("���ұ�Ԫ�ظ���  :%d\t������Ԫ�ظ���  :%d\t�������Χ    :[0,%d]\n",  ST.count, k[0].Key, Random_Range-1);
    printf("������Ԫ�ظ���  :%d\t��ϣ��Ԫ�ظ���  :%d\t��ͻ��������  :%d\n", BST->nodeNumber, HT.count, Duplivate_Threshold);
    printTip("ɾ�����������ڵ�");
    Del_BSTree(&BST, BST->elem.Key); //ɾ�����ڵ�
    printf("���ұ�Ԫ�ظ���  :%d\t������Ԫ�ظ���  :%d\t�������Χ    :[0,%d]\n", ST.count,  k[0].Key, Random_Range-1);
    printf("������Ԫ�ظ���  :%d\t��ϣ��Ԫ�ظ���  :%d\t��ͻ��������  :%d\n", BST->nodeNumber, HT.count, Duplivate_Threshold);
    printTip("˳�����");
    getTime_SearchST(ST, k, SeqSearch_SeaTable);
    printTip("�۰����");
    getTime_SearchST(ST, k, BinSearch_SeaTable);
    printTip("��������������");
    t_start  = clock();
    for (i = 0; i < data_length; i++)
       if(Search_BST(BST, k[i].Key)!=NULL)
            num++;
    t_end = clock();
    printf("����������ʱ��\t��%dms\t�ɹ����ҵ�%d��Ԫ��\n",(int)(t_end - t_start),num);
    num = 0;
    printTip("��ϣ�����");
    t_start  = clock();
    for (i = 0; i < data_length; i++)
       if(Search_Hash(HT, k[i].Key)>=0)
           num++;
    t_end = clock();
    printf("��ϣ�����ʱ��\t��%dms\t�ɹ����ҵ�%d��Ԫ��\n",(int)(t_end - t_start),num);
    num = 0;
    printf("***************************** ������Խ��� *****************************\n");
    system("pause");
}
