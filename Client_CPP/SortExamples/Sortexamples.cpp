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

void Sortexamples::Merge(int arr[], int start, int end, int mid)
{
	static int mergeCount;
	int* tmp = new int[end + 1];

	// ���� �迭 ����
	for (int i = start; i <= end; i++)
	{
		tmp[i] = arr[i];
		cout << "������..";
		mergeCount++;
	}

	int part1 = start; // ����, ���� ��Ʈ�� ���� ���� �ε����� �ʱ�ȭ
	int part2 = mid + 1; // ������, ������ ��Ʈ�� ���� ���� �ε����� �ʱ�ȭ
	int index = start; // ���� �迭 ���� ��ġ

	// ��Ʈ1�� ��Ʈ2�� ������ ������ ���� ��ȸ
	while (part1 <= mid && // ��Ʈ1�� ��Ʈ2�� ������ �Ѿ�� �ʾ��� ��
		   part2 <= end) // ��Ʈ2�� �ִ� ������ �Ѿ�� �ʾ�����
	{
		if (tmp[part1] <= tmp[part2])
		{
			arr[index++] = tmp[part1++];
			cout << "������..";
			mergeCount++;
		}

		else
		{
			arr[index++] = tmp[part2++];
			cout << "������..";
			mergeCount++;
		}
	}

	// ������ ���� part1 ���ĺ��� mid ������ ��Ҹ� ������ ������
	for (int i = 0; i < mid - part1; i++)
	{
		arr[index + i] = tmp[part1 + i];
		cout << "������..";
		mergeCount++;
	}

	for (int i = mid+1; i < end - part2; i++)
	{
		arr[index + 1] = tmp[part2 + i];
		cout << "������..";
		mergeCount++;
	}

	cout << "�����Ϸ� : (count :" << mergeCount << ")";
	for (int i = start; i <= end; i++)
	{
		cout << arr[i] << ", ";
	}
	cout << endl;


	delete[] tmp;
}

void Sortexamples::MergeSort(int arr[], int start, int end)
{
	if (start < end) {
		int mid = (start + end) / 2;

		MergeSort(arr, start, mid);
		MergeSort(arr, mid + 1, end);

		Merge(arr, start, end, mid);
	}
}
