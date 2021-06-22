/*
 * @Author: liguiyin
 * @Date: 2019-12-03 15:10:01
 * @LastEditTime: 2019-12-06 20:15:42
 * @Description: README
 * @FilePath: \Sort\source\main.c
 */
#include "sort.h"
int main()
{
    printf("****** ���������� ******\n");
    SeaList S;
    Init_SeaList(&S, SeaList_Length);
    Creat_SeaList(&S, Sort_Data_Length);

    printf("���Ա�Ԫ�ظ�����%d\n", S.rcd_num);
    printf("�����㷨\t  ʱ��\n");

    getSortTime(S, Insert_Sort, ascending);   //ֱ�Ӳ���
    getSortTime(S, BInsert_Sort, ascending);  //�۰����
    getDlta(&S);                              //���ݱ�����������
    getSortTime(S, Shell_Sort, ascending);    //ϣ��
    getSortTime(S, Select_Sort, ascending);   //��ѡ��
    getSortTime(S, Bubble_Sort, ascending);   //ð��
    getSortTime(S, Quick_Sort, ascending);    //����
    getSortTime(S, Heap_Sort, ascending);     //������
    getSortTime(S, Merge_Sort, ascending);    //�鲢
    printf("--------------------------\n"); //�ָ���
    getSortTime(S, Insert_Sort, descending);  //ֱ�Ӳ���
    getSortTime(S, BInsert_Sort, descending); //�۰����
    getDlta(&S);                              //���ݱ�����������
    getSortTime(S, Shell_Sort, descending);   //ϣ��
    getSortTime(S, Select_Sort, descending);  //��ѡ��
    getSortTime(S, Bubble_Sort, descending);  //ð��
    getSortTime(S, Quick_Sort, descending);   //����
    getSortTime(S, Heap_Sort, descending);    //������
    getSortTime(S, Merge_Sort, descending);   //�鲢

    printf("******* ������Խ��� *******\n");
    system("pause");
    return 0;
}
