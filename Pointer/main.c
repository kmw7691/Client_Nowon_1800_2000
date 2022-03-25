#pragma warning(disable:4996)
#include <stdio.h>

int main() {
	
	// & : 주소 연산자
	int a = 3;
	//scanf("%d", &a);
	printf("%d\n", a);
	printf("%d\n", &a);
	printf("%p`\n", &a);


	// * : 간접 참조 연산자
	// 주소 앞에 붙어서 해당 주소의 값을 참조함.
	// 직접참조 : 값을 직접 참조하는걸 직접참조라고 한다(변수 R Value 사용)
	printf("%d\n", *&a);
	printf("%d\n", sizeof(*&a));

	// * : 포인터
	// 자료형 뒤에 붙어서 해당 자료형의 주소를 가리키는 자료형으로 바꿔줌
	int* p;
	p = &a;
	printf("%d\n", p);

	double d = 1.23;
	double* pd;
	p = &d;

	// 포인터도 변수 자료형이, 포인터 변수는 자료형 상관없이 4byte 크기를 할당받는다
	// 단, 16비트 컴퓨터는 2byte
	printf("%d\n", sizeof(p));
	printf("%d\n", sizeof(pd));

	printf("size of *p %d\n", sizeof(*p));
	printf("size of *pd %d\n", sizeof(*pd));

	return 0;
}