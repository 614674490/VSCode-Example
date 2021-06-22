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
	char ProcessName[10]; //进程名
	int TrackNumber;	  //磁道号
} processAccess;

processAccess DiskAccess[100];
int main()
{
	int ProcessNumber;
	int CorrentTrackNumber;

	int TrackLength;	 //磁道长度
	int TotalLength = 0; //累计长度
	float AverageLength; //平均寻道长度
	int k;
	int i, j, m;
	cout << "输入访问磁盘进程个数:";
	cin >> ProcessNumber;
	k = ProcessNumber;
	cout << "请输入进程名称和其访问的磁道号：\n";
	for (int i = 0; i < ProcessNumber; i++)
	{
		cin >> DiskAccess[i].ProcessName >> DiskAccess[i].TrackNumber;
	}
	cout << "输入当前磁头所在磁道号：\n";
	cin >> CorrentTrackNumber;
	cout << "调度次序为：\n";
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
		CorrentTrackNumber = DiskAccess[k - 1].TrackNumber; //更换磁道号
		cout << DiskAccess[k - 1].ProcessName << ": " << DiskAccess[k - 1].TrackNumber << "移动距离" << TrackLength << "\n";
		k--;
	}
	AverageLength = TotalLength / ProcessNumber;
	cout << "平均寻道长度：" << AverageLength << "\n";
	system("pause");
	return 0;
}
