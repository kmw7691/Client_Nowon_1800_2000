#include <stdio.h>

// if 문 : 특정 조건의 참/거짓 여부에 따라 흐름을 제어함.
// 형태 : if (조건){조건이 참일때 실행할 내용}


// if else 문
// 형태 : if(조건){조건이 참일때 실행할 내용}
//		  else	  {조건이 거짓일때 실행할 내용}

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