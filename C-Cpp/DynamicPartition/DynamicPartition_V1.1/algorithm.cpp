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
	int n = 1;	  //从第一个开始
	int dataSize; //大小
	int cinSize;  //输入的大小
	int newSize;  //新地址和大小
	cout << "大小:";
	cin >> cinSize;
	while (n <= S->elementTotal())
	{
		dataSize = S->getdatasize(n); //找到第一个合适大小的分区
		if (cinSize <= dataSize)
			break;
		n++;
	}
	if (n > S->elementTotal()) //找不到则分配失败
		return 0;
	cout << endl
		 << "符合要求的分区信息：" << endl
		 << "物理块号：" << S->getdataorder(n) << "\t";
	cout << "地址：" << S->getdataaddress(n) << "\t";
	cout << "旧大小：" << S->getdatasize(n) << endl;

	newSize = S->getdatasize(n) - cinSize; //更新分区大小

	cout << endl
		 << "分区新大小：" << newSize << endl;
	S->alterElement(newSize, n); //更改数据
	//堆栈存储历史信息，方便之后进行回收
	cache[0].push_back(S->getdataaddress(n) + newSize); //分配区域的起始地址
	cache[1].push_back(cinSize);						//分配区域的大小
	return 1;
}

bool loopfirst(LinkedList *S, vector<vector<int>> &cache)
{
	int n = S->loop; //类内公有变量loop用来记录指针位置，默认为1
	int dataSize;	 //大小
	int cinSize;	 //输入的大小
	int newSize;	 //新大小
	cout << "大小:";
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
		 << "符合要求的分区信息：" << endl
		 << "物理块号：" << S->getdataorder(n) << "\t";
	cout << "地址：" << S->getdataaddress(n) << "\t";
	cout << "旧大小：" << S->getdatasize(n) << endl;

	S->alterElement(newSize, n);
	cout << endl
		 << "分区新大小：" << newSize << endl;

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
	int cinSize; //输入的大小
	cout << "大小:";
	cin >> cinSize;

	if (cinSize > S->getdatasize(n))
		return 0;

	cout << endl
		 << "符合要求的分区信息：" << endl
		 << "物理块号：" << S->getdataorder(n) << "\t";
	cout << "地址：" << S->getdataaddress(n) << "\t";
	cout << "旧大小：" << S->getdatasize(n) << endl;

	newSize = S->getdatasize(n) - cinSize;

	cout << endl
		 << "分区新大小：" << newSize << endl;
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
		//使用随机数模拟分区使用完成顺序
		pos = rand() % cache[0].size();
		address = cache[0][pos];
		size = cache[1][pos];
		cout << "地址：" << address << "\t"
			 << "大小：" << size << "\t该分区已使用完，进行回收" << endl
			 << endl;
		int i = 1;
		//查看是否有相邻空闲分区
		for (; i <= L->elementTotal(); ++i)
		{
			if (address == (L->getdataaddress(i) + L->getdatasize(i)))
			{
				size += L->getdatasize(i);
				L->alterElement(size, i);
				break;
			}
		}
		//无相邻空闲分区，插入链表
		if (i == L->elementTotal() + 1)
			L->addToLast(*(new Partition(0, address, size)));
		cache[0].erase(cache[0].begin() + pos);
		cache[1].erase(cache[1].begin() + pos);
	}
	//碎片整理，尝试进行碎片合并
	L->partitionMerge();
}
