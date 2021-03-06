#include <stdio.h>

// While : 특정 조건에 따라 내용을 반복 제어
// 형태 : while(조건){조건이 참일때 반복할 내용}

// do while : 내용을 일단 한번 실행하고 특정 조건에 따라 내용을 반복제어
// 형태 : do{조건이 참일때 반복할내용} while(조건)

int main(void) {

	while (1) // while(1) : 조건이 항상 참인 반복문(if, case포함)을 무한 루프라고함
	{
		printf("asdfugayhq111\n");
			break; // 분기문, 가장 가까운 반복문을 찾아서 해당 반복문을 조건 비교줄로 돌아감
					  // go to분기문도 있지만 성능이 안좋아서 안씀
		printf("asdfugayhq222\n");
	}
	printf("while statement is over\n");

	int count = 0;
	while (count < 5) {
		printf("while count : %d\n", count);
		count++;
	}
	printf("while statement is over\n");

	// do while
	do {
		printf("do while test\n");
	} while (0);

	return 0;
}