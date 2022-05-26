#include "Sortexamples.h"
#include <iostream>
using namespace std;

void Sortexamples::BubbleSort(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		// 이미 정렬된 친구들은 할필요 없으므로 length -i -1 까지 순화
		for (int j = 0; j < length - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				// 스왑
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;

				// 스왑결과출력
				cout << "스왑됨";
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

		// 스왑
		int tmp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = tmp;


		// 스왑결과출력
		cout << "스왑됨";
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

		cout << "스왑됨";
		for (int k = 0;k < length;k++)
		{
			cout << arr[k] << ",";
		}
		cout << endl;
	}
}

void Sortexamples::Merge(int arr[], int start, int end, int mid)
{
	int* tmp = new int[end + 1];

	for (int i = start; i <= end; i++)
	{
		tmp[i] = arr[i];
	}

	int part1 = start;
	int part2 = mid + 1;
	int index = start;

	while (part1 <= mid &&
		part2 <= end)
	{
		if (tmp[part1] <= tmp[part2])
		{
			arr[index++] = tmp[part1++];
		}

		else
		{
			arr[index++] = tmp[part2++];
		}
	}

	for (int i = 0; i < mid - part1; i++)
	{

	}
}

void Sortexamples::MergeSort(int arr[], int start, int end)
{
	if (start < end) {
		int mid = start + (end - 1) / 2;

		MergeSort(arr, start, mid);
		MergeSort(arr, mid + 1, end);

		Merge(arr, start, end, mid);
	}
}
