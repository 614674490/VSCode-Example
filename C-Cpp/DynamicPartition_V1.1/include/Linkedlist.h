#pragma once
#ifndef LINKEDLIST_H //���û�ж��������
#define LINKEDLIST_H //���������
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
//������-�������
class Partition
{
private:
	int order;	 //������
	int address; //��ַ
	int size;	 //��С
public:
	//Ĭ�Ϲ��캯��
	Partition()
	{
		order = -1;
		address = -1;
		size = -1;
	}
	//���캯��
	Partition(int order, int address, int size)
	{
		this->order = order;
		this->address = address;
		this->size = size;
	}
	//��ȡ˽�г�Ա����
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
	//����'='
	Partition operator=(const Partition &p)
	{
		this->order = p.order;
		this->address = p.address;
		this->size = p.size;
		return *this;
	}
	//����<<�������أ�����<<��ֱ���������������Ϣ
	friend ostream &operator<<(ostream &os, const Partition &c)
	{
		os << "������:" << setw(3) << c.order << "\t"; //�����ֵ���Ϊ3���ո�
		os << "��ַ:" << setw(3) << c.address << "\t";
		os << "��С:" << setw(3) << c.size << "\t";
		return os;
	}
};
//˫��ѭ������
class LinkedList
{
private:
	class Node
	{
	public:
		Partition data; //������,������Ϊ����
		Node *prior;	//ָ��ǰһ�����
		bool priorflag;
		Node *next; //ָ����һ�����
		bool nextflag;
		//�ù��캯���Ĳ����б���ʽ��ʼ����Ա
		Node(const Partition &element, Node *&pri, Node *&nt) : data(element), next(nt), prior(pri), priorflag(1), nextflag(1) {}
		Node() : data(data) {}
	};
	Node *head; //ָ���һ�����(ͷ�ڵ�)
public:
	int loop; //����ѭ����Ӧ�㷨->λ��ָ��
	//��ʼ��������һ���ս�㣬�����
	LinkedList() : head(new Node()), loop(1)
	{
		head->prior = head->next = head;
	}
	//��ʼ��
	void init();
	//��ȡԪ������
	int elementTotal() const; //const->��ֹ�޸����Ա
	//�ж��Ƿ�Ϊ����
	bool isEmpty() const
	{
		return head == head->next ? true : false;
	}
	//��Ԫ����������ע��node��ָ������
	void addToLast(const Partition &element)
	{
		Node *ne = new Node(element, head->prior, head);
		head->prior = head->prior->next = ne;
	}
	//��ȡ�������������š���ַ�ʹ�С
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
	void insertElement(const Partition &element, int position);
	//��ȡԪ��
	Partition getElement(int index) const;
	//�޸�Ԫ��
	void alterElement(const int Newelement, int index);
	//�������
	void Traverse(void (*visit)(Partition element));
	//����
	void ascendingSort(int n, int m); //��������
	void InsertSort(int n);			  //ֱ�Ӳ�������
	void BInsertSort(int n);		  //�۰��������
	void QSort(int n);				  //��������
	//����[]����
	Partition &
	operator[](int index);
	//�������
	void clearAllElement();
	//�����ϲ�
	void partitionMerge();
};
#endif
