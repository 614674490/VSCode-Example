/*
 * @Author: Ken Kaneki
 * @Date: 2020-04-08 13:28:49
 * @LastEditTime: 2020-05-21 10:57:48
 * @Description: README
 * @FilePath: \bank\bank.cpp
 */
#include <iostream>
#include <string>
using namespace std;
#define Range 10

int MAX[Range][Range] = {0};        //最大需求
int Allocation[Range][Range] = {0}; //已分配资源向量
int Need[Range][Range] = {0};       //需要资源向量

int Available[Range] = {0}; //可用资源向量

int enterprogram = 0, resource_count = 0; //请求资源进程数 资源种类
/**
 * @description: 输出状态表
 * @param {void}
 * @return: void
 */
void print_StatueTable(int Work[][Range], int Finish[], int Work_Allocation[][Range])
{
    int i, j;
    char k, t = 'A';
    cout << "Available:";
    for (i = 0; i < resource_count; i++)
    {
        cout << Available[i] << "  ";
    }
    cout << endl;
    cout << "\tWork\t\tMax\t\tAllocation\tNeed\t\tWork+Allocation\tFinish" << endl;
    cout << '\t';
    for (k = 0; k < 3 * resource_count; k++)
    {
        cout << t << "  ";
        t = 'A';
        if (((k + 1) % resource_count) == 0)
        {
            if (k != 3 * resource_count - 1)
                cout << '\t';
            else
                cout << endl;
        }
        t += (k + 1) % resource_count;
    }
    for (j = 0; j < enterprogram; j++)
    {
        cout << 'P' << j + 1 << '\t';
        for (i = 0; i < resource_count; i++)
        {
            if (Work[j][i] >= 0)
                cout << Work[j][i] << "  ";
            else
                cout << "x  ";
        }
        cout << '\t';
        for (i = 0; i < resource_count; i++)
        {
            cout << MAX[j][i] << "  ";
        }
        cout << '\t';
        for (i = 0; i < resource_count; i++)
        {
            cout << Allocation[j][i] << "  ";
        }
        cout << '\t';
        for (i = 0; i < resource_count; i++)
        {
            cout << Need[j][i] << "  ";
        }
        cout << '\t';
        for (i = 0; i < resource_count; i++)
        {
            if (Work_Allocation[j][i] >= 0)
                cout << Work_Allocation[j][i] << "  ";
            else
                cout << "x  ";
        }
        if (Finish[j])
            cout << "\tTRUE";
        else
            cout << "\tFALSE";
        cout << endl;
    }
}
/**
 * @description: 交互程序
 * @param {进程数 资源种类数}
 * @return: void
 */
void Instance(int M, int N)
{
    int i = 0, j = 0;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            MAX[i][j] = 0;
            Allocation[i][j] = 0;
            Need[i][j] = 0;
        }
    }
    cout << "资源数量：" << endl; //初始总资源数量
    for (i = 0; i < N; i++)
    {
        cout << "第" << i + 1 << "类：";
        cin >> Available[i];
    }
    for (i = 0; i < M; i++)
    {
        cout << "P" << i + 1 << "最大需求:" << endl;
        for (j = 0; j < N; j++)
        {
            cout << "第" << j + 1 << "类：";
            cin >> MAX[i][j];
        }
        cout << "P" << i + 1 << "已分配:" << endl;
        for (j = 0; j < N; j++)
        {
            cout << "第" << j + 1 << "类：";
            cin >> Allocation[i][j];

            Need[i][j] = MAX[i][j] - Allocation[i][j];
            Available[j] -= Allocation[i][j];
        }
    }
}
/**
 * @description: 当前系统是否处于安全状态，执行安全性算法
 * @param {int,int}
 * @return: 1: safe 0: unsafe
 */
int Issafe(int M, int N)
{
    int Work[Range], Finish[Range], Thread = 0, temp[Range], flag = 1, i, j, order[Range];
    int k, Work_Temp[Range][Range], Work_Allocation[Range][Range];
    for (i = 0; i < M; i++) //赋初值,防止无法分配时向量越界
    {
        for (j = 0; j < N; j++)
        {
            Work_Temp[i][j] = -1;
            Work_Allocation[i][j] = -1;
        }
    }
    for (i = 0; i < N; i++) //工作向量初始化
        Work[i] = Available[i];
    for (i = 0; i < M; i++)
    {
        Finish[i] = 0; //完成向量(1:TRUE 0:FALSE)
        temp[i] = 1;   //默认各个进程均可满足需求
    }
    while (Thread < M && flag == 1)
    {
        for (i = 0; i < M; i++)
        {
            if (!Finish[i]) //对未结束进程进行操作
            {
                temp[i] = 1;
                for (j = 0; j < N; j++)
                {
                    if (Work[j] < Need[i][j]) //遍历查询可被满足的进程
                        temp[i] = 0;          //跳过此进程;
                }
                if (temp[i] != 0)
                {
                    for (k = 0; k < N; k++)
                        Work_Temp[i][k] = Work[k];
                    Finish[i] = 1;         //标记完成
                    order[Thread] = i + 1; //记录结束的进程顺序
                    Thread++;              //完成数+1
                    for (j = 0; j < N; j++)
                        Work[j] += Allocation[i][j]; //回收资源
                    for (k = 0; k < N; k++)
                        Work_Allocation[i][k] = Work[k];
                    goto exit;
                }
            }
        }
    exit:
        flag = 0;
        for (i = 0; i < M; i++)
        {
            if (Finish[i] == 0) //所有进程均结束 退出while循环
                if (temp[i])    //仍然存在无法结束的进程 退出while循环
                    flag = 1;   //存在可以结束的但未结束的进程 继续结束进程
        }
    }
    print_StatueTable(Work_Temp, Finish, Work_Allocation);
    if (Thread == M)
    {
        cout << "存在安全序列:" << endl;
        cout << '{';
        for (i = 0; i < Thread; i++)
            cout << "p" << order[i] << " ";
        cout << '}' << endl;
        return 1;
    }
    else
        return 0;
}
/**
 * @description: 预分配
 * @param {进程号(数组) 进程数 资源种类数}
 * @return: 1: 允许分配 0: 不可分配
 */
int Request(int num, int M, int N)
{
    int request1[10], i;
    cout << "进程" << num + 1 << "发请求：" << endl;
    for (i = 0; i < N; i++) //输入请求资源数
    {
        cout << "需第" << i + 1 << "类:";
        cin >> request1[i];
        if (request1[i] > Need[num][i])
        {
            cout << "需要超过宣称最大值，错误，不分配" << endl;
            return 0;
        }
        else if (request1[i] > Available[i])
        {
            cout << "无足够资源，等待" << endl;
            return 0;
        }
    }
    //满足以上条件后进行分配，更新资源向量值
    for (i = 0; i < N; i++)
    {
        Available[i] -= request1[i];       //先将资源分配给进程
        Allocation[num][i] += request1[i]; //进程已分配资源数增加
        Need[num][i] -= request1[i];       //对应需求资源数减少
    }
    if (Issafe(M, N))
    {
        cout << "满足条件，分配" << endl;
        return 1;
    }
    else
    {
        cout << "分配后进入不安全态，不分配" << endl;
        for (i = 0; i < N; i++) //恢复初值
        {
            Available[i] += request1[i];
            Allocation[num][i] -= request1[i];
            Need[num][i] += request1[i];
        }
        return 0;
    }
}

int main()
{
    int progress_id = 0, safestatue = 0;
    char ans = 'N';
    do
    {
        cout << "请求资源进程数:";
        cin >> enterprogram;
        cout << "资源种类:";
        cin >> resource_count;
        Instance(enterprogram, resource_count);
        safestatue = Issafe(enterprogram, resource_count);
        if (safestatue)
        {
            cout << "系统处于安全态!" << endl;
            ans = 'N';
            do
            {
                cout << "输入请求进程号（如1或2或3等）:";
                cin >> progress_id;
                while (progress_id > enterprogram || progress_id < 1) //进程号输入限制
                {
                    cout << "error!the number should between 1 and " << enterprogram << endl;
                    cout << "input the progress number:";
                    cin >> progress_id;
                }
                Request(progress_id - 1, enterprogram, resource_count);
                cout << "是否继续进行分配(N:停止分配 Y:继续分配)" << endl;
                cin >> ans;
                while (!(ans == 'N' | ans == 'Y'))
                {
                    cout << "input error! please input again" << endl;
                    cin >> ans;
                }
            } while (ans == 'Y');
        }
        else
        {
            cout << "it is not in a safe condition!" << endl;
            cout << "其他进程请求不分配！(N:结束测试 Y:重新输入)" << endl;
            cin >> ans;
            while (!(ans == 'N' | ans == 'Y'))
            {
                cout << "input error! please input again" << endl;
                cin >> ans;
            }
        }
    } while (ans == 'Y');

    system("pause");
    return 0;
}
