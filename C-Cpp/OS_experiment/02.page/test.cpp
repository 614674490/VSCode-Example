#include <iostream>
using namespace std;

const int MaxNumber = 100;
struct Node
{
    char elem;               //���пռ����ƣ���д��ĸ��
    int FreePartition;       //���пռ仹ʣ��Ĵ�С
    char Par_set[MaxNumber]; //������Ľ������ƣ�Сд��ĸ��
};
Node FreePartition[MaxNumber];
Node FirstPartition[MaxNumber];
Node CycleFirstPartition[MaxNumber];
Node BestPartition[MaxNumber];
Node WorstPartition[MaxNumber];
int ProcessNeed[MaxNumber];
Node FreePartition_temp[MaxNumber];
int PartitionNum, ProcessNum;

//PartitionNum��ʾ�ռ�����ĸ�����ProcessNum��ʾ���̸�����
//@@@@@@@@@@@@@@@@@@@@@@@@@@ ������пռ�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void print(Node *a) //�������������
{
    for (int i = 0; i < PartitionNum; cout << "���пռ�����" << a[i].elem << " ,  ��ʣ��Ŀռ��С " << a[i].FreePartition << " ,  ������Ľ���" << a[i++].Par_set << endl)
        ;
}
void full_item(char *source, char item) //���¿��з�������Ľ�����Ϣ
{
    int temp = 1; //j��¼�ܹ��ж��ٽ����ˣ�
    for (int i = 0; i < MaxNumber; i++)
    {
        if (source[i] != '#')
            temp++;
        else
            break;
    }
    while (temp-- >= 0)
    {
        source[temp + 1] = source[temp]; //�����еĽ��̺���һ����
    }
    source[0] = item; //д���½��̣�
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ �״����򣨿ɰ�������ͽ�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void automatic_sort(int choice)
{
    int i = 0, j = 0;
    bool quit = false;
    Node source_temp;
    if (choice == 0)
    { //�����������򣻼���best first�㷨�����п��пռ�������䡣

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
    { //���ս������򣻼���worst first�㷨�����п��пռ�������䡣

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

//@@@@@@@@@@@@@@@@@@@@@@@@@@����������� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void crete()
{
    for (int i = 0; i < PartitionNum; FreePartition_temp[i] = FreePartition[i], i++)
        ;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ �״���Ӧ�㷨(first fit)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
                FirstPartition[j].FreePartition -= ProcessNeed[i]; //����ʣ��ռ���Ϣ
                full_item(FirstPartition[j].Par_set, 'a' + i);     //���·�����Ķ���
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ ѭ���״���Ӧ�㷨��next first) @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool next_first()
{
    int i = 0, j = 0;
    int next_site = 0;            //�´ο�ʼѰַ���±�
    int cycle_num = PartitionNum; //ѭ������
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
                CycleFirstPartition[j - 1].FreePartition -= ProcessNeed[i]; //����ʣ��ռ���Ϣ
                full_item(CycleFirstPartition[j - 1].Par_set, 'a' + i);     //���·�����Ķ���
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ �����Ӧ�㷨��best first��@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool best_first()
{
    int choice = 0;
    automatic_sort(choice); //�Ƚ�������

    bool success_temp = false;
    for (int i = 0; i < ProcessNum; i++)
    {
        success_temp = false;
        for (int j = 0; j < PartitionNum; j++)
        {

            if (ProcessNeed[i] <= BestPartition[j].FreePartition)
            {
                BestPartition[j].FreePartition -= ProcessNeed[i]; //����ʣ��ռ���Ϣ
                full_item(BestPartition[j].Par_set, 'a' + i);     //���·�����Ķ���
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
        automatic_sort(choice); //��������
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@ ���Ӧ�㷨��worst first��   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool worst_first()
{

    int choice = 1;
    automatic_sort(choice); //�Ƚ�������
    bool success_temp = false;
    for (int i = 0; i < ProcessNum; i++)
    {
        success_temp = false;
        for (int j = 0; j < PartitionNum; j++)
        {

            if (ProcessNeed[i] <= WorstPartition[j].FreePartition)
            {
                WorstPartition[j].FreePartition -= ProcessNeed[i]; //����ʣ��ռ���Ϣ
                full_item(WorstPartition[j].Par_set, 'a' + i);     //���·�����Ķ���
                success_temp = true;
                break;
            }
        }
        if (!success_temp)
            return false;
        automatic_sort(choice); //��������
    }

    return true;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@������ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void main()
{

    freopen("text.txt", "rt", stdin);
    int choice = 0;
    cout << "�㷨ѡ��:" << endl
         << "1-�״���Ӧ�㷨��2-ѭ���״���Ӧ�㷨��3-�����Ӧ�㷨��4-���Ӧ�㷨" << endl
         << endl;
    //cout<<"��������з����ĸ���n"<<endl;
    cin >> PartitionNum;
    //cout<<"��������̸���m"<<endl;
    cin >> ProcessNum;

    int i = 0;

    for (i = 0; i<PartitionNum; cin>> FreePartition[i].FreePartition, FreePartition[i].elem = 'A' + i, FreePartition[i++].Par_set[0] = '#')
        ;

    cout << "��ʼ�����" << endl;
    print(&FreePartition[0]);
    cout << "!!!!!!!!!!!��ʼ�����" << endl
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
            cout << "�״���Ӧ�㷨" << endl;
            if (first_fit())
                print(&FirstPartition[0]);
            else
                cout << "�״���Ӧ�㷨����ʧ��" << endl;
        }
        else if (choice == 2)
        {
            cout << "ѭ���״���Ӧ�㷨" << endl;
            if (next_first())
                print(&CycleFirstPartition[0]);
            else
                cout << "ѭ���״���Ӧ�㷨����ʧ��" << endl;
        }
        else if (choice == 3)
        {
            cout << "�����Ӧ�㷨" << endl;
            if (best_first())
                print(&BestPartition[0]);
            else
                cout << "�����Ӧ�㷨����ʧ��" << endl;
        }
        else if (choice == 4)
        {
            cout << "���Ӧ�㷨" << endl;
            if (worst_first())
                print(&WorstPartition[0]);
            else
                cout << "���Ӧ�㷨����ʧ��" << endl;
        }
        else
        {
            cout << "�����ѡ������choiceֵ�д�" << endl;
        }
        cout << endl
             << endl;
    }
}
