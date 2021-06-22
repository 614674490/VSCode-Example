/*
 * @Author: Ken Kaneki
 * @Date: 2020-04-08 13:28:49
 * @LastEditTime: 2020-05-21 15:33:40
 * @Description: README
 */
#include "string.h"
#include <iomanip>
#include <iostream>
using namespace std;

typedef struct Page
{
    char operate[5];
    int pageId;   //页号
    int pageAddr; //页地址
} page;
page p[20];
typedef struct PageTab
{
    char memoryFlag; //主存存在标识 0:未分配主存块 1: 分配主存块
    int blockId;     //所在主存块号
    char isModify;   //是否修改
    int diskPos;     //磁盘位置
} pageTab;
pageTab t[7] =
    {                        //页号
        {'0', -1, '0', 020}, //0
        {'1', 6, '0', 022},  //1
        {'1', 7, '0', 024},  //2
        {'1', 2, '0', 033},  //3
        {'0', -1, '0', 036}, //4
        {'0', -1, '0', 040}, //5
        {'1', 0, '0', 150}}; //6
int main()
{
    int TotalPages;                     //程序页面总数 指令序列长度
    int AddressOfMemory;                //用于计算主存地址
    int ExchangePage;                   //置换出的页面
    int MemoryAdress = 0;               //分配给4个主存块，与MemoryBlocks[]合用
    int PageNumber;                     //页号
    int MemoryBlocks[4] = {1, 2, 3, 6}; //用数组表示分配给的4个主存块，1 2 3 6依次是6 7 2 0
    int pagenum[50];                    //调用页面号,最多50个页面
    int blockpage[50][4];               //存储主存块(6 7 2 0)映射的页号
    int blocktemp[50] = {6, 7, 2, 0};
    float pageFaultRate = 0; //缺页率
    int i, j;
    cout << "请输入程序调用页面总数 :\n";
    cin >> TotalPages;
    cout << "请输入程序调用页面信息（操作 页号 页内地址）:\n";
    for (int i = 0; i < TotalPages; i++) //将页面访问序列录入
    {
        cin >> p[i].operate >> p[i].pageId >> p[i].pageAddr;
        pagenum[i] = p[i].pageId;
    }
    for (int i = 0; i < TotalPages; i++) //执行指令
    {
        PageNumber = p[i].pageId;            //获取指令所在的页号
        if (t[PageNumber].memoryFlag == '1') //该页已分配主存块
        {
            AddressOfMemory = 1024 * t[PageNumber].blockId + p[i].pageAddr; //物理地址=块起始地址+页地址
            if (strcmp(p[i].operate, "save") == 0)
            {
                t[PageNumber].isModify = '1';
            }
            cout << "程序页面" << PageNumber << "已加载入主存块" << t[PageNumber].blockId << ";\t其主存地址为:" << AddressOfMemory << ";\n";
            for (int j = 0; j < 4; j++) //存储此时页面信息
            {
                blockpage[i][j] = -1;
            }
        }
        else //未分配主存，按照先进先出原则进行置换
        {
            pageFaultRate++; //先计算缺页次数
            cout << "调入页面" << PageNumber << "置换";
            ExchangePage = MemoryBlocks[MemoryAdress]; //查看当前首元素
            if (t[ExchangePage].isModify == '1')
            { //对于之前修改的内容,将其放回磁盘(辅存块)进行备份
                cout << ExchangePage << ";\t页面已经被修改,写回辅存块" << t[ExchangePage].diskPos << ";\t调入页面的主存地址";
            }
            else //置换对象没有内容，无需备份
            {
                cout << ExchangePage;
            }
            MemoryBlocks[MemoryAdress] = PageNumber; //置换当前首元素
            MemoryAdress = (MemoryAdress + 1) % 4;
            t[PageNumber].blockId = t[ExchangePage].blockId;
            t[PageNumber].memoryFlag = '1';

            t[ExchangePage].memoryFlag = '0';
            t[ExchangePage].blockId = -1;
            AddressOfMemory = 1024 * t[PageNumber].blockId + p[i].pageAddr; //物理地址=块起始地址+页地址
            cout << ";\t调入主存块" << t[PageNumber].blockId << ";\t页面的主存地址" << AddressOfMemory << ";\n";
            for (int j = 0; j < 4; j++) //存储此时页面信息
            {
                blockpage[i][j] = MemoryBlocks[j];
            }
        }
    }
    pageFaultRate = pageFaultRate / TotalPages;
    //打印输出页面置换过程并计算缺页率
    cout << "页面置换过程:" << endl;
    cout << " \\ ";
    for (int i = 0; i < TotalPages - 1; i++)
    {
        cout << pagenum[i] << "  ";
    }
    cout << pagenum[i] << endl;
    for (i = 0; i < 4; i++)
    {
        cout << blocktemp[i] << "  ";
        for (j = 0; j < TotalPages - 1; j++)
        {
            if (blockpage[j][i] >= 0)
                cout << blockpage[j][i] << "  ";
            else
                cout << "   ";
        }
        if (blockpage[j][i] >= 0)
            cout << blockpage[j][i] << endl;
        else
            cout << " " << endl;
    }
    cout << "缺页率: " << pageFaultRate * 100 << '%' << endl;
    system("pause");
    return 0;
}
