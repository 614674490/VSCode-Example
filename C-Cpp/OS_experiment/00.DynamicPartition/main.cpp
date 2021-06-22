/*
 * @Author: Ken Kaneki
 * @Date: 2020-05-25 21:33:36
 * @LastEditTime: 2020-06-01 08:49:11
 * @Description: README
 * @FilePath: \undefinedd:\VSCode\C-Cpp\OS_experiment\00.DynamicPartition\main.cpp
 */
#include "Linkedlist.h"

partition *sorttemp;

void print(partition &a)
{
	cout << a << endl;
}

int main()
{
	//初始化双向链表，不用动
	LinkedList *L = new LinkedList();
	L->init();
	sorttemp = new partition[L->elementTotal() + 1];
	L->Traverse(print);
	//TODO

	return 0;
}
