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

#define SeaList_Length 400000   //����������ܳ���
#define Sort_Data_Length 40000 //���������ĳ���

#define Random_Range SeaList_Length * 2
#define Sort_Data_Seed 123

typedef int KeyType; //����ؼ�������
typedef struct node
{
    KeyType Key; //�ȽϹؼ���
    //InfoType otherInfo;//���⸽����Ϣ
} RcdType, *PtrRcdType;
typedef struct
{
    RcdType *rcd; //��¼�洢�ռ��ַ 0��ַΪ������
    int rcd_num;  //��¼���� rcd_num<length-1
    int length;   //������ܳ���
    int *dlta;    //ϣ�������������
} SeaList, *PtrSeaList;
typedef enum
{
    descending = 0, //����
    ascending = 1   //����
} sortOrder;
RcdType *_random(int seed, int num, int range);
#define DEFARG(name, defval) ((#name[0]) ? (name + 0) : defval)                  //������ֿո�
#define random(seed, num, range) _random(seed, num, DEFARG(range, Random_Range)) //��ӳ�䴫Ĭ��ֵ ǰ������������Ҫ��ͬ
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
