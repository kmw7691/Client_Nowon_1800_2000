#include <iostream>
#include <stdlib.h>
using namespace std;

struct MyStruct
{
	int a;
};

int main() {

	// c���� �����Ҵ�
	struct MyStruct* a = (struct MyStruct*)malloc(sizeof(MyStruct));
	free(a);

	// c++���� �����Ҵ�
	// new Ű���带 ���
	// Ÿ��* �������̸� = new Ÿ��;
	MyStruct* myStruct = new MyStruct;
	delete myStruct;

	int* pi = new int;
	*pi = 100;
	cout << *pi << endl; // namespace �Ⱦ��� �׻� std:: �ٿ��ٰ�
	delete pi;

	return 0;
}