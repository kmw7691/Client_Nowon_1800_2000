#include <stdio.h>

// While : Ư�� ���ǿ� ���� ������ �ݺ� ����
// ���� : while(����){������ ���϶� �ݺ��� ����}

// do while : ������ �ϴ� �ѹ� �����ϰ� Ư�� ���ǿ� ���� ������ �ݺ�����
// ���� : do{������ ���϶� �ݺ��ҳ���} while(����)

int main(void) {

	while (1) // while(1) : ������ �׻� ���� �ݺ���(if, case����)�� ���� ���������
	{
		printf("asdfugayhq111\n");
			break; // �б⹮, ���� ����� �ݺ����� ã�Ƽ� �ش� �ݺ����� ���� ���ٷ� ���ư�
					  // go to�б⹮�� ������ ������ �����Ƽ� �Ⱦ�
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