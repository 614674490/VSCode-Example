#include <iostream>
using namespace std;

const int MaxNumber = 100;
struct Node
{
    char elem;               //空闲空间名称（大写字母）
    int FreePartition;       //空闲空间还剩余的大小
    char Par_set[MaxNumber]; //分配给的进程名称（小写字母）
};
Node FreePartition[MaxNumber];
Node FirstPartition[MaxNumber];
Node CycleFirstPartition[MaxNumber];
Node BestPartition[MaxNumber];
Node WorstPartition[MaxNumber];
int ProcessNeed[MaxNumber];
Node FreePartition_temp[MaxNumber];
int PartitionNum, ProcessNum;

//PartitionNum表示空间分区的个数，ProcessNum表示进程个数；
//@@@@@@@@@@@@@@@@@@@@@@@@@@ 输出空闲空间分配情况@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void print(Node *a) //输出最后分配的情况
{
    for (int i = 0; i < PartitionNum; cout << "空闲空间名称" << a[i].elem << " ,  还剩余的空间大小 " << a[i].FreePartition << " ,  分配给的进程" << a[i++].Par_set << endl)
        ;
}
void full_item(char *source, char item) //更新空闲分区分配的进程信息
{
    int temp = 1; //j记录总共有多少进程了；
    for (int i = 0; i < MaxNumber; i++)
    {
        if (source[i] != '#')
            temp++;
        else
            break;
    }
    while (temp-- >= 0)
    {
        source[temp + 1] = source[temp]; //将已有的进程后退一个；
    }
    source[0] = item; //写入新进程；
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ 首次排序（可按照升序和降序排序）@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void automatic_sort(int choice)
{
    int i = 0, j = 0;
    bool quit = false;
    Node source_temp;
    if (choice == 0)
    { //按照升序排序；即用best first算法来进行空闲空间分区分配。

        for (i = 0; i < PartitionNum - 1; i++)
        {
            quit = true;
            for (j = 0; j < PartitionNum - (i + 1); j++)
                if (BestPartition[j].FreePartition > BestPartition[j + 1].FreePartition)
                {
                    quit = false;
                    source_temp = BestPartition[j];
                    BestPartition[j] = BestPartition[j + 1];
                    BestPartition[j + 1] = source_temp;
                }
            if (quit)
                return;
        }
    }

    else
    { //按照降序排序；即用worst first算法来进行空闲空间分区分配。

        for (i = 0; i < PartitionNum - 1; i++)
        {
            quit = true;
            for (j = 0; j < PartitionNum - (i + 1); j++)
                if (WorstPartition[j].FreePartition < WorstPartition[j + 1].FreePartition)
                {
                    quit = false;
                    source_temp = WorstPartition[j];
                    WorstPartition[j] = WorstPartition[j + 1];
                    WorstPartition[j + 1] = source_temp;
                }
            if (quit)
                return;
        }
    }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@清楚已有数据 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void crete()
{
    for (int i = 0; i < PartitionNum; FreePartition_temp[i] = FreePartition[i], i++)
        ;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ 首次适应算法(first fit)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool first_fit()
{
    int i = 0, j = 0;
    bool success_temp = false;

    for (i = 0; i < ProcessNum; i++)
    {
        success_temp = false;
        for (j = 0; j < PartitionNum; j++)
        {

            if (ProcessNeed[i] <= FirstPartition[j].FreePartition)
            {
                FirstPartition[j].FreePartition -= ProcessNeed[i]; //更新剩余空间信息
                full_item(FirstPartition[j].Par_set, 'a' + i);     //更新分配给的队列
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ 循环首次适应算法（next first) @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool next_first()
{
    int i = 0, j = 0;
    int next_site = 0;            //下次开始寻址的下标
    int cycle_num = PartitionNum; //循环次数
    bool success_temp = false;
    j = next_site;
    for (i = 0; i < ProcessNum; i++)
    {
        success_temp = false;
        cycle_num = PartitionNum;

        while (cycle_num--)
        {
            j = (++next_site) % PartitionNum;
            if (ProcessNeed[i] <= CycleFirstPartition[j - 1].FreePartition)
            {
                CycleFirstPartition[j - 1].FreePartition -= ProcessNeed[i]; //更新剩余空间信息
                full_item(CycleFirstPartition[j - 1].Par_set, 'a' + i);     //更新分配给的队列
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ 最佳适应算法（best first）@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool best_first()
{
    int choice = 0;
    automatic_sort(choice); //先进行排序

    bool success_temp = false;
    for (int i = 0; i < ProcessNum; i++)
    {
        success_temp = false;
        for (int j = 0; j < PartitionNum; j++)
        {

            if (ProcessNeed[i] <= BestPartition[j].FreePartition)
            {
                BestPartition[j].FreePartition -= ProcessNeed[i]; //更新剩余空间信息
                full_item(BestPartition[j].Par_set, 'a' + i);     //更新分配给的队列
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
        automatic_sort(choice); //进行排序
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ 最坏适应算法（worst first）   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool worst_first()
{

    int choice = 1;
    automatic_sort(choice); //先进行排序
    bool success_temp = false;
    for (int i = 0; i < ProcessNum; i++)
    {
        success_temp = false;
        for (int j = 0; j < PartitionNum; j++)
        {

            if (ProcessNeed[i] <= WorstPartition[j].FreePartition)
            {
                WorstPartition[j].FreePartition -= ProcessNeed[i]; //更新剩余空间信息
                full_item(WorstPartition[j].Par_set, 'a' + i);     //更新分配给的队列
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
        automatic_sort(choice); //进行排序
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@主程序 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void main()
{

    freopen("text.txt", "rt", stdin);
    int choice = 0;
    cout << "算法选择:" << endl
         << "1-首次适应算法，2-循环首次适应算法，3-最佳适应算法，4-最坏适应算法" << endl
         << endl;
    //cout<<"请输入空闲分区的个数n"<<endl;
    cin >> PartitionNum;
    //cout<<"请输入进程个数m"<<endl;
    cin >> ProcessNum;

    int i = 0;

    for (i = 0; i<PartitionNum; cin>> FreePartition[i].FreePartition, FreePartition[i].elem = 'A' + i, FreePartition[i++].Par_set[0] = '#')
        ;

    cout << "初始化情况" << endl;
    print(&FreePartition[0]);
    cout << "!!!!!!!!!!!初始化情况" << endl
         << endl
         << endl
         << endl;

    for (i = 0; i<ProcessNum; cin>> ProcessNeed[i++])
        ;

    for (i = 0; i < PartitionNum; WorstPartition[i] = BestPartition[i] = CycleFirstPartition[i] = FirstPartition[i] = FreePartition[i], i++)
        ;

    while (cin >> choice)
    {
        cout << "@@@@@@@@@@@@@" << endl;
        if (choice == 1)
        {
            cout << "首次适应算法" << endl;
            if (first_fit())
                print(&FirstPartition[0]);
            else
                cout << "首次适应算法分配失败" << endl;
        }
        else if (choice == 2)
        {
            cout << "循环首次适应算法" << endl;
            if (next_first())
                print(&CycleFirstPartition[0]);
            else
                cout << "循环首次适应算法分配失败" << endl;
        }
        else if (choice == 3)
        {
            cout << "最佳适应算法" << endl;
            if (best_first())
                print(&BestPartition[0]);
            else
                cout << "最佳适应算法分配失败" << endl;
        }
        else if (choice == 4)
        {
            cout << "最坏适应算法" << endl;
            if (worst_first())
                print(&WorstPartition[0]);
            else
                cout << "最坏适应算法分配失败" << endl;
        }
        else
        {
            cout << "输入的选择数的choice值有错" << endl;
        }
        cout << endl
             << endl;
    }
}
