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
 * @brief   ����һ��KeyType���͵������
 * @param[in]   seed:��������� 0->time range : 0-range-1 rcd:������� num:Ԫ�ظ���
 * @retval  Satus
 **/
RcdType *_random(int seed, int num, int range)
{
    int i;
    if (range < num)
    {
        printError("Ԫ�ظ������ó����������Χ"); //��ֹ���ִ����ظ�����
        num = range;
    }
    RcdType *rcd = (RcdType *)malloc(sizeof(RcdType) * num);
    if (!rcd)
    {
        printError("�ڴ����!");
        return NULL;
    }
    rcd[0].Key = 0;
    if (seed <= 0)
        srand((unsigned)time(NULL)); //��ʱ����Ϊ����
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
 * @param[in]   SeaList Sruct , SeaList_Length(����0��ַ)
 * @retval  Satus
 * @note    ���������,0��ַ��Ų��ҹؼ���
 **/
Status Init_SeaList(PtrSeaList S, int Length)
{
    if (SeaList_Length > Random_Range)
    {
        printError("��¼�����ó����������Χ!");
        Length = Random_Range;
    }
    if (S->rcd = (RcdType *)malloc(Length * sizeof(RcdType)))
    {
        S->length = Length;
        S->rcd_num = 0;
        S->rcd[0].Key = 0; //0��ַ����ֵ
        return OK;
    }
    else
    {
        printError("�ڴ����");
        return ERROR;
    }
}
/**
 * @brief:        ���������
 * @param[in]:    �����ṹ��ָ��  ��¼����(������0��ַ)
 * @return:       Satus
 * @note:         rcd[0].Key�洢Ԫ�ظ���
 */
Status Creat_SeaList(SeaList *S, int Rcd_Num)
{
    if (Rcd_Num > S->length - 1)
    {
        printError("��¼�������ɳ�����!"); //�ܱ�����0��ַ�ͼ�¼ Rcd_Num��������¼��Ŀ
        Rcd_Num = S->length - 1;             //��� S.rcd_num<S.length-1
    }
    S->rcd = random(Sort_Data_Seed, Rcd_Num, );
    if (!S->rcd)
    {
        printError("���Ա���ʧ��!");
        return ERROR;
    }
    else
    {
        S->rcd_num = S->rcd[0].Key;
        return OK;
    }
}
/**
 * @brief:        ��������
 * @param[in]:    ���Ա�ṹ��
 * @return:       null
 * @note:         ֻ��ӡ��¼ 0��ַ���ݲ���ӡ
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
 * @brief:        ����������¼
 * @param[in]:    ��¼A ��¼B
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
 * @brief:        �������
 * @param[in]:    ����� �����㷨
 * @return:       ����ʱ��
 * @note:         null
 */
int getSortTime(SeaList S, void (*Sort)(SeaList, sortOrder), sortOrder sortorder)
{
    int t_start, t_end;
    Creat_SeaList(&S, Sort_Data_Length);
    char order[4] = "��\0";  //��Ϊ����
    if (sortorder == descending)
        strcpy(order, "��\0");   //��Ϊ����
    if (Sort == Insert_Sort)
        printf("ֱ�Ӳ�������%s\t��", order);
    else if (Sort == BInsert_Sort)
        printf("�۰��������%s\t��", order);
    else if (Sort == Shell_Sort)
        printf("ϣ������%s\t��", order);
    else if (Sort == Select_Sort)
        printf("ѡ������%s\t��", order);
    else if (Sort == Bubble_Sort)
        printf("ð������%s\t��", order);
    else if (Sort == Quick_Sort)
        printf("��������%s\t��", order);
    else if (Sort == Heap_Sort)
        printf("������%s\t��", order);
    else if (Sort == Merge_Sort)
        printf("�鲢����%s\t��", order);
    t_start = clock();
    Sort(S, sortorder);
    t_end = clock();
    printf("%dms\n", t_end - t_start);
    //printSort(S);
    return t_end - t_start;
}
/**
 * @brief:        ������->ֱ�Ӳ�������(Ĭ������)
 * @param[in]:    �����ṹ�� ����ʽ
 * @return:       void
 * @note:         ʱ�����ܣ�O(n^2)  �ռ����ܣ�O(1)
 *                �ȶ����ܣ��ȶ�
 */
void Insert_Sort(SeaList S, sortOrder sortorder)
{
    int i, j;
    for (i = 2; i <= S.rcd_num; i++)
    {
        S.rcd[0] = S.rcd[i];                                                                                     //���Ƶ�������
        for (j = i - 1; sortorder == ascending ? S.rcd[0].Key < S.rcd[j].Key : S.rcd[0].Key > S.rcd[j].Key; j--) //��ǰi-1�����ݵ���Ƚ�
            S.rcd[j + 1] = S.rcd[j]; //��j�����ݴ����ڲ������� ��R[j]�����������1λ
        S.rcd[j + 1] = S.rcd[0]; //��j������С�ڵ��ڲ������ݣ��򽫲������ݲ��뵽j+1��λ�ã���R[j]�ĺ���
    }
}
/**
 * @brief:        �۰��������(Ĭ������)
 * @param[in]:    �����
 * @return:       null
 * @note:         ������ֱ�Ӳ���ıȽϴ����������ƶ�����δ����
 */
void BInsert_Sort(SeaList S, sortOrder sortorder)
{
    int i, j;
    int low, high, mid;
    for (i = 2; i <= S.rcd_num; i++)
    {
        S.rcd[0] = S.rcd[i]; //���Ƶ�������
        low = 1, high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (sortorder == ascending ? S.rcd[0].Key < S.rcd[mid].Key : S.rcd[0].Key > S.rcd[mid].Key)
                high = mid - 1; //������ڵͰ���
            else
                low = mid + 1; //������ڸ߰���
        }
        for (j = i - 1; j >= high + 1; j--) //��¼����
            S.rcd[j + 1] = S.rcd[j];
        S.rcd[high + 1] = S.rcd[0]; //����
    }
}
/**
 * @brief:        ϣ���������㷨(һ��ϣ������)
 * @param[in]:    ����� ����dk
 * @return:       null
 * @note:         ����ֱ�Ӳ��������㷨
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
                S.rcd[j + dk] = S.rcd[j]; //��¼����
            S.rcd[j + dk] = S.rcd[0];     //����
        }
    }
}
/**
 * @brief:        ����������
 * @param[in]:    �����
 * @return:       ������
 * @note:         ������0��ַ�洢������������
 */
Status getDlta(SeaList *S)
{
    int dlta_length = 0; //������������
    dlta_length = ((S->rcd_num / 2 - 1) / 2) + 1;
    S->dlta = (int *)malloc(sizeof(int) * (dlta_length + 1));
    if (!S->dlta)
    {
        printError("�ڴ����");
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
 * @brief:        ϣ������(Ĭ������)
 * @param[in]:    ����� ������ ������
 * @return:       null
 * @note:         dlta[k]=2^(t-k+1)-1 --> O(n^(3/2)) tΪ��������
 *                ��n��ĳ���ض���Χ��,�ȽϺ��ƶ�����ԼΪn^1.3
 *                ��n->��ʱ���ɼ��ٵ�n(log2n)^2
 *                ��������dlta[]�е�ֵû�г�1֮��Ĺ�����,�������һ������ֵ�������1
 */
void _Shell_Sort(SeaList S, int dlta[], int t, sortOrder sortorder)
{
    //���������ж�˳���S��ϣ������
    int i;
    for (i = 0; i < t; i++)
        ShellInsert(S, dlta[i], sortorder);
}
void Shell_Sort(SeaList S, sortOrder sortorder)
{
    _Shell_Sort(S, S.dlta + 1, S.dlta[0], sortorder);
}
/**
 * @brief:        ������->��ѡ������(Ĭ������)
 * @param[in]:    �����ṹ��
 * @return:       void
 * @note:         ʱ�����ܣ�O(n^2)  �ռ����ܣ�O(1)
 *                �ȶ����ܣ��ȶ�
 */
void Select_Sort(SeaList S, sortOrder sortorder)
{
    int i, j, k;
    for (i = 1; i <= S.rcd_num; i++)
    {
        k = i;
        for (j = i; j <= S.rcd_num; j++) //Ѱ����Сֵ����λ��
        {
            if (sortorder == ascending ? S.rcd[j].Key < S.rcd[k].Key : S.rcd[j].Key > S.rcd[k].Key)
                k = j;
        }
        if (k != i)
            Swap_Rcd(&S.rcd[i], &S.rcd[k]);
    }
}
/**
 * @brief:        ������->ð������(Ĭ������)
 * @param[in]:    �����ṹ��
 * @return:       void
 * @note:         ʱ�����ܣ�O(n^2)  �ռ����ܣ�O(1)
 *                �ȶ����ܣ��ȶ�
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
 * @brief:        �����������㷨1
 * @param[in]:    ����� low high
 * @return:       ��������λ��
 * @note:         һ�˿�������
 */
int Partition(SeaList S, int low, int high, sortOrder sortorder)
{
    KeyType pivotkey = S.rcd[low].Key;
    S.rcd[0] = S.rcd[low]; //�ݴ������¼
    while (low < high)     //�ӱ�����˽������м�ɨ��
    {
        while (low < high && (sortorder == ascending ? S.rcd[high].Key >= pivotkey : S.rcd[high].Key <= pivotkey))
            high--;
        S.rcd[low] = S.rcd[high]; //���������¼С�ļ�¼�Ƶ��Ͷ�
        while (low < high && (sortorder == ascending ? S.rcd[low].Key <= pivotkey : S.rcd[low].Key >= pivotkey))
            low++;
        S.rcd[high] = S.rcd[low]; //���������¼��ļ�¼�Ƶ��߶�
    }
    S.rcd[low] = S.rcd[0];
    return low;
}
/**
 * @brief:        �����������㷨2
 * @param[in]:    �����
 * @return:       null
 * @note:         ʱ�����ܣ����:O(nlogn) �:O(n^2)  �ռ����ܣ�O(logn)
 *                �ȶ����ܣ����ȶ�
 */
void QSort(SeaList S, int low, int high, sortOrder sortorder)
{
    int pivotc;
    if (low < high)
    {
        pivotc = Partition(S, low, high, sortorder); //���ݹ��ӱ�ֳ�������
        QSort(S, low, pivotc - 1, sortorder);        //����
        QSort(S, pivotc + 1, high, sortorder);       //����
    }
}
/**
 * @brief:        ���������㷨(Ĭ������)
 * @param[in]:    �����
 * @return:       null
 * @note:         ʱ�����ܣ����:O(nlogn) �:O(n^2)  �ռ����ܣ�O(logn)
 *                �ȶ����ܣ����ȶ�
 */
void Quick_Sort(SeaList S, sortOrder sortorder)
{
    QSort(S, 1, S.rcd_num, sortorder);
}
/**
 * @brief:        ɸѡ�㷨  -->  ���ɴ󶥶�
 * @param[in]:    ������ӱ� s(��ʼ��ַ) m(������ַ)
 * @return:       null
 * @note:         ��֪S.rcd[s..m]�еĹؼ��ֳ�H.r[s]�������ѵĶ���,����S.rcd[s]
 * �Ĺؼ���,ʹ֮��Ϊһ���󶥶�
 */
void Heap_Adjust(SeaList S, int s, int m, sortOrder sortorder)
{
    int j;
    S.rcd[0] = S.rcd[s];            //�ݴ������¼
    for (j = 2 * s; j <= m; j *= 2) //���Źؼ���Key�ϴ�ĺ��ӽ������ɸѡ
    {
        if (j < m && (sortorder == ascending ? S.rcd[j].Key < S.rcd[j + 1].Key : S.rcd[j].Key > S.rcd[j + 1].Key)) //jΪKey�ϴ�ļ�¼�±�
            j++;                                                                                                   //��ǰ��ĵ����Һ��ӻ��ֵ�
        if (sortorder == ascending ? S.rcd[0].Key >= S.rcd[j].Key : S.rcd[0].Key <= S.rcd[j].Key)                  //���Ѷ����ڵ�ǰ���Ĺؼ����򲻵���
            break;
        S.rcd[s] = S.rcd[j]; //����s��jλ�õļ�¼�����滻
        s = j;
    }
    S.rcd[s] = S.rcd[0];
}
/**
 * @brief:        ������(Ĭ������)
 * @param[in]:    �����
 * @return:       null
 * @note:         ʱ�����ܣ����:O(nlogn) �:O(nlogn)  �ռ����ܣ�O(1)
 *                �ȶ����ܣ����ȶ�
 */
void Heap_Sort(SeaList S, sortOrder sortorder)
{
    int i;
    for (i = S.rcd_num / 2; i > 0; i--) //��n/2�����Ͽ�ʼ����ɸѡ ʹ֮��Ϊ�󶥶�
        Heap_Adjust(S, i, S.rcd_num, sortorder);
    for (i = S.rcd_num; i > 1; i--) //��ʼ��������
    {
        Swap_Rcd(&S.rcd[1], &S.rcd[i]);      //��һ����¼��� ���һ����¼����
        Heap_Adjust(S, 1, i - 1, sortorder); //����һ����¼�ŵ�����β�󣬽�ʣ���Ԫ�����µ���Ϊ�󶥶�
    }
}
/**
 * @brief:        �鲢(�鲢�������㷨1)
 * @param[in]:    ����� �����ռ�(=S.rcd_num) low m high
 * @return:       void
 * @note:         �������S.rcd[low..m]��S.rcd[m+1..high]�鲢Ϊ�����S.rcd[low..high]
 */
void Merge(SeaList S, int low, int mid, int high, sortOrder sortorder)
{
    RcdType *r = (PtrRcdType)malloc(sizeof(RcdType) * (high - low + 1));
    if (r == NULL)
        return; //����ڴ���䲻�㣬����ɷ�������ã�ֱ�ӷ���

    int j = mid + 1, i = low, k = 0;
    while (j <= high && i <= mid)
    {
        if (sortorder == ascending ? S.rcd[i].Key < S.rcd[j].Key : S.rcd[i].Key > S.rcd[j].Key)
            r[k++] = S.rcd[i++];
        else
            r[k++] = S.rcd[j++];
    }
    while (i <= mid) //��ʣ���¼������ʣ��ռ���
        r[k++] = S.rcd[i++];
    while (j <= high)
        r[k++] = S.rcd[j++];

    k = 0;
    for (i = low; i <= high; i++)
        S.rcd[i] = r[k++];
    free(r);
}
/**
 * @brief:        �鲢(�鲢�������㷨2)
 * @param[in]:    ����� low high
 * @return:       void
 * @note:         �ݹ�ʵ��
 */

void MergeSortRecursion(SeaList S, int low, int high, sortOrder sortorder)
{
    if (low >= high)
        return;
    int mid = (low + high) / 2;
    MergeSortRecursion(S, low, mid, sortorder);      //��벿��
    MergeSortRecursion(S, mid + 1, high, sortorder); //�Ұ벿��
    Merge(S, low, mid, high, sortorder);             //�鲢
}

/**
 * @brief:        �鲢����(Ĭ������)
 * @param[in]:    �����
 * @return:       null
 * @note:         ʱ�����ܣ����:O(nlogn) �:O(nlogn)  �ռ����ܣ�O(n)
 *                �ȶ����ܣ��ȶ�
 */
void Merge_Sort(SeaList S, sortOrder sortorder)
{
    if (!S.rcd || S.rcd_num <= 0)
        return;
    MergeSortRecursion(S, 1, S.rcd_num, sortorder);
}
