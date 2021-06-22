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
    printf("****** 排序程序测试 ******\n");
    SeaList S;
    Init_SeaList(&S, SeaList_Length);
    Creat_SeaList(&S, Sort_Data_Length);

    printf("线性表元素个数：%d\n", S.rcd_num);
    printf("排序算法\t  时间\n");

    getSortTime(S, Insert_Sort, ascending);   //直接插入
    getSortTime(S, BInsert_Sort, ascending);  //折半插入
    getDlta(&S);                              //根据表长产生增量表
    getSortTime(S, Shell_Sort, ascending);    //希尔
    getSortTime(S, Select_Sort, ascending);   //简单选择
    getSortTime(S, Bubble_Sort, ascending);   //冒泡
    getSortTime(S, Quick_Sort, ascending);    //快速
    getSortTime(S, Heap_Sort, ascending);     //堆排序
    getSortTime(S, Merge_Sort, ascending);    //归并
    printf("--------------------------\n"); //分割线
    getSortTime(S, Insert_Sort, descending);  //直接插入
    getSortTime(S, BInsert_Sort, descending); //折半插入
    getDlta(&S);                              //根据表长产生增量表
    getSortTime(S, Shell_Sort, descending);   //希尔
    getSortTime(S, Select_Sort, descending);  //简单选择
    getSortTime(S, Bubble_Sort, descending);  //冒泡
    getSortTime(S, Quick_Sort, descending);   //快速
    getSortTime(S, Heap_Sort, descending);    //堆排序
    getSortTime(S, Merge_Sort, descending);   //归并

    printf("******* 程序测试结束 *******\n");
    system("pause");
    return 0;
}
