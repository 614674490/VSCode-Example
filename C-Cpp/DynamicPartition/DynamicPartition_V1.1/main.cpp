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
		 << "已分配完成" << endl
		 << "to do something" << endl
		 << "使用完成，开始回收·····" << endl
		 << endl;
}

int main()
{
	vector<vector<int>> cache(2); //二维动态数组，储存已分配的分区信息
	int number;					  //操作数
	char judge;					  //是否继续申请分配内存
	char recoveryflag = 0;		  //是否回收标志(空间未分配的情况下，不进行回收)
	bool flag = 0;				  //内存分配是否成功标志
	int sort_mode = 2;			  //默认折半插入排序
	//初始化双向链表
	LinkedList *L = new LinkedList();
	cout << "初始化空闲链表（如需更改数据，请到data.txt中修改）" << endl;
	L->init();
	L->Traverse(print);
	//TODO
	while (1)
	{
		do
		{
			cout << "1.首次排序	2.循环首次	3.最佳排序	4.最差排序" << endl;
			cout << "输入要进行的操作序号：";
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
			cout << "请输入排序算法[1: 直接插入排序  2: 折半插入排序(推荐)  3: 快速排序]" << endl;
			cin >> sort_mode;
			flag = best(L, cache, sort_mode);
			break;
		case 4:
			flag = worst(L, cache);
			break;
		}
		if (flag)
		{
			cout << "插入地址为：" << cache[0].back() << endl;
			L->Traverse(print);
			recoveryflag = 1;
		}
		else
			cout << "申请分配空间过大" << endl
				 << endl;

		cout << "是否继续分配内存(y/n)" << endl;
		cin >> judge;
		if (judge == 'n')
			break;
	}
	if (recoveryflag)
	{
		//使用已分配内存
		doSomething();
		//回收
		recovery(L, cache);
		L->Traverse(print);
	}
	else
		cout << "空间未分配，无需回收" << endl;
	system("pause");
	return 0;
}
