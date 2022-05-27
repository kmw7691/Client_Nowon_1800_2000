#include <iostream>
#include "Sortexamples.h"

int main() {
	
	int arr1[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "�����Ʈ����" << arr1 << std::endl;
	Sortexamples::BubbleSort(arr1, 10);
	

	// ������ ��Ʈ�� �����Ʈ���� �Ϲ������� ������
	// �Ѵ� 1/2 * N^2 �� �ð��� �ɸ����� ������ �� Ƚ����
	// ������ ��Ʈ�� ���� ����
	int arr2[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "�����Ǽ�Ʈ����" << arr2 << std::endl;
	Sortexamples::SelectionSort(arr2, 10);


	int arr3[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "�μ�Ʈ��Ʈ����" << arr3 << std::endl;
	Sortexamples::InsertionSort(arr3, 10);

	int const mergeSortArrayCount = 1;
	int arr4[mergeSortArrayCount] = { 1 };
	std::cout << "���� ��Ʈ����" << arr4 << std::endl;
	Sortexamples::MergeSort(arr4, 0, mergeSortArrayCount - 1);

	for (int i = 0; i < mergeSortArrayCount - 1; i++)
	{
		std::cout << arr4[i];
	}

	return 0;
}