#include "Sortexamples.h"
#include <iostream>
using namespace std;

void Sortexamples::BubbleSort(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		// �̹� ���ĵ� ģ������ ���ʿ� �����Ƿ� length -i -1 ���� ��ȭ
		for (int j = 0; j < length - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				// ����
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;

				// ���Ұ�����
				cout << "���ҵ�";
				for (int k = 0;k < length;k++)
				{
					cout << arr[k] << ",";
				}
				cout << endl;
			}
		}
	}
}

void Sortexamples::SelectionSort(int arr[], int length)
{
	int minIdx = 0;
	for (int i = 0; i < length; i++)
	{
		minIdx = i;
		for (int j = i + 1; j < length - 1; j++)
		{
			if (arr[j] < arr[minIdx])
				minIdx = j;
		}

		// ����
		int tmp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = tmp;


		// ���Ұ�����
		cout << "���ҵ�";
		for (int k = 0;k < length;k++)
		{
			cout << arr[k] << ",";
		}
		cout << endl;
	}
}

void Sortexamples::InsertionSort(int arr[], int length)
{
	int key = 0, j = 0;
	for (int i = 0; i < length; i++)
	{
		key = arr[i];
		j = i - 1;
		while (arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;

		cout << "���ҵ�";
		for (int k = 0;k < length;k++)
		{
			cout << arr[k] << ",";
		}
		cout << endl;
	}
}
