#include <iostream>
#include "MyTemplate.h"

// 포인터를 쓰는경우 vs 참조자를 쓰는경우
// 포인터 : 직접 해당 변수의 주소값이 필요한경우
// 참조자 : 해당 변수의 값만 필요한경우
template <typename T>
void Swap(T& a, T& b);

template <typename T, typename K>
void ForceSum(T& a, K& b);

int main() {

	int a = 3;
	int b = 5;
	double c = 2.0;
	double d = 4.4;

	Swap<int>(a, b);
	Swap<double>(c, d);

	// 함수템플릿
	ForceSum<int, double>(a, c);

	// 
	MyTemplate<int, double> myTemplate;
	myTemplate.ForceSum(a, c);

	return 0;
}

template<typename T>
void Swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template<typename T, typename K>
void ForceSum(T& a, K& b)
{
	return a + (T)b;
}
