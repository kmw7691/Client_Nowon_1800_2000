#include <stdio.h>

// if �� : Ư�� ������ ��/���� ���ο� ���� �帧�� ������.
// ���� : if (����){������ ���϶� ������ ����}


// if else ��
// ���� : if(����){������ ���϶� ������ ����}
//		  else	  {������ �����϶� ������ ����}

int main(void) {
	int isTrue = 0;

	if (isTrue) {
		printf("this is True\n");
	}

	else {
		printf("this is false\n");
	}

	int num = 0;

	if (num == 0) {
		printf("this is 0\n");
	}
	else if (num == 1) {
		printf("this is 1\n");
	}
	else if (num == 2) {
		printf("this is 2\n");
	}
	else {
		printf("I don't know this number\n");
	}
}