#pragma once
#include <assert.h>
#include <iostream>
using namespace std;

class partition
{
private:
	int order;
	int address;
	int size;

public:
	partition()
	{
		order = -1;
		address = -1;
		size = -1;
	}
	partition(int order, int address, int size)
	{
		this->order = order;
		this->address = address;
		this->size = size;
	}
	int getorder()
	{
		return order;
	}
	int getaddress()
	{
		return address;
	}
	int getsize()
	{
		return size;
	}
	void altersize(int n)
	{
		if (size < n)
			return;
		size -= n;
	}
	partition operator=(const partition &p)
	{
		this->order = p.order;
		this->address = p.address;
		this->size = p.size;
		return *this;
	}
	friend ostream &operator<<(ostream &os, const partition &c)
	{
		os << "序号：" << c.order << "\t地址：" << c.address << "\t大小：" << c.size;
		return os;
	}
};

class LinkedList
{
private:
	class Node
	{
	public:
		partition data; //数据域,假设其为分区
		Node *prior;	//指向前一个结点
		bool priorflag;
		Node *next; //指向下一个结点
		bool nextflag;

		Node(const partition &element, Node *&pri, Node *&nt) : data(element), next(nt), prior(pri), priorflag(0), nextflag(0) {}
		Node() : data(data) {}
	};
	Node *head; //指向第一个结点
public:
	//初始化：构造一个空结点，搭建空链
	LinkedList() : head(new Node())
	{
		head->prior = head->next = head;
	}
	//初始化
	void init();
	//获取元素总数
	int elementTotal() const;
	//判断是否为空链
	bool isEmpty() const
	{
		return head == head->next ? true : false;
	}
	//将元素添加至最后，注意node的指针设置
	void addToLast(const partition &element)
	{
		Node *ne = new Node(element, head->prior, head);
		head->prior = head->prior->next = ne;
	}
	int getdataorder(int n)
	{
		return getElement(n).getorder();
	}
	int getdataaddress(int n)
	{
		return getElement(n).getaddress();
	}
	int getdatasize(int n)
	{
		return getElement(n).getsize();
	}
	//插入元素
	void insertElement(const partition &element, int position);
	//
	int findElement(const int order) const;
	//获取元素
	partition getElement(int index) const;
	//修改元素
	void alterElement(const int Newelement, int index);
	//正序遍历
	void Traverse(void (*visit)(partition &element));
	//重载[]函数
	partition &operator[](int index);
	//清空链表
	void clearAllElement();
	//销毁链表
	~LinkedList();
};
/***************************************
*对链表进行初始化
*从data.txt获取数据
****************************************/
void LinkedList::init()
{
	int n;
	int order, address, size;
	freopen("data.txt", "r", stdin);
	cin >> n;
	n += 1;
	while (--n)
	{
		cin >> order >> address >> size;
		addToLast(*(new partition(order, address, size)));
	}
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
void LinkedList::insertElement(const partition &element, int position)
{
	assert(position > 0 && position <= elementTotal() + 1);
	Node *p = head;
	while (position)
	{
		p = p->next;
		position--;
	}
	//此时p指向要插入的结点
	Node *pNew = new Node(element, p->prior, p);
	p->prior = p->prior->next = pNew;
}
/********************************
*找到返回元素的索引，否则返回0
********************************/
int LinkedList::findElement(const int order) const
{
	Node *p = head->next;
	int i = 0;
	while (p != head)
	{
		i++;
		if (p->data.getorder() == order)
			return i;
		p = p->next;
	}
	return 0;
}
/***************************************
*返回找到的元素的副本
***************************************/
partition LinkedList::getElement(int index) const
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //位置索引是否合法,链表是否空
	Node *p = head->next;
	while (--index)
		p = p->next;
	return p->data;
}
/****************************************
*用Newelement代替索引为index的元素
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
void LinkedList::Traverse(void (*visit)(partition &element))
{
	if (isEmpty())
		cout << "链表为空" << endl;
	Node *p = head->next;
	while (p != head)
	{
		visit(p->data); //注意此时外部visit函数有权限修改LinkedList<T>的私有数据
		p = p->next;
	}
}
/**************************************************
*返回链表的元素引用，并可读写.实际上链表没有[]意义上的所有功能
*因此[]函数是有限制的.重载它是为了客户端代码简洁，因为从链表读写
*数据是最常用的
***************************************************/
partition &LinkedList::operator[](int index)
{
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
