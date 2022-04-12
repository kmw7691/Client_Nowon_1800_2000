#include <iostream>
#include <stdlib.h>
using namespace std;

struct MyStruct
{
	int a;
};

int main() {

	// c에서 동적할당
	struct MyStruct* a = (struct MyStruct*)malloc(sizeof(MyStruct));
	free(a);

	// c++에서 동적할당
	// new 키워드를 사용
	// 타입* 포인터이름 = new 타입;
	MyStruct* myStruct = new MyStruct;
	delete myStruct;

	int* pi = new int;
	*pi = 100;
	cout << *pi << endl; // namespace 안쓸땐 항상 std:: 붙여줄것
	delete pi;

	return 0;
}