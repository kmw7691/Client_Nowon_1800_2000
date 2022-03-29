#include <stdio.h>

void RefreshMaxAndMin(int* arr, int size, int** maxPtr, int** minPtr) {
	int* max,* min;
	max = min = &arr[0];

	for (int i = 0; i < size; i++)
	{
		if (*max < arr[i])
			max = &arr[i];

		if (*min > arr[i])
			min = &arr[i];
	}

	*maxPtr = max;
	*minPtr = min;

}

int main() {

	int a = 3;
	int* p = &a;
	int** pp = &p;

	printf("%p\n", p);
	printf("%p\n", pp);

	printf("%d\n", *p);
	printf("%d\n", **pp);

	printf("%p\n", &pp);

	int* maxPtr;
	int* minPtr;
	int arr[5] = {3,2,4,2,6};

	// �Լ����� ������ ���� : 
	// maxPtr�� arr�� ���� ū����
	// minPtr�� arr�� ���� �������� ����Ű����
	int size = sizeof(arr) / sizeof(int);
	RefreshMaxAndMin(arr, size, &maxPtr, &minPtr);

	printf("�ִ밪 : %d, �ּҰ� : %d\n", *maxPtr, *minPtr);

	return 0;
}