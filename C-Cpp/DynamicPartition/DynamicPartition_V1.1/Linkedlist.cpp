#include "Linkedlist.h"
#include <fstream>

/***************************************
*对链表进行初始化
*从data.txt获取数据
****************************************/
void LinkedList::init()
{
	int n;
	int order, address, size;
	ifstream f("data.txt"); //默认以 ios::in 的方式打开文件，文件不存在时操作失败
	if (!f.good())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	f >> n; //第一行为链表长度
	n += 1;
	//连续录入5次数据
	while (--n)
	{
		f >> order >> address >> size;
		addToLast(*(new Partition(order, address, size))); //尾插法
	}
	f.close();
}
/***************************************
*返回元素总数
****************************************/
int LinkedList::elementTotal() const
{
	int Total = 0;
	for (Node *p = head->next; p != head; p = p->next)
		++Total;
	return Total;
}
/**********************************************
*在position指定的位置插入元素。原来position及后面的元
*素后移
***********************************************/
void LinkedList::insertElement(const Partition &element, int position)
{
	assert(position > 0 && position <= elementTotal() + 1); //如果它的条件返回错误，则终止程序执行
	Node *p = head;
	//定位
	while (position)
	{
		p = p->next;
		position--;
	}
	//此时p指向要插入的结点
	Node *pNew = new Node(element, p->prior, p);
	p->prior = p->prior->next = pNew;
}
/***************************************
*返回找到的元素的副本
***************************************/
Partition LinkedList::getElement(int index) const
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //位置索引是否合法,链表是否空
	Node *p = head->next;
	while (--index)
		p = p->next;
	return p->data;
}
/****************************************
*用Newelement代替索引为index的元素->修改分区大小
*****************************************/
void LinkedList::alterElement(const int Newelement, int index)
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //位置索引是否合法,链表是否空
	Node *p = head->next;
	while (--index)
		p = p->next;
	p->data.altersize(Newelement);
}
/***************************************
*正向遍历，以链表中每个元素作为参数调用visit函数
*****************************************/
void LinkedList::Traverse(void (*visit)(Partition element))
{
	if (isEmpty())
		cout << "链表为空" << endl;
	Node *p = head->next;
	cout << "---------------"
		 << "空闲分区链表信息"
		 << "----------------------" << endl
		 << endl;
	while (p != head)
	{
		visit(p->data);
		p = p->next;
	}
	cout << endl;
}
/*
* 实现对链表的升序排序
* n-> size / address ; m-> insertsort
*/
void LinkedList::ascendingSort(int n, int m)
{
	switch (m)
	{
	case 1:
		cout << "<直接插入排序>" << endl;
		InsertSort(n);
		break;
	case 2:
		cout << "<折半插入排序>" << endl;
		BInsertSort(n);
		break;
	case 3:
		cout << "<快速排序>" << endl;
		QSort(n);
		break;
	default:
		cout << "<排序模式错误，自动转为折半插入排序!>" << endl;
	}
}

/***************************************
*直接插入排序
*****************************************/
void LinkedList::InsertSort(int n)
{
	LinkedList m; //存放排序之后的链表
	LinkedList L = *this;
	int Ltemp, Mtemp;
	m.insertElement(L[1], 1);
	for (int i = 2; i <= L.elementTotal(); i++)
	{
		for (int j = 1; j <= m.elementTotal();)
		{
			if (n)
			{
				Ltemp = L[i].getsize();
				Mtemp = m[j].getsize();
			}
			else
			{
				Ltemp = L[i].getaddress();
				Mtemp = m[j].getaddress();
			}
			if (Ltemp < Mtemp)
			{
				m.insertElement(L[i], j);
				break;
			}
			j++;
			if (j == m.elementTotal() + 1)
			{
				m.insertElement(L[i], m.elementTotal() + 1);
				break;
			}
		}
	}
	*this = m;
}
/**
 * 折半插入排序(默认升序)
 */
void LinkedList::BInsertSort(int n)
{
	int i, j;
	int low, high, mid;
	LinkedList S = *this;
	for (i = 2; i <= S.elementTotal(); i++)
	{
		S[0] = S[i]; //复制到监视哨
		low = 1, high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (n ? S[0].getsize() < S[mid].getsize() : S[0].getaddress() < S[mid].getaddress())
				high = mid - 1; //插入点在低半区
			else
				low = mid + 1; //插入点在高半区
		}
		for (j = i - 1; j >= high + 1; j--) //记录后移
			S[j + 1] = S[j];
		S[high + 1] = S[0]; //插入
	}
}
/**
 * 快速排序子算法1
 */
int QSort1(LinkedList S, int low, int high, int n)
{
	int pivotkey;
	if (n)
		pivotkey = S[low].getsize();
	else
		pivotkey = S[low].getaddress();
	S[0] = S[low];	   //暂存枢轴记录
	while (low < high) //从表的两端交替向中间扫描
	{
		while (low < high && (n ? S[high].getsize() : S[high].getaddress()) >= pivotkey)
			high--;
		S[low] = S[high]; //将比枢轴记录小的记录移到低端
		while (low < high && (n ? S[low].getsize() : S[low].getaddress()) <= pivotkey)
			low++;
		S[high] = S[low]; //将比枢轴记录大的记录移到高端
	}
	S[low] = S[0];
	return low;
}
/**
 * 快速排序子算法2
 */
void QSort2(LinkedList S, int low, int high, int n)
{
	int pivotc;
	if (low < high)
	{
		pivotc = QSort1(S, low, high, n); //将递归子表分成两部分
		QSort2(S, low, pivotc - 1, n);	  //先左
		QSort2(S, pivotc + 1, high, n);	  //后右
	}
}
/*
* 快速排序算法
*/
void LinkedList::QSort(int n)
{
	QSort2(*this, 1, (*this).elementTotal(), n);
}
/**************************************************
*返回链表的元素引用，并可读写.实际上链表没有[]意义上的所有功能
*因此[]函数是有限制的.重载它是为了客户端代码简洁，因为从链表读写
*数据是最常用的
***************************************************/
Partition &LinkedList::operator[](int index)
{
	if (index == 0)
		return head->data;
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //[]函数使用前提条件
	Node *p = head->next;
	while (--index)
		p = p->next;
	return p->data;
}
/***************************
*清空链表
***************************/
void LinkedList::clearAllElement()
{
	Node *p = head->next, *pTemp = 0;
	while (p != head)
	{
		pTemp = p->next;
		delete p;
		p = pTemp;
	}
	head->prior = head->next = head; //收尾工作
}
/***************************
*尝试将空闲分区链表中碎片合并
***************************/
void LinkedList::partitionMerge()
{
	int address;
	if (isEmpty())
		cout << "链表为空" << endl;
	InsertSort(0);
	Node *p = head->next->next;
	Node *del = NULL;
	while (p != head)
	{
		address = p->prior->data.getaddress() + p->prior->data.getsize();
		if (address == p->data.getaddress())
		{
			p->prior->data.altersize(p->prior->data.getsize() + p->data.getsize());
			del = p;
			p = p->next;
			del->prior->next = del->next;
			del->next->prior = del->prior;
			delete del;
		}
		else
			p = p->next;
	}
}
