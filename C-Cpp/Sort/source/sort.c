/*
 * @Author: liguiyin
 * @Date: 2019-12-03 15:10:01
 * @LaSEditTime: 2019-12-04 13:20:27
 * @Description: README
 * @FilePath: \Sort\source\sort.c
 */
#include "sort.h"
#include "time.h"
/**
 * @brief   产生一组KeyType类型的随机数
 * @param[in]   seed:随机数种子 0->time range : 0-range-1 rcd:存放数组 num:元素个数
 * @retval  Satus
 **/
RcdType *_random(int seed, int num, int range)
{
    int i;
    if (range < num)
    {
        printError("元素个数不得超过随机数范围"); //防止出现大量重复数据
        num = range;
    }
    RcdType *rcd = (RcdType *)malloc(sizeof(RcdType) * num);
    if (!rcd)
    {
        printError("内存溢出!");
        return NULL;
    }
    rcd[0].Key = 0;
    if (seed <= 0)
        srand((unsigned)time(NULL)); //将时间作为种子
    else
        srand(seed);
        for (i = 1; i <= num; i++)
        {
            rcd[i].Key = ((double)rand() / RAND_MAX) * range;
            rcd[0].Key++;
        }
    return rcd;
}
/**
 * @brief   Init SeaList
 * @param[in]   SeaList Sruct , SeaList_Length(包括0地址)
 * @retval  Satus
 * @note    加入监视哨,0地址存放查找关键字
 **/
Status Init_SeaList(PtrSeaList S, int Length)
{
    if (SeaList_Length > Random_Range)
    {
        printError("记录表长不得超过随机数范围!");
        Length = Random_Range;
    }
    if (S->rcd = (RcdType *)malloc(Length * sizeof(RcdType)))
    {
        S->length = Length;
        S->rcd_num = 0;
        S->rcd[0].Key = 0; //0地址赋初值
        return OK;
    }
    else
    {
        printError("内存溢出");
        return ERROR;
    }
}
/**
 * @brief:        创建排序表
 * @param[in]:    排序表结构体指针  记录数量(不包括0地址)
 * @return:       Satus
 * @note:         rcd[0].Key存储元素个数
 */
Status Creat_SeaList(SeaList *S, int Rcd_Num)
{
    if (Rcd_Num > S->length - 1)
    {
        printError("记录数量不可超过表长!"); //总表长包括0地址和记录 Rcd_Num仅包括记录数目
        Rcd_Num = S->length - 1;             //因此 S.rcd_num<S.length-1
    }
    S->rcd = random(Sort_Data_Seed, Rcd_Num, );
    if (!S->rcd)
    {
        printError("线性表创建失败!");
        return ERROR;
    }
    else
    {
        S->rcd_num = S->rcd[0].Key;
        return OK;
    }
}
/**
 * @brief:        输出排序表
 * @param[in]:    线性表结构体
 * @return:       null
 * @note:         只打印记录 0地址数据不打印
 */
void printSort(SeaList S)
{
    int i;
    for (i = 1; i <= S.rcd_num; i++)
    {
        printf("%-8d", S.rcd[i].Key);
        if (!(i % 15))
            printf("\n");
    }
    printf("\n\n");
}
/**
 * @brief:        交换两个记录
 * @param[in]:    记录A 记录B
 * @return:       null
 * @note:         null
 */
void Swap_Rcd(PtrRcdType ra, PtrRcdType rb)
{
    RcdType rt;
    rt = *ra;
    *ra = *rb;
    *rb = rt;
}
/**
 * @brief:        排序测试
 * @param[in]:    排序表 排序算法
 * @return:       排序时长
 * @note:         null
 */
int getSortTime(SeaList S, void (*Sort)(SeaList, sortOrder), sortOrder sortorder)
{
    int t_start, t_end;
    Creat_SeaList(&S, Sort_Data_Length);
    char order[4] = "↑\0";  //↑为升序
    if (sortorder == descending)
        strcpy(order, "↓\0");   //↓为降序
    if (Sort == Insert_Sort)
        printf("直接插入排序%s\t：", order);
    else if (Sort == BInsert_Sort)
        printf("折半插入排序%s\t：", order);
    else if (Sort == Shell_Sort)
        printf("希尔排序%s\t：", order);
    else if (Sort == Select_Sort)
        printf("选择排序%s\t：", order);
    else if (Sort == Bubble_Sort)
        printf("冒泡排序%s\t：", order);
    else if (Sort == Quick_Sort)
        printf("快速排序%s\t：", order);
    else if (Sort == Heap_Sort)
        printf("堆排序%s\t：", order);
    else if (Sort == Merge_Sort)
        printf("归并排序%s\t：", order);
    t_start = clock();
    Sort(S, sortorder);
    t_end = clock();
    printf("%dms\n", t_end - t_start);
    //printSort(S);
    return t_end - t_start;
}
/**
 * @brief:        简单排序->直接插入排序(默认升序)
 * @param[in]:    排序表结构体 排序方式
 * @return:       void
 * @note:         时间性能：O(n^2)  空间性能：O(1)
 *                稳定性能：稳定
 */
void Insert_Sort(SeaList S, sortOrder sortorder)
{
    int i, j;
    for (i = 2; i <= S.rcd_num; i++)
    {
        S.rcd[0] = S.rcd[i];                                                                                     //复制到监视哨
        for (j = i - 1; sortorder == ascending ? S.rcd[0].Key < S.rcd[j].Key : S.rcd[0].Key > S.rcd[j].Key; j--) //和前i-1个数据倒序比较
            S.rcd[j + 1] = S.rcd[j]; //第j个数据大于于插入数据 则将R[j]的数据向后移1位
        S.rcd[j + 1] = S.rcd[0]; //第j个数据小于等于插入数据，则将插入数据插入到j+1的位置，即R[j]的后面
    }
}
/**
 * @brief:        折半插入排序(默认升序)
 * @param[in]:    排序表
 * @return:       null
 * @note:         减少了直接插入的比较次数，但是移动次数未减少
 */
void BInsert_Sort(SeaList S, sortOrder sortorder)
{
    int i, j;
    int low, high, mid;
    for (i = 2; i <= S.rcd_num; i++)
    {
        S.rcd[0] = S.rcd[i]; //复制到监视哨
        low = 1, high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (sortorder == ascending ? S.rcd[0].Key < S.rcd[mid].Key : S.rcd[0].Key > S.rcd[mid].Key)
                high = mid - 1; //插入点在低半区
            else
                low = mid + 1; //插入点在高半区
        }
        for (j = i - 1; j >= high + 1; j--) //记录后移
            S.rcd[j + 1] = S.rcd[j];
        S.rcd[high + 1] = S.rcd[0]; //插入
    }
}
/**
 * @brief:        希尔排序子算法(一趟希尔排序)
 * @param[in]:    排序表 增量dk
 * @return:       null
 * @note:         改自直接插入排序算法
 */
void ShellInsert(SeaList S, int dk, sortOrder sortorder)
{
    int i, j;
    for (i = dk + 1; i <= S.rcd_num; i++)
    {
        if (sortorder == ascending ? S.rcd[i].Key < S.rcd[i - dk].Key : S.rcd[i].Key > S.rcd[i - dk].Key)
        {
            S.rcd[0] = S.rcd[i];
            for (j = i - dk; j > 0 && sortorder == ascending ? S.rcd[0].Key < S.rcd[j].Key : S.rcd[0].Key > S.rcd[j].Key; j -= dk)
                S.rcd[j + dk] = S.rcd[j]; //记录后移
            S.rcd[j + dk] = S.rcd[0];     //插入
        }
    }
}
/**
 * @brief:        生成增量表
 * @param[in]:    排序表
 * @return:       增量表
 * @note:         增量表0地址存储增量序列数量
 */
Status getDlta(SeaList *S)
{
    int dlta_length = 0; //生成增量序列
    dlta_length = ((S->rcd_num / 2 - 1) / 2) + 1;
    S->dlta = (int *)malloc(sizeof(int) * (dlta_length + 1));
    if (!S->dlta)
    {
        printError("内存溢出");
        return ERROR;
    }
    S->dlta[0] = 0;
    int i;
    for (i = 1; i <= dlta_length; i++)
    {
        S->dlta[i] = 1 + 2 * (i - 1);
        S->dlta[0]++;
    }
}
/**
 * @brief:        希尔排序(默认升序)
 * @param[in]:    排序表 递增表 递增表长
 * @return:       null
 * @note:         dlta[k]=2^(t-k+1)-1 --> O(n^(3/2)) t为排序趟数
 *                当n在某个特定范围内,比较和移动次数约为n^1.3
 *                当n->∞时，可减少到n(log2n)^2
 *                增量序列dlta[]中的值没有除1之外的公因子,并且最后一个增量值必须等于1
 */
void _Shell_Sort(SeaList S, int dlta[], int t, sortOrder sortorder)
{
    //按增量序列对顺序表S做希尔排序
    int i;
    for (i = 0; i < t; i++)
        ShellInsert(S, dlta[i], sortorder);
}
void Shell_Sort(SeaList S, sortOrder sortorder)
{
    _Shell_Sort(S, S.dlta + 1, S.dlta[0], sortorder);
}
/**
 * @brief:        简单排序->简单选择排序(默认升序)
 * @param[in]:    排序表结构体
 * @return:       void
 * @note:         时间性能：O(n^2)  空间性能：O(1)
 *                稳定性能：稳定
 */
void Select_Sort(SeaList S, sortOrder sortorder)
{
    int i, j, k;
    for (i = 1; i <= S.rcd_num; i++)
    {
        k = i;
        for (j = i; j <= S.rcd_num; j++) //寻找最小值所在位置
        {
            if (sortorder == ascending ? S.rcd[j].Key < S.rcd[k].Key : S.rcd[j].Key > S.rcd[k].Key)
                k = j;
        }
        if (k != i)
            Swap_Rcd(&S.rcd[i], &S.rcd[k]);
    }
}
/**
 * @brief:        简单排序->冒泡排序(默认升序)
 * @param[in]:    排序表结构体
 * @return:       void
 * @note:         时间性能：O(n^2)  空间性能：O(1)
 *                稳定性能：稳定
 */
void Bubble_Sort(SeaList S, sortOrder sortorder)
{
    int i, j;
    for (i = 1; i <= S.rcd_num; i++)
    {
        for (j = 1; j <= S.rcd_num - i; j++)
        {
            if (sortorder == ascending ? S.rcd[j + 1].Key < S.rcd[j].Key : S.rcd[j + 1].Key > S.rcd[j].Key)
                Swap_Rcd(&S.rcd[j + 1], &S.rcd[j]);
        }
    }
}
/**
 * @brief:        快速排序子算法1
 * @param[in]:    排序表 low high
 * @return:       枢轴所在位置
 * @note:         一趟快速排序
 */
int Partition(SeaList S, int low, int high, sortOrder sortorder)
{
    KeyType pivotkey = S.rcd[low].Key;
    S.rcd[0] = S.rcd[low]; //暂存枢轴记录
    while (low < high)     //从表的两端交替向中间扫描
    {
        while (low < high && (sortorder == ascending ? S.rcd[high].Key >= pivotkey : S.rcd[high].Key <= pivotkey))
            high--;
        S.rcd[low] = S.rcd[high]; //将比枢轴记录小的记录移到低端
        while (low < high && (sortorder == ascending ? S.rcd[low].Key <= pivotkey : S.rcd[low].Key >= pivotkey))
            low++;
        S.rcd[high] = S.rcd[low]; //将比枢轴记录大的记录移到高端
    }
    S.rcd[low] = S.rcd[0];
    return low;
}
/**
 * @brief:        快速排序子算法2
 * @param[in]:    排序表
 * @return:       null
 * @note:         时间性能：最好:O(nlogn) 最坏:O(n^2)  空间性能：O(logn)
 *                稳定性能：不稳定
 */
void QSort(SeaList S, int low, int high, sortOrder sortorder)
{
    int pivotc;
    if (low < high)
    {
        pivotc = Partition(S, low, high, sortorder); //将递归子表分成两部分
        QSort(S, low, pivotc - 1, sortorder);        //先左
        QSort(S, pivotc + 1, high, sortorder);       //后右
    }
}
/**
 * @brief:        快速排序算法(默认升序)
 * @param[in]:    排序表
 * @return:       null
 * @note:         时间性能：最好:O(nlogn) 最坏:O(n^2)  空间性能：O(logn)
 *                稳定性能：不稳定
 */
void Quick_Sort(SeaList S, sortOrder sortorder)
{
    QSort(S, 1, S.rcd_num, sortorder);
}
/**
 * @brief:        筛选算法  -->  建成大顶堆
 * @param[in]:    排序表子表 s(起始地址) m(结束地址)
 * @return:       null
 * @note:         已知S.rcd[s..m]中的关键字除H.r[s]外均满足堆的定义,调整S.rcd[s]
 * 的关键字,使之成为一个大顶堆
 */
void Heap_Adjust(SeaList S, int s, int m, sortOrder sortorder)
{
    int j;
    S.rcd[0] = S.rcd[s];            //暂存调整记录
    for (j = 2 * s; j <= m; j *= 2) //沿着关键字Key较大的孩子结点向下筛选
    {
        if (j < m && (sortorder == ascending ? S.rcd[j].Key < S.rcd[j + 1].Key : S.rcd[j].Key > S.rcd[j + 1].Key)) //j为Key较大的记录下标
            j++;                                                                                                   //当前层的的左右孩子或兄弟
        if (sortorder == ascending ? S.rcd[0].Key >= S.rcd[j].Key : S.rcd[0].Key <= S.rcd[j].Key)                  //若堆顶大于当前结点的关键字则不调整
            break;
        S.rcd[s] = S.rcd[j]; //否则将s和j位置的记录进行替换
        s = j;
    }
    S.rcd[s] = S.rcd[0];
}
/**
 * @brief:        堆排序(默认升序)
 * @param[in]:    排序表
 * @return:       null
 * @note:         时间性能：最好:O(nlogn) 最坏:O(nlogn)  空间性能：O(1)
 *                稳定性能：不稳定
 */
void Heap_Sort(SeaList S, sortOrder sortorder)
{
    int i;
    for (i = S.rcd_num / 2; i > 0; i--) //从n/2处往上开始进行筛选 使之成为大顶堆
        Heap_Adjust(S, i, S.rcd_num, sortorder);
    for (i = S.rcd_num; i > 1; i--) //开始调整排序
    {
        Swap_Rcd(&S.rcd[1], &S.rcd[i]);      //第一个记录输出 最后一个记录代替
        Heap_Adjust(S, 1, i - 1, sortorder); //将第一个记录放到数组尾后，将剩余的元素重新调整为大顶堆
    }
}
/**
 * @brief:        归并(归并排序子算法1)
 * @param[in]:    排序表 辅助空间(=S.rcd_num) low m high
 * @return:       void
 * @note:         将有序的S.rcd[low..m]和S.rcd[m+1..high]归并为有序的S.rcd[low..high]
 */
void Merge(SeaList S, int low, int mid, int high, sortOrder sortorder)
{
    RcdType *r = (PtrRcdType)malloc(sizeof(RcdType) * (high - low + 1));
    if (r == NULL)
        return; //如果内存分配不足，两侧成分已排序好，直接返回

    int j = mid + 1, i = low, k = 0;
    while (j <= high && i <= mid)
    {
        if (sortorder == ascending ? S.rcd[i].Key < S.rcd[j].Key : S.rcd[i].Key > S.rcd[j].Key)
            r[k++] = S.rcd[i++];
        else
            r[k++] = S.rcd[j++];
    }
    while (i <= mid) //将剩余记录拷贝到剩余空间中
        r[k++] = S.rcd[i++];
    while (j <= high)
        r[k++] = S.rcd[j++];

    k = 0;
    for (i = low; i <= high; i++)
        S.rcd[i] = r[k++];
    free(r);
}
/**
 * @brief:        归并(归并排序子算法2)
 * @param[in]:    排序表 low high
 * @return:       void
 * @note:         递归实现
 */

void MergeSortRecursion(SeaList S, int low, int high, sortOrder sortorder)
{
    if (low >= high)
        return;
    int mid = (low + high) / 2;
    MergeSortRecursion(S, low, mid, sortorder);      //左半部分
    MergeSortRecursion(S, mid + 1, high, sortorder); //右半部分
    Merge(S, low, mid, high, sortorder);             //归并
}

/**
 * @brief:        归并排序(默认升序)
 * @param[in]:    排序表
 * @return:       null
 * @note:         时间性能：最好:O(nlogn) 最坏:O(nlogn)  空间性能：O(n)
 *                稳定性能：稳定
 */
void Merge_Sort(SeaList S, sortOrder sortorder)
{
    if (!S.rcd || S.rcd_num <= 0)
        return;
    MergeSortRecursion(S, 1, S.rcd_num, sortorder);
}
