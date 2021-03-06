#include <stdio.h>
#include "test.h"

// 반환형 함수이름 (매개변수1자료형 매개변수1이름, 매개변수2자료형 매개변수2이름, ... )
// {
//		연산내용
//		반환문 (return 반환값)
// }

// 지역변수 : 중괄호 내에 정의된 변수. 해당 중괄호를 벗어나면 메모리에서 지워짐.
// 전역변수 : 모든 곳에서 접근할수 있는 변수

int globalCount;


// 데이터 영역에 저장되는 변수들 ( 전역변수, 정적변수 ) 은 선언과 동시에 0 으로 초기화된다.

int main(void) {

	doSomething();

	int testNum1 = 3;
	int testNum2 = 5;
	// 함수의 호출 형태
	// 함수이름(인자1, 인자2, ...)
	sum(testNum1, testNum2);
	sum(2, 3); // 한번 정의 된 함수는 여러번 호출 가능.( 함수호출시 정의된 함수를 복사해서 사용함)
	sub(4, 3);
	return 0;
}

int doSomething() {

	//int globalCount = 0; // 지역변수는 해당 중괄호 밖에서 정의된 모든 같은 이름의 변수보다 우선순위다. 

	// static : 정적 키워드 , static 으로 선언되면 동적으로 메모리할당이 불가능하다. 프로그램이 끝날때까지 지워지지 않도록 데이터영역에 저장된다.
	static int localCount; // 정적 지역변수 : 데이터영역에 저장되어 프로그램이 끝날떄까지 지워지지는 않지만, 해당 중괄호 안에서만 접근가능하다. 

	localCount++;
	globalCount++;
	printf("doSomething has been called :  %d times(global)\n", globalCount);
	printf("doSomething has been called :  %d times(static local)\n", localCount);

	if (localCount < 10) {
		doSomething();// 재귀함수 : 함수 내에서 동일한 함수 호출
	}
	return 0;
}

// 매개변수 도 지역변수 ( 매개변수 ⊂ 지역변수 )
int sum(int a, int b) {

	int tmpValue = a + b;
	printf("%d\n", tmpValue); // 함수 내에서도 함수 호출 가능
	return tmpValue;
}

int sub(int a, int b) {

	// register 변수
	// 해당 변수를 빠른 연산을위해서 메모리에 할당하지말고 register 에 직접 할당을 시도하는 키워드
	// 만약에 register 키워드를 사용하는게 적절하지 않다고 컴파일러가 판단하면 register에 할당하지 않는다.
	register int tmpValue = a - b;
	printf("%d\n", tmpValue);
	return tmpValue;
}