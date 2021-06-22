LinkedList.h	空闲链表有关定义及操作
algorithm.h	分配、回收算法实现
##############partition类->分区空间####################
//字段意义
int order;		//序号
int address;	//地址
int size;		//空间大小

//获取order、address、size
int getorder(int n)
int getaddress(int n)
int getsize(int n)

//重写了<<运算符
example：
partition p;
cout<<p;
控制台输出：
序号：XXX 地址：XXX 大小：XXX


###############LinkedList类方法######################
//获取链表长度
int elementToatal()

//重载[ ]
//可以通过下标直接访问,类似数组
example：
LinkedList *L = new LinkedList();
（*L）[1]返回链表中第一个partition的引用

//n从1开始
//获取order、address、size
int getdataorder(int n)
int getdataaddress(int n)
int getdatasize(int n)

//index从1开始
//修改index位置partition.size值为Newelement
alterElement(const int Newelement,int index)

