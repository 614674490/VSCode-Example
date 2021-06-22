/*
 * @Author: Ken Kaneki
 * @Date: 2020-06-01 23:39:45
 * @LastEditTime: 2020-06-12 11:17:47
 * @Description: README
 * @FilePath: \DynamicPartition_V1.0\source\algorithm.cpp
 */
#include "algorithm.h"
bool first(LinkedList *S, vector<vector<int>> &cache)
{
	int n = 1;	  //�ӵ�һ����ʼ
	int dataSize; //��С
	int cinSize;  //����Ĵ�С
	int newSize;  //�µ�ַ�ʹ�С
	cout << "��С:";
	cin >> cinSize;
	while (n <= S->elementTotal())
	{
		dataSize = S->getdatasize(n); //�ҵ���һ�����ʴ�С�ķ���
		if (cinSize <= dataSize)
			break;
		n++;
	}
	if (n > S->elementTotal()) //�Ҳ��������ʧ��
		return 0;
	cout << endl
		 << "����Ҫ��ķ�����Ϣ��" << endl
		 << "�����ţ�" << S->getdataorder(n) << "\t";
	cout << "��ַ��" << S->getdataaddress(n) << "\t";
	cout << "�ɴ�С��" << S->getdatasize(n) << endl;

	newSize = S->getdatasize(n) - cinSize; //���·�����С

	cout << endl
		 << "�����´�С��" << newSize << endl;
	S->alterElement(newSize, n); //��������
	//��ջ�洢��ʷ��Ϣ������֮����л���
	cache[0].push_back(S->getdataaddress(n) + newSize); //�����������ʼ��ַ
	cache[1].push_back(cinSize);						//��������Ĵ�С
	return 1;
}

bool loopfirst(LinkedList *S, vector<vector<int>> &cache)
{
	int n = S->loop; //���ڹ��б���loop������¼ָ��λ�ã�Ĭ��Ϊ1
	int dataSize;	 //��С
	int cinSize;	 //����Ĵ�С
	int newSize;	 //�´�С
	cout << "��С:";
	cin >> cinSize;
	while (1)
	{
		if (n > S->elementTotal())
			n = 1;
		dataSize = S->getdatasize(n);
		if (cinSize <= dataSize)
			break;
		n++;
		if (n == S->loop)
			return 0;
	}
	S->loop = n;
	newSize = S->getdatasize(n) - cinSize;

	cout << endl
		 << "����Ҫ��ķ�����Ϣ��" << endl
		 << "�����ţ�" << S->getdataorder(n) << "\t";
	cout << "��ַ��" << S->getdataaddress(n) << "\t";
	cout << "�ɴ�С��" << S->getdatasize(n) << endl;

	S->alterElement(newSize, n);
	cout << endl
		 << "�����´�С��" << newSize << endl;

	cache[0].push_back(S->getdataaddress(n) + newSize);
	cache[1].push_back(cinSize);
	return 1;
}

bool best(LinkedList *S, vector<vector<int>> &cache, int mode)
{
	S->ascendingSort(1, mode);
	return first(S, cache);
}

bool worst(LinkedList *S, vector<vector<int>> &cache)
{
	S->InsertSort(1);
	int newSize;
	int n = S->elementTotal();
	int cinSize; //����Ĵ�С
	cout << "��С:";
	cin >> cinSize;

	if (cinSize > S->getdatasize(n))
		return 0;

	cout << endl
		 << "����Ҫ��ķ�����Ϣ��" << endl
		 << "�����ţ�" << S->getdataorder(n) << "\t";
	cout << "��ַ��" << S->getdataaddress(n) << "\t";
	cout << "�ɴ�С��" << S->getdatasize(n) << endl;

	newSize = S->getdatasize(n) - cinSize;

	cout << endl
		 << "�����´�С��" << newSize << endl;
	S->alterElement(newSize, n);
	cache[0].push_back(S->getdataaddress(n) + newSize);
	cache[1].push_back(cinSize);
	return 1;
}
void recovery(LinkedList *L, vector<vector<int>> &cache)
{
	srand((int)time(0));
	int pos = -1;
	int printpos = -1;
	int address = -1;
	int size = -1;
	while (cache[0].size())
	{
		//ʹ�������ģ�����ʹ�����˳��
		pos = rand() % cache[0].size();
		address = cache[0][pos];
		size = cache[1][pos];
		cout << "��ַ��" << address << "\t"
			 << "��С��" << size << "\t�÷�����ʹ���꣬���л���" << endl
			 << endl;
		int i = 1;
		//�鿴�Ƿ������ڿ��з���
		for (; i <= L->elementTotal(); ++i)
		{
			if (address == (L->getdataaddress(i) + L->getdatasize(i)))
			{
				size += L->getdatasize(i);
				L->alterElement(size, i);
				break;
			}
		}
		//�����ڿ��з�������������
		if (i == L->elementTotal() + 1)
			L->addToLast(*(new Partition(0, address, size)));
		cache[0].erase(cache[0].begin() + pos);
		cache[1].erase(cache[1].begin() + pos);
	}
	//��Ƭ�������Խ�����Ƭ�ϲ�
	L->partitionMerge();
}
