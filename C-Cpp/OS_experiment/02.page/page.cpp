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
    int pageId;   //ҳ��
    int pageAddr; //ҳ��ַ
} page;
page p[20];
typedef struct PageTab
{
    char memoryFlag; //������ڱ�ʶ 0:δ��������� 1: ���������
    int blockId;     //����������
    char isModify;   //�Ƿ��޸�
    int diskPos;     //����λ��
} pageTab;
pageTab t[7] =
    {                        //ҳ��
        {'0', -1, '0', 020}, //0
        {'1', 6, '0', 022},  //1
        {'1', 7, '0', 024},  //2
        {'1', 2, '0', 033},  //3
        {'0', -1, '0', 036}, //4
        {'0', -1, '0', 040}, //5
        {'1', 0, '0', 150}}; //6
int main()
{
    int TotalPages;                     //����ҳ������ ָ�����г���
    int AddressOfMemory;                //���ڼ��������ַ
    int ExchangePage;                   //�û�����ҳ��
    int MemoryAdress = 0;               //�����4������飬��MemoryBlocks[]����
    int PageNumber;                     //ҳ��
    int MemoryBlocks[4] = {1, 2, 3, 6}; //�������ʾ�������4������飬1 2 3 6������6 7 2 0
    int pagenum[50];                    //����ҳ���,���50��ҳ��
    int blockpage[50][4];               //�洢�����(6 7 2 0)ӳ���ҳ��
    int blocktemp[50] = {6, 7, 2, 0};
    float pageFaultRate = 0; //ȱҳ��
    int i, j;
    cout << "������������ҳ������ :\n";
    cin >> TotalPages;
    cout << "������������ҳ����Ϣ������ ҳ�� ҳ�ڵ�ַ��:\n";
    for (int i = 0; i < TotalPages; i++) //��ҳ���������¼��
    {
        cin >> p[i].operate >> p[i].pageId >> p[i].pageAddr;
        pagenum[i] = p[i].pageId;
    }
    for (int i = 0; i < TotalPages; i++) //ִ��ָ��
    {
        PageNumber = p[i].pageId;            //��ȡָ�����ڵ�ҳ��
        if (t[PageNumber].memoryFlag == '1') //��ҳ�ѷ��������
        {
            AddressOfMemory = 1024 * t[PageNumber].blockId + p[i].pageAddr; //�����ַ=����ʼ��ַ+ҳ��ַ
            if (strcmp(p[i].operate, "save") == 0)
            {
                t[PageNumber].isModify = '1';
            }
            cout << "����ҳ��" << PageNumber << "�Ѽ����������" << t[PageNumber].blockId << ";\t�������ַΪ:" << AddressOfMemory << ";\n";
            for (int j = 0; j < 4; j++) //�洢��ʱҳ����Ϣ
            {
                blockpage[i][j] = -1;
            }
        }
        else //δ�������棬�����Ƚ��ȳ�ԭ������û�
        {
            pageFaultRate++; //�ȼ���ȱҳ����
            cout << "����ҳ��" << PageNumber << "�û�";
            ExchangePage = MemoryBlocks[MemoryAdress]; //�鿴��ǰ��Ԫ��
            if (t[ExchangePage].isModify == '1')
            { //����֮ǰ�޸ĵ�����,����Żش���(�����)���б���
                cout << ExchangePage << ";\tҳ���Ѿ����޸�,д�ظ����" << t[ExchangePage].diskPos << ";\t����ҳ��������ַ";
            }
            else //�û�����û�����ݣ����豸��
            {
                cout << ExchangePage;
            }
            MemoryBlocks[MemoryAdress] = PageNumber; //�û���ǰ��Ԫ��
            MemoryAdress = (MemoryAdress + 1) % 4;
            t[PageNumber].blockId = t[ExchangePage].blockId;
            t[PageNumber].memoryFlag = '1';

            t[ExchangePage].memoryFlag = '0';
            t[ExchangePage].blockId = -1;
            AddressOfMemory = 1024 * t[PageNumber].blockId + p[i].pageAddr; //�����ַ=����ʼ��ַ+ҳ��ַ
            cout << ";\t���������" << t[PageNumber].blockId << ";\tҳ��������ַ" << AddressOfMemory << ";\n";
            for (int j = 0; j < 4; j++) //�洢��ʱҳ����Ϣ
            {
                blockpage[i][j] = MemoryBlocks[j];
            }
        }
    }
    pageFaultRate = pageFaultRate / TotalPages;
    //��ӡ���ҳ���û����̲�����ȱҳ��
    cout << "ҳ���û�����:" << endl;
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
    cout << "ȱҳ��: " << pageFaultRate * 100 << '%' << endl;
    system("pause");
    return 0;
}
