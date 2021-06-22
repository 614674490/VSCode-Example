#pragma once
#ifndef LINKEDLIST_H //如果没有定义这个宏
#define LINKEDLIST_H //定义这个宏
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
//分区类-结点数据
class Partition
{
private:
	int order;	 //物理块号
	int address; //地址
	int size;	 //大小
public:
	//默认构造函数
	Partition()
	{
		order = -1;
		address = -1;
		size = -1;
	}
	//构造函数
	Partition(int order, int address, int size)
	{
		this->order = order;
		this->address = address;
		this->size = size;
	}
	//读取私有成员变量
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
		size = n;
	}
	//重载'='
	Partition operator=(const Partition &p)
	{
		this->order = p.order;
		this->address = p.address;
		this->size = p.size;
		return *this;
	}
	//用于<<操作重载，重载<<，直接输出单个分区信息
	friend ostream &operator<<(ostream &os, const Partition &c)
	{
		os << "物理块号:" << setw(3) << c.order << "\t"; //对象和值间隔为3个空格
		os << "地址:" << setw(3) << c.address << "\t";
		os << "大小:" << setw(3) << c.size << "\t";
		return os;
	}
};
//双向循环链表
class LinkedList
{
private:
	class Node
	{
	public:
		Partition data; //数据域,假设其为分区
		Node *prior;	//指向前一个结点
		bool priorflag;
		Node *next; //指向下一个结点
		bool nextflag;
		//用构造函数的参数列表形式初始化成员
		Node(const Partition &element, Node *&pri, Node *&nt) : data(element), next(nt), prior(pri), priorflag(1), nextflag(1) {}
		Node() : data(data) {}
	};
	Node *head; //指向第一个结点(头节点)
public:
	int loop; //用于循环适应算法->位置指针
	//初始化：构造一个空结点，搭建空链
	LinkedList() : head(new Node()), loop(1)
	{
		head->prior = head->next = head;
	}
	//初始化
	void init();
	//获取元素总数
	int elementTotal() const; //const->防止修改类成员
	//判断是否为空链
	bool isEmpty() const
	{
		return head == head->next ? true : false;
	}
	//将元素添加至最后，注意node的指针设置
	void addToLast(const Partition &element)
	{
		Node *ne = new Node(element, head->prior, head);
		head->prior = head->prior->next = ne;
	}
	//获取结点分区的物理块号、地址和大小
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
	void insertElement(const Partition &element, int position);
	//获取元素
	Partition getElement(int index) const;
	//修改元素
	void alterElement(const int Newelement, int index);
	//正序遍历
	void Traverse(void (*visit)(Partition element));
	//排序
	void ascendingSort(int n, int m); //升序排序
	void InsertSort(int n);			  //直接插入排序
	void BInsertSort(int n);		  //折半插入排序
	void QSort(int n);				  //快速排序
	//重载[]函数
	Partition &
	operator[](int index);
	//清空链表
	void clearAllElement();
	//分区合并
	void partitionMerge();
};
#endif
