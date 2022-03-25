#include<stdio.h>

int main(void) {

	// 키워드 (예약어)
	// 내부적으로 문법을 위한 용도로 정의되어있는 단어.
	// 변수 이름으로 키워드는 사용할수 없다.

	int STR;
	int DEX;
	int CON;
	int INT;

	//정수형 변수
	int a;//4byte, 부호가 있는 정수 자료형
	//unsigned:부호가 없는 형태로 사용 가능하게 한다
	unsigned int ua;//
	short s;//2byte, 부호가 있는 정수 자료형
	long l; // 4byte, 부호가 있는 정수 자료형
	long long ll; // 8byte 이상, 부호가 있는 정수 자료형
	char c; // 1byte(대부분) , 문자 자료형

	// = : 대입연산자 오른쪽에있는 값을 왼쪽에 있는 변수에 대입하는 연산자.
	// 변수에 값을 써 넣어야 할대는 공간으로
	// 변수의 값을 참조해야할 경우에는 값으로 사용
	
	// 쓰레기값 : 확보한 메모리 공간에 남아있는 알수없는 값
	// 초기화 : 선언된 변수에 가장 처음으로 값을 대입하는 행위 ( 쓰레기값을 없애기 위해서 )

	a = 4;
	ua = 0;
	c = 1232; // -128 ~ 127 까지 범위.1232를 대입하면 오버플로우가 발생함.
	s = 1232;
	printf("%d\n", a);
	printf("%d\n", ua);
	printf("%d\n", c);
	printf("%d\n", s);
	int a2 = 3;

	// 실수 변수 선언
	float f; // 4byte  , 부호가 있는 실수 자료형
	double d; // 8byte ,  부호가 있는 실슈 자료형
	long double ld; // 8byte 이상, 운영체제에 따라 다름

	f = 1.2345648656684534153538486541685415;
	d = 1.2345648656684534153538486541685415;
	ld = 1.2345648656684534153538486541685415;

	printf("%.30f\n", f);
	printf("%.30lf\n", d);
	printf("%.30llf\n", ld);


	//배열(Array)	
	//============================================

	// 1차원 배열
	int arr1x_1[3] = { 1, 2, 3 };
	int arr1x_2[3] = { 1, 2 };
	double arr1x_3[3] = { 4.4, 5.5, 6.2 };

	printf("%d\n", arr1x_1[0]);
	printf("%d\n", arr1x_1[1]);
	printf("%d\n", arr1x_1[2]);
	
	// 2차원 배열
	short arr2x_1[4][3] = { {1, 2, 3},
							{4, 5, 6},
							{7, 8, 9},
							{0, 1, 2} };

	short arr2x_2[2][3] = { 1, 2, 3, 4, 5, 6 };
	short arr2x_3[][2] = { 1, 2, 3, 4, 5, 6, 7 };
	// 1 3 5 7
	// 2 4 6 0
	printf("%d\n", arr2x_3[3][1]); // 배열이름[열 인덱스][행 인덱스]
	//short arr2x_4[2][] = { 1, 2, 3, 4};
	//배열은 초기화 할때 열의 크기를 정해주면 
	//컴파일러가 배열의 크기는 알아서 확보한다.


	// 문자열 (문자의 배열)
	// 문자열은 배열 마지막에 null 문자가 붙는다.
	// ======================================================
	char str1[20] = "hello";
	char str2[6] = "hello";
	char str3[5] = "hello"; // null 문자가 들어갈 공간이 확보되지 않음.
	char str4[] = "hello";
	char str5[6] = { 'H', 'e', 'l', 'l', 'o', '\0' };

	printf("%c\n", str5[0]);
	printf("%s\n", str5);

	// 함수 호출 형태
	// 함수이름(인자);
	
	//strcpy(문자열 변수, 문자열 값) : 문자열 변수에 문자열 값을 대입.
	strcpy(str1, "I don't know\n");
	printf("%s\n", str1);
	
	//strlen(문자열 값) : 문자열 값의 길이를 반환
	strlen(str1);
	printf("%c\n", strlen(str1));
	printf("%c\n", strlen("I don't know\n"));

	//strcmp(문자열값1, 문자열값2) 문자열을 아스키코드로 변환했을때
	//문자열값 1이 더 크면 양수 반환, 같으면 0 반환, 적으면 -1 반환
	printf("%d\n", strcmp(str2, str4));

	//const
	// const 로 정의된 변수는 초기화 이후에 값을 수정할 수 없음
	// 변수를 상수처럼 사용하기 위한 용도
	//---------------------------------------------------
	const int goalPosition = 200;
	
	//LValue 롸 RValue ?
	//대입연산자 기준으로 왼쪽에 있는 값을 LValue, 오른쪽에있는 값을 RValue 라고함
	//---------------------------------------------------

	// 변수를 선언할 때 유의할 점
	//1. 키워드(예약어) 와 다른 식별자 이름
	//2. 식별자 이름을 쓸 때에는 알파벳,아라비아숫자,_(언더바 : 주로 단어 사이에 구분하기위해 사용)
	
}










