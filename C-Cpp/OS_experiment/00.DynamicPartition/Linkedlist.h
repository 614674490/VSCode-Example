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
		os << "��ţ�" << c.order << "\t��ַ��" << c.address << "\t��С��" << c.size;
		return os;
	}
};

class LinkedList
{
private:
	class Node
	{
	public:
		partition data; //������,������Ϊ����
		Node *prior;	//ָ��ǰһ�����
		bool priorflag;
		Node *next; //ָ����һ�����
		bool nextflag;

		Node(const partition &element, Node *&pri, Node *&nt) : data(element), next(nt), prior(pri), priorflag(0), nextflag(0) {}
		Node() : data(data) {}
	};
	Node *head; //ָ���һ�����
public:
	//��ʼ��������һ���ս�㣬�����
	LinkedList() : head(new Node())
	{
		head->prior = head->next = head;
	}
	//��ʼ��
	void init();
	//��ȡԪ������
	int elementTotal() const;
	//�ж��Ƿ�Ϊ����
	bool isEmpty() const
	{
		return head == head->next ? true : false;
	}
	//��Ԫ����������ע��node��ָ������
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
	//����Ԫ��
	void insertElement(const partition &element, int position);
	//
	int findElement(const int order) const;
	//��ȡԪ��
	partition getElement(int index) const;
	//�޸�Ԫ��
	void alterElement(const int Newelement, int index);
	//�������
	void Traverse(void (*visit)(partition &element));
	//����[]����
	partition &operator[](int index);
	//�������
	void clearAllElement();
	//��������
	~LinkedList();
};
/***************************************
*��������г�ʼ��
*��data.txt��ȡ����
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
*����Ԫ������
****************************************/
int LinkedList::elementTotal() const
{
	int Total = 0;
	for (Node *p = head->next; p != head; p = p->next)
		++Total;
	return Total;
}
/**********************************************
*��positionָ����λ�ò���Ԫ�ء�ԭ��position�������Ԫ
*�غ���
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
	//��ʱpָ��Ҫ����Ľ��
	Node *pNew = new Node(element, p->prior, p);
	p->prior = p->prior->next = pNew;
}
/********************************
*�ҵ�����Ԫ�ص����������򷵻�0
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
*�����ҵ���Ԫ�صĸ���
***************************************/
partition LinkedList::getElement(int index) const
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //λ�������Ƿ�Ϸ�,�����Ƿ��
	Node *p = head->next;
	while (--index)
		p = p->next;
	return p->data;
}
/****************************************
*��Newelement��������Ϊindex��Ԫ��
*****************************************/
void LinkedList::alterElement(const int Newelement, int index)
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //λ�������Ƿ�Ϸ�,�����Ƿ��
	Node *p = head->next;
	while (--index)
		p = p->next;
	p->data.altersize(Newelement);
}
/***************************************
*�����������������ÿ��Ԫ����Ϊ��������visit����
*****************************************/
void LinkedList::Traverse(void (*visit)(partition &element))
{
	if (isEmpty())
		cout << "����Ϊ��" << endl;
	Node *p = head->next;
	while (p != head)
	{
		visit(p->data); //ע���ʱ�ⲿvisit������Ȩ���޸�LinkedList<T>��˽������
		p = p->next;
	}
}
/**************************************************
*���������Ԫ�����ã����ɶ�д.ʵ��������û��[]�����ϵ����й���
*���[]�����������Ƶ�.��������Ϊ�˿ͻ��˴����࣬��Ϊ�������д
*��������õ�
***************************************************/
partition &LinkedList::operator[](int index)
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //[]����ʹ��ǰ������
	Node *p = head->next;
	while (--index)
		p = p->next;
	return p->data;
}
/***************************
*�������
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
	head->prior = head->next = head; //��β����
}
