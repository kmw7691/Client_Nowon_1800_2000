#include<stdio.h>

int main() 
{
	//scanf
	//scanf(���Ĺ��ڿ�, ������ ����)
	//�Է��� ���Ë� ���� ����ϴٰ� ������ ������ ������ �ش� �Է°��� ������
	int n; 
	printf("Enter intafer value");
	scanf_s("%d", &n);
	printf("n : %d", n);

	// & : ���� ������
	//���� �տ� �پ �ش� ������ �ּҰ��� �����ϴ� ������

	float f ;
	scanf_s("%f", &f);

	char str[20];
	scanf_s("%s", str , 10+sizeof(char));
	// sizeof Ű����
	// ������� : sizeof(�ڷ���)
	// �ڷ����� �ش��ϴ� ������ ũ�⸦ ��ȯ��

	printf("str : %s", str);

	return 0;
}