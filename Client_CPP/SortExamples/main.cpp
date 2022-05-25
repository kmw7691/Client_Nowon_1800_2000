#include <iostream>
#include "Sortexamples.h"

int main() {
	
	int arr1[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "버블소트시작" << arr1 << std::endl;
	Sortexamples::BubbleSort(arr1, 10);
	
	int arr2[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "셀렉션소트시작" << arr2 << std::endl;
	Sortexamples::SelectionSort(arr2, 10);


	int arr3[10] = { 3,6,7,4,2,1,5,9,8,0 };
	std::cout << "인설트소트시작" << arr3 << std::endl;
	Sortexamples::InsertionSort(arr3, 10);

	return 0;
}