#include <stdio.h>

void print_all_elements(int* arr,int len) {

	for (int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
}

int main() {

	// 배열을 선언하게되면
	// 배열이 메모리에 할당될때
	// a라는 변수명을 컴파일 할때 포인터형 변수로 바꿈
	// 즉 배열은 앞에 포인터(*)가 붙지 않아도 포인터 변수임.
	int arr[] = { 10,20,30,40,50,80,90 };
	int len = sizeof(arr) / sizeof(int);
	print_all_elements(arr, len);
	printf("%p\n", arr);
	printf("%d\n", arr[0]); // arr[index]는 변수형태
	printf("%p\n", &arr[0]);
	printf("%p\n", &arr[1]);

	// 포인터 간의 연산
	printf("%p\n", arr + 4); // 의미 : arr주소에 4 * sizeof(arr 자료형)
	printf("%d\n", *(arr + 0)); // 의미 : arr주소에서부터 arr 자료형 크기만큼 값을 참조함.
	printf("%d\n", *(arr + 1));
	printf("%d\n", *(arr + 2));
	printf("%d\n", *(arr + 3));
	printf("%d\n", *(arr + 4));
	
	int* p, * q;
	p = &arr[0];
	q = &arr[4];

	// 포인터 간의 덧셈은 불가능함
	//printf("%d\n", p + q);

	// 포인터 간의 뺄셈 = 주소간의 인덱스 차이를 반환함
	// 뺄셈의 결과값이 음수면, 해당 인덱스 * 자료형 byte 수 만큼 주소가 앞서있다.
	printf("%d\n", p - q);

	// 포인터 간의 관계연산
	printf("%d\n", p < q);

	// 포인터의 덧셈
	printf("%d\n", *p++);
	printf("%d\n", *(p++));
	printf("%d\n", ++*p);
	printf("%d\n", *(++p));
	printf("%d\n", (*p)++);
	printf("%d\n", *p);

	return 0;
}