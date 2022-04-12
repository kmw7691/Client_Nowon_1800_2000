#include<stdio.h>

int main() 
{
	//scanf
	//scanf(서식문자열, 변수값 참조)
	//입력이 들어올떄 까지 대기하다가 들어오면 참조한 변수에 해당 입력값을 대입함
	int n; 
	printf("Enter intafer value");
	scanf_s("%d", &n);
	printf("n : %d", n);

	// & : 참조 연산자
	//변수 앞에 붙어서 해당 변수의 주소값을 참조하는 연산자

	float f ;
	scanf_s("%f", &f);

	char str[20];
	scanf_s("%s", str , 10+sizeof(char));
	// sizeof 키워드
	// 사용형태 : sizeof(자료형)
	// 자료형에 해당하는 데이터 크기를 반환됨

	printf("str : %s", str);

	return 0;
}