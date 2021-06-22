/*
 * @Author: Ken Kaneki
 * @Date: 2020-06-01 23:39:04
 * @LastEditTime: 2020-06-12 11:20:29
 * @Description: README
 * @FilePath: \DynamicPartition_V1.0\source\main.cpp
 */
#include "algorithm.h"
//converting to execution character set: Illegal byte sequence
void print(Partition a)
{
	cout << a << endl;
}

void doSomething()
{
	cout << endl
		 << "�ѷ������" << endl
		 << "to do something" << endl
		 << "ʹ����ɣ���ʼ���ա���������" << endl
		 << endl;
}

int main()
{
	vector<vector<int>> cache(2); //��ά��̬���飬�����ѷ���ķ�����Ϣ
	int number;					  //������
	char judge;					  //�Ƿ������������ڴ�
	char recoveryflag = 0;		  //�Ƿ���ձ�־(�ռ�δ���������£������л���)
	bool flag = 0;				  //�ڴ�����Ƿ�ɹ���־
	int sort_mode = 2;			  //Ĭ���۰��������
	//��ʼ��˫������
	LinkedList *L = new LinkedList();
	cout << "��ʼ��������������������ݣ��뵽data.txt���޸ģ�" << endl;
	L->init();
	L->Traverse(print);
	//TODO
	while (1)
	{
		do
		{
			cout << "1.�״�����	2.ѭ���״�	3.�������	4.�������" << endl;
			cout << "����Ҫ���еĲ�����ţ�";
			cin >> number;
		} while (!(number > 0 && number < 5));
		switch (number)
		{
		case 1:
			flag = first(L, cache);
			break;
		case 2:
			flag = loopfirst(L, cache);
			break;
		case 3:
			cout << "�����������㷨[1: ֱ�Ӳ�������  2: �۰��������(�Ƽ�)  3: ��������]" << endl;
			cin >> sort_mode;
			flag = best(L, cache, sort_mode);
			break;
		case 4:
			flag = worst(L, cache);
			break;
		}
		if (flag)
		{
			cout << "�����ַΪ��" << cache[0].back() << endl;
			L->Traverse(print);
			recoveryflag = 1;
		}
		else
			cout << "�������ռ����" << endl
				 << endl;

		cout << "�Ƿ���������ڴ�(y/n)" << endl;
		cin >> judge;
		if (judge == 'n')
			break;
	}
	if (recoveryflag)
	{
		//ʹ���ѷ����ڴ�
		doSomething();
		//����
		recovery(L, cache);
		L->Traverse(print);
	}
	else
		cout << "�ռ�δ���䣬�������" << endl;
	system("pause");
	return 0;
}
