#pragma warning(disable : 4996)
#include <stdio.h>
#include "BasicOperations.h"


/*
�ʿ��� �Լ� : ���ϱ�, ����, ������, ���ϱ�, ������ ��ɸ��� ���� �ϳ���

�ܼ�â����
"sum"�Է½� "sum" �Լ� ȣ��
"sub" �Է½� "sub" �Լ� ȣ��
"div" �Է½� "div" �Լ�ȣ��
"mul" �Է½� "mul" �Լ� ȣ��
"mod" �Է½� " mod" �Լ� ȣ��

��� �Լ��� ����ø���

1. ���� ��� �ܼ�â�� ���
2. �������� OperationCount �ϳ��� ������Ű�� �ܼ�â�� ���
*/

int OperationCount;
int main(void) {
	int op[4];
	int a, b;

	printf("5 factorial %d\n", factorial(5));

	while (1) {
		int isOperated = 1;
		printf("����� �Է� (sum, sub, div, mul, mod) : ");
		scanf("%s", &op);
		printf("���꿡 ����� ���ڸ� �ΰ� �Է� : ");
		scanf("%d %d", &a, &b);

		if (!strcmp("sum", op)) printf("%d\n", sum(a, b));
		else if (!strcmp("sub", op)) printf("%d\n", sub(a, b));
		else if (!strcmp("div", op)) printf("%d\n", div(a, b));
		else if (!strcmp("mul", op)) printf("%d\n", mul(a, b));
		else if (!strcmp("mod", op)) printf("%d\n", mod(a, b));
		else {
			printf("�Է¿���\n");
			isOperated = 0;
		}
		OperationCount += isOperated;
		printf("operation count : %d\n", OperationCount);
	}
}