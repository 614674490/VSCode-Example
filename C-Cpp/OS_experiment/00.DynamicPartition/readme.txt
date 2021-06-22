输入数据在data.txt
排序不要直接对链表排序
       先将里面的partition全部拷贝到sorttemp，然后对其排序，最后通过序号对链表进行修改
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
//修改index位置partition.size值，size = size-Newelement
alterElement(const int Newelement,int index)

//根据order查找，返回节点位置
//位置从1开始
int findElement(const int order)
