/*#include<iostream>
#include<windows.h>
using namespace std;
void insert_sort(int array[], int size)				//�������򣬰��յ���������
{
	for (int i = 1; i < size; ++i)					//iָʾ���ǵ�ǰ������Ԫ��
	{
		int key = array[i];						//key��¼��ǰ������Ԫ�ص�ֵ
		int j=i-1;								//array[0����i-1]Ϊ�Ѿ�����õ�����
		while (key < array[j] && j>=0)			//������key��Ԫ�ذ�������,����Ҫ���յݼ����У���<��Ϊ>���ɣ�
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j+1] = key;						//���뵱ǰԪ��
		
	}
}
void display(int array[], int size)
{
	for (int i = 0; i < size; ++i)
		cout << array[i] << "	";
	cout << endl;
}
int main()
{	
	const int size = 100000;
	int a[size];
	for (int i = 0; i < size; i++)
		a[i] = size - i;

	DWORD dwStart = GetTickCount();//��ȡ��ʼʱ��

	insert_sort(a,size);
	DWORD dwEnd = GetTickCount();  //��ȡ����ʱ��
	DWORD dwTimes = dwEnd - dwStart; //��������ʱ��
	cout << dwTimes << endl;
	//display(a, 0, size-1);

	system("pause");
}*/