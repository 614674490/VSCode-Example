#include "Linkedlist.h"
#include <fstream>

/***************************************
*��������г�ʼ��
*��data.txt��ȡ����
****************************************/
void LinkedList::init()
{
	int n;
	int order, address, size;
	ifstream f("data.txt"); //Ĭ���� ios::in �ķ�ʽ���ļ����ļ�������ʱ����ʧ��
	if (!f.good())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	f >> n; //��һ��Ϊ������
	n += 1;
	//����¼��5������
	while (--n)
	{
		f >> order >> address >> size;
		addToLast(*(new Partition(order, address, size))); //β�巨
	}
	f.close();
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
void LinkedList::insertElement(const Partition &element, int position)
{
	assert(position > 0 && position <= elementTotal() + 1); //��������������ش�������ֹ����ִ��
	Node *p = head;
	//��λ
	while (position)
	{
		p = p->next;
		position--;
	}
	//��ʱpָ��Ҫ����Ľ��
	Node *pNew = new Node(element, p->prior, p);
	p->prior = p->prior->next = pNew;
}
/***************************************
*�����ҵ���Ԫ�صĸ���
***************************************/
Partition LinkedList::getElement(int index) const
{
	assert(index > 0 && index <= elementTotal() && !isEmpty()); //λ�������Ƿ�Ϸ�,�����Ƿ��
	Node *p = head->next;
	while (--index)
		p = p->next;
	return p->data;
}
/****************************************
*��Newelement��������Ϊindex��Ԫ��->�޸ķ�����С
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
void LinkedList::Traverse(void (*visit)(Partition element))
{
	if (isEmpty())
		cout << "����Ϊ��" << endl;
	Node *p = head->next;
	cout << "---------------"
		 << "���з���������Ϣ"
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
* ʵ�ֶ��������������
* n-> size / address ; m-> insertsort
*/
void LinkedList::ascendingSort(int n, int m)
{
	switch (m)
	{
	case 1:
		cout << "<ֱ�Ӳ�������>" << endl;
		InsertSort(n);
		break;
	case 2:
		cout << "<�۰��������>" << endl;
		BInsertSort(n);
		break;
	case 3:
		cout << "<��������>" << endl;
		QSort(n);
		break;
	default:
		cout << "<����ģʽ�����Զ�תΪ�۰��������!>" << endl;
	}
}

/***************************************
*ֱ�Ӳ�������
*****************************************/
void LinkedList::InsertSort(int n)
{
	LinkedList m; //�������֮�������
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
 * �۰��������(Ĭ������)
 */
void LinkedList::BInsertSort(int n)
{
	int i, j;
	int low, high, mid;
	LinkedList S = *this;
	for (i = 2; i <= S.elementTotal(); i++)
	{
		S[0] = S[i]; //���Ƶ�������
		low = 1, high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (n ? S[0].getsize() < S[mid].getsize() : S[0].getaddress() < S[mid].getaddress())
				high = mid - 1; //������ڵͰ���
			else
				low = mid + 1; //������ڸ߰���
		}
		for (j = i - 1; j >= high + 1; j--) //��¼����
			S[j + 1] = S[j];
		S[high + 1] = S[0]; //����
	}
}
/**
 * �����������㷨1
 */
int QSort1(LinkedList S, int low, int high, int n)
{
	int pivotkey;
	if (n)
		pivotkey = S[low].getsize();
	else
		pivotkey = S[low].getaddress();
	S[0] = S[low];	   //�ݴ������¼
	while (low < high) //�ӱ�����˽������м�ɨ��
	{
		while (low < high && (n ? S[high].getsize() : S[high].getaddress()) >= pivotkey)
			high--;
		S[low] = S[high]; //���������¼С�ļ�¼�Ƶ��Ͷ�
		while (low < high && (n ? S[low].getsize() : S[low].getaddress()) <= pivotkey)
			low++;
		S[high] = S[low]; //���������¼��ļ�¼�Ƶ��߶�
	}
	S[low] = S[0];
	return low;
}
/**
 * �����������㷨2
 */
void QSort2(LinkedList S, int low, int high, int n)
{
	int pivotc;
	if (low < high)
	{
		pivotc = QSort1(S, low, high, n); //���ݹ��ӱ�ֳ�������
		QSort2(S, low, pivotc - 1, n);	  //����
		QSort2(S, pivotc + 1, high, n);	  //����
	}
}
/*
* ���������㷨
*/
void LinkedList::QSort(int n)
{
	QSort2(*this, 1, (*this).elementTotal(), n);
}
/**************************************************
*���������Ԫ�����ã����ɶ�д.ʵ��������û��[]�����ϵ����й���
*���[]�����������Ƶ�.��������Ϊ�˿ͻ��˴����࣬��Ϊ�������д
*��������õ�
***************************************************/
Partition &LinkedList::operator[](int index)
{
	if (index == 0)
		return head->data;
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
/***************************
*���Խ����з�����������Ƭ�ϲ�
***************************/
void LinkedList::partitionMerge()
{
	int address;
	if (isEmpty())
		cout << "����Ϊ��" << endl;
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
