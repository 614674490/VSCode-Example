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

int MAX[Range][Range] = {0};        //�������
int Allocation[Range][Range] = {0}; //�ѷ�����Դ����
int Need[Range][Range] = {0};       //��Ҫ��Դ����

int Available[Range] = {0}; //������Դ����

int enterprogram = 0, resource_count = 0; //������Դ������ ��Դ����
/**
 * @description: ���״̬��
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
 * @description: ��������
 * @param {������ ��Դ������}
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
    cout << "��Դ������" << endl; //��ʼ����Դ����
    for (i = 0; i < N; i++)
    {
        cout << "��" << i + 1 << "�ࣺ";
        cin >> Available[i];
    }
    for (i = 0; i < M; i++)
    {
        cout << "P" << i + 1 << "�������:" << endl;
        for (j = 0; j < N; j++)
        {
            cout << "��" << j + 1 << "�ࣺ";
            cin >> MAX[i][j];
        }
        cout << "P" << i + 1 << "�ѷ���:" << endl;
        for (j = 0; j < N; j++)
        {
            cout << "��" << j + 1 << "�ࣺ";
            cin >> Allocation[i][j];

            Need[i][j] = MAX[i][j] - Allocation[i][j];
            Available[j] -= Allocation[i][j];
        }
    }
}
/**
 * @description: ��ǰϵͳ�Ƿ��ڰ�ȫ״̬��ִ�а�ȫ���㷨
 * @param {int,int}
 * @return: 1: safe 0: unsafe
 */
int Issafe(int M, int N)
{
    int Work[Range], Finish[Range], Thread = 0, temp[Range], flag = 1, i, j, order[Range];
    int k, Work_Temp[Range][Range], Work_Allocation[Range][Range];
    for (i = 0; i < M; i++) //����ֵ,��ֹ�޷�����ʱ����Խ��
    {
        for (j = 0; j < N; j++)
        {
            Work_Temp[i][j] = -1;
            Work_Allocation[i][j] = -1;
        }
    }
    for (i = 0; i < N; i++) //����������ʼ��
        Work[i] = Available[i];
    for (i = 0; i < M; i++)
    {
        Finish[i] = 0; //�������(1:TRUE 0:FALSE)
        temp[i] = 1;   //Ĭ�ϸ������̾�����������
    }
    while (Thread < M && flag == 1)
    {
        for (i = 0; i < M; i++)
        {
            if (!Finish[i]) //��δ�������̽��в���
            {
                temp[i] = 1;
                for (j = 0; j < N; j++)
                {
                    if (Work[j] < Need[i][j]) //������ѯ�ɱ�����Ľ���
                        temp[i] = 0;          //�����˽���;
                }
                if (temp[i] != 0)
                {
                    for (k = 0; k < N; k++)
                        Work_Temp[i][k] = Work[k];
                    Finish[i] = 1;         //������
                    order[Thread] = i + 1; //��¼�����Ľ���˳��
                    Thread++;              //�����+1
                    for (j = 0; j < N; j++)
                        Work[j] += Allocation[i][j]; //������Դ
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
            if (Finish[i] == 0) //���н��̾����� �˳�whileѭ��
                if (temp[i])    //��Ȼ�����޷������Ľ��� �˳�whileѭ��
                    flag = 1;   //���ڿ��Խ����ĵ�δ�����Ľ��� ������������
        }
    }
    print_StatueTable(Work_Temp, Finish, Work_Allocation);
    if (Thread == M)
    {
        cout << "���ڰ�ȫ����:" << endl;
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
 * @description: Ԥ����
 * @param {���̺�(����) ������ ��Դ������}
 * @return: 1: ������� 0: ���ɷ���
 */
int Request(int num, int M, int N)
{
    int request1[10], i;
    cout << "����" << num + 1 << "������" << endl;
    for (i = 0; i < N; i++) //����������Դ��
    {
        cout << "���" << i + 1 << "��:";
        cin >> request1[i];
        if (request1[i] > Need[num][i])
        {
            cout << "��Ҫ�����������ֵ�����󣬲�����" << endl;
            return 0;
        }
        else if (request1[i] > Available[i])
        {
            cout << "���㹻��Դ���ȴ�" << endl;
            return 0;
        }
    }
    //����������������з��䣬������Դ����ֵ
    for (i = 0; i < N; i++)
    {
        Available[i] -= request1[i];       //�Ƚ���Դ���������
        Allocation[num][i] += request1[i]; //�����ѷ�����Դ������
        Need[num][i] -= request1[i];       //��Ӧ������Դ������
    }
    if (Issafe(M, N))
    {
        cout << "��������������" << endl;
        return 1;
    }
    else
    {
        cout << "�������벻��ȫ̬��������" << endl;
        for (i = 0; i < N; i++) //�ָ���ֵ
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
        cout << "������Դ������:";
        cin >> enterprogram;
        cout << "��Դ����:";
        cin >> resource_count;
        Instance(enterprogram, resource_count);
        safestatue = Issafe(enterprogram, resource_count);
        if (safestatue)
        {
            cout << "ϵͳ���ڰ�ȫ̬!" << endl;
            ans = 'N';
            do
            {
                cout << "����������̺ţ���1��2��3�ȣ�:";
                cin >> progress_id;
                while (progress_id > enterprogram || progress_id < 1) //���̺���������
                {
                    cout << "error!the number should between 1 and " << enterprogram << endl;
                    cout << "input the progress number:";
                    cin >> progress_id;
                }
                Request(progress_id - 1, enterprogram, resource_count);
                cout << "�Ƿ�������з���(N:ֹͣ���� Y:��������)" << endl;
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
            cout << "�����������󲻷��䣡(N:�������� Y:��������)" << endl;
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
