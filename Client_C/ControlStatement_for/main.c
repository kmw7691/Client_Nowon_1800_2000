#include <stdio.h>

// for : Ư�� ���ǿ� ���� �ݺ��ϸ鼭
//		 �ݺ� �Ҷ����� Ư�� �Լ��� ������ �� �ִ� �ݺ���
// ���� : for(�ʱⰪ; ���ǽ� ; ������){������ ���϶� ������ ����}

int main(void) {
	// ���� ������ (ctrl + r) �ι� ������ ������ ������ ��� �����Ҽ�����
	for (int count = 0; count < 5; count++)
	{
		printf("%d\n", count);
	}

	for (int i = 0; ; i++)
	{
		if (i < 5) {
			printf("%d\n", i);
			continue; // �Ƚᵵ �ݺ��� ��. �ٵ� ó���������� continue�� ������ ���� ������ �������� �ʰ�
					  // �ٽ� ó�� �ݺ����� ���ư�.
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