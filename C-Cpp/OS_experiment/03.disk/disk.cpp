/*
 * @Author: Ken Kaneki
 * @Date: 2020-05-19 12:50:35
 * @LastEditTime: 2020-05-25 08:28:23
 * @Description: README
 */

#include <cmath>
#include <iostream>
using namespace std;

typedef struct ProcessAccess
{
	char ProcessName[10]; //������
	int TrackNumber;	  //�ŵ���
} processAccess;

processAccess DiskAccess[100];
int main()
{
	int ProcessNumber;
	int CorrentTrackNumber;

	int TrackLength;	 //�ŵ�����
	int TotalLength = 0; //�ۼƳ���
	float AverageLength; //ƽ��Ѱ������
	int k;
	int i, j, m;
	cout << "������ʴ��̽��̸���:";
	cin >> ProcessNumber;
	k = ProcessNumber;
	cout << "������������ƺ�����ʵĴŵ��ţ�\n";
	for (int i = 0; i < ProcessNumber; i++)
	{
		cin >> DiskAccess[i].ProcessName >> DiskAccess[i].TrackNumber;
	}
	cout << "���뵱ǰ��ͷ���ڴŵ��ţ�\n";
	cin >> CorrentTrackNumber;
	cout << "���ȴ���Ϊ��\n";
	for (int p = 0; p < ProcessNumber; p++)
	{
		processAccess temp;
		for (i = 0; i < k; i++)
		{
			m = i;
			for (j = i; j < k; j++)
			{
				if (abs(DiskAccess[j].TrackNumber - CorrentTrackNumber) > abs(DiskAccess[m].TrackNumber - CorrentTrackNumber))
					m = j;
			}
			if (m != i)
			{
				temp = DiskAccess[m];
				DiskAccess[m] = DiskAccess[i];
				DiskAccess[i] = temp;
			}
		}
		TrackLength = abs(CorrentTrackNumber - DiskAccess[k - 1].TrackNumber);
		TotalLength += TrackLength;
		CorrentTrackNumber = DiskAccess[k - 1].TrackNumber; //�����ŵ���
		cout << DiskAccess[k - 1].ProcessName << ": " << DiskAccess[k - 1].TrackNumber << "�ƶ�����" << TrackLength << "\n";
		k--;
	}
	AverageLength = TotalLength / ProcessNumber;
	cout << "ƽ��Ѱ�����ȣ�" << AverageLength << "\n";
	system("pause");
	return 0;
}
