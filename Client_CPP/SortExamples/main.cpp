#include <iostream>
#include "Sortexamples.h"

int main() {
	
	int arr1[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "�����Ʈ����" << arr1 << std::endl;
	Sortexamples::BubbleSort(arr1, 10);
	
	int arr2[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "�����Ǽ�Ʈ����" << arr2 << std::endl;
	Sortexamples::SelectionSort(arr2, 10);


	int arr3[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "�μ�Ʈ��Ʈ����" << arr3 << std::endl;
	Sortexamples::InsertionSort(arr3, 10);

	return 0;
}