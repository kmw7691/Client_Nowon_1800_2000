#include <stdio.h>

// for : 특정 조건에 따라 반복하면서
//		 반복 할때마다 특정 함수를 수행할 수 있는 반복문
// 형태 : for(초기값; 조건식 ; 증감식){조건이 참일때 실행할 내용}

int main(void) {
	// 변수 선택후 (ctrl + r) 두번 누르면 선택한 변수를 모두 변경할수있음
	for (int count = 0; count < 5; count++)
	{
		printf("%d\n", count);
	}

	for (int i = 0; ; i++)
	{
		if (i < 5) {
			printf("%d\n", i);
			continue; // 안써도 반복은 됨. 근데 처리과정에서 continue를 만나면 이후 과정을 실행하지 않고
					  // 다시 처음 반복으로 돌아감.
		}
		else {
			printf("\n");
		}

		if (i > 10) {
			printf("index is bigger than 10, finish for loop\n");
			break;
		}

		printf("for loop is on going");
	}

	return 0;
}