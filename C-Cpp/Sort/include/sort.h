/*
 * @Author: liguiyin
 * @Date: 2019-12-03 15:10:01
 * @LastEditTime: 2019-12-06 16:27:04
 * @Description: README
 * @FilePath: \Sort\include\sort.h
 */
#ifndef _sort_h
#define _sort_h
#include "config.h"

#define SeaList_Length 400000   //线性排序表总长度
#define Sort_Data_Length 40000 //定义待排序的长度

#define Random_Range SeaList_Length * 2
#define Sort_Data_Seed 123

typedef int KeyType; //定义关键字类型
typedef struct node
{
    KeyType Key; //比较关键字
    //InfoType otherInfo;//额外附加信息
} RcdType, *PtrRcdType;
typedef struct
{
    RcdType *rcd; //记录存储空间地址 0地址为监视哨
    int rcd_num;  //记录个数 rcd_num<length-1
    int length;   //排序表总长度
    int *dlta;    //希尔排序的增量表
} SeaList, *PtrSeaList;
typedef enum
{
    descending = 0, //降序
    ascending = 1   //升序
} sortOrder;
RcdType *_random(int seed, int num, int range);
#define DEFARG(name, defval) ((#name[0]) ? (name + 0) : defval)                  //切勿出现空格
#define random(seed, num, range) _random(seed, num, DEFARG(range, Random_Range)) //宏映射传默认值 前后两个参数名要相同
Status Init_SeaList(PtrSeaList S, int Length);
Status Creat_SeaList(SeaList *S, int Rcd_Num);
Status getDlta(SeaList *S);
void printSort(SeaList S);
void Swap_Rcd(PtrRcdType ra, PtrRcdType rb);
int getSortTime(SeaList S, void (*Sort)(SeaList, sortOrder), sortOrder sortorder);
void Insert_Sort(SeaList S, sortOrder sortorder);
void BInsert_Sort(SeaList S, sortOrder sortorder);
void ShellInsert(SeaList S, int dk, sortOrder sortorder);
void _Shell_Sort(SeaList S, int dlta[], int t, sortOrder sortorder);
void Shell_Sort(SeaList S, sortOrder sortorder);
void Select_Sort(SeaList S, sortOrder sortorder);
void Bubble_Sort(SeaList S, sortOrder sortorder);
int Partition(SeaList S, int low, int high, sortOrder sortorder);
void QSort(SeaList S, int low, int high, sortOrder sortorder);
void Quick_Sort(SeaList S, sortOrder sortorder);
void Heap_Adjust(SeaList S, int s, int m, sortOrder sortorder);
void Heap_Sort(SeaList S, sortOrder sortorder);
void Merge(SeaList S, int low, int m, int high, sortOrder sortorder);
void MergeSortRecursion(SeaList S, int low, int high, sortOrder sortorder);
void Merge_Sort(SeaList S, sortOrder sortorder);
#endif
