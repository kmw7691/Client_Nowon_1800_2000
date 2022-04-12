#pragma warning(disable : 4996)
#include <stdio.h>

int GetFactorial(int n);
double sum(double a, double b), sub(double a, double b), mul(double a, double b), div(double a, double b);

int main() {
	// 함수 포인터의 형태
	// 반환형 (*함수포인터변수이름)(파라미터1자료형 (파라미터1) ...) 
	int (*pf)(int);
	pf = GetFactorial;

	printf("%d\n", GetFactorial(5));
	printf("%d\n", pf(5));

	// 예제 
	double (*pOP)(double, double) = NULL;
	char op[20]; // 명령어 입력을 받을 문자열
	printf("연산 명령어를 입력하세여 (sum, sub, div, mul):");
	scanf("%s", op);

	if (!strcmp(op, "sum")) pOP = sum;
	else if (!strcmp(op, "sub")) pOP = sub;
	else if (!strcmp(op, "div")) pOP = div;
	else if (!strcmp(op, "mul")) pOP = mul;

	if (pOP != NULL)
		printf("3 과 7의 연산 결과는 : %lf\n", pOP(3, 7));

}

int GetFactorial(int n) {
	int fact = 1;
	for (int i = 1; i <= n; i++)
	{
		fact *= i;
		fact = fact * i;
	}
	return fact;
}

double sum(double a, double b)
{
	return a + b;
}

double sub(double a, double b)
{
	return a - b;
}

double mul(double a, double b)
{
	return a * b;
}

double div(double a, double b)
{
	return a / b;
}