#pragma warning(disable:4996)
#include <stdio.h>

int main() {
	
	// 주소 : 메모리 번지

	// & : 주소 연산자
	int a = 3;
	// scanf("%d", &a);
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
	int* p; //포인터 변수
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


	double* pd1, * pd2, d1, d2;
	d1 = 2.0;
	d2 = 4.0;
	pd1 = &d1;
	pd2 = &d2;

	// 대입 연산자 쓰지 않고 *pd1, *pd2, d1, d2의 조합으로 6을 출력할 수 있는
	// 4가지 경우를 써보시오 (각 변수는 연산에 한번씩만 사용가능)
	
	printf("%f + %f = %f\n", d1, d2, d1 + d2);
	printf("%f + %f = %f\n", d1, *pd2, d1 + *pd2);
	printf("%f + %f = %f\n", *pd1, d2, *pd1 + d2);
	printf("%f + %f = %f\n", *pd1, *pd2, *pd1 + *pd2);

	// 상수형 포인터
	// 형태 : const 자료형*
	// 포인터를 바꿀수 없다는게 아니라, 포인터가 가리키는 해당 주소의 값을 바꿀수 없도록함.
	// 즉, 간접참조연산을 L-value 로 사용할 수 없다.

	int n1 = 0, n2 = 0;
	const int* pa = &n1;
	pa = &n2;
	//*pa = 20; // 불가능
	n1 = *pa; // 가능
	// const(상수형)의 사용목적 : 변하지 않으면서 특정 값을 보기 편하게 나타낼때 사용
	
	const int n3 = 0;
	int* pn3 = &n3;
	*pn3 = 3; // 간접 참조를 통해 n3의 번지수에 접근하면
			  // n3 식별자를 거치지 않으므로 해당 주소의 값을 수정할수가 있다
	printf("%d\n", n3);

	// 다른 자료형 포인터간의 대입
	// L-value 포인터 자료형이 더 크다면 할당받지 못한 공간에 접근하는 위험한 상황이
	// 발생할 수 있으므로 주의해야함. 컴파일 에러는 아님

	int _n = 3;
	double _d = 3.5;
	int* _p = &_n;
	double* _pd = &_d;

	printf("_p : &p\n", _p);
	printf("_pd : %p", _pd);
	_p = _pd;
	printf("_p : &p\n", _p);
	printf("_pd : %p", _pd);



	*_p = 3;
	printf("size of *p %d\n", sizeof(*_p));
	printf("%d\n", *_p);
	_pd = _p;
	*_p = 3.5;
	printf("size of *pd %d\n", sizeof(*_pd));
	printf("%lf\n", *_pd);

	int* pc = NULL;
	if (pc != NULL)
		printf("%p", pc);

	// 포인터를 사용하는이유
	// swap 예시

	int _a = 1, _b = 2;
	// 함수 호출
	swap(_a, _b);
	printf("a = %d, b = %d \n", _a, _b); // 예상결과 a = 2, b = 1;

	return 0;
}


void swap(int a, int b) {
	int t = a;
	a = b;
	b = t;
}