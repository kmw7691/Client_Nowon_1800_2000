#pragma warning (disable : 4996)
#include <stdio.h>

// FSM( Finite State Machine )
// ���� ���� �ӽ�
enum JumpState {
	Idle,
	PrepareToJump,
	InFlight,
	Falling,
	OnGround,
};

// enum : ������ ��������� �ڷ����� �����ϱ����� Ű����
enum PlayerState {
	Idle,
	Walk,
	Run,
	Attack,
	DoubleAttack,
	Jump,
	Hurt,
};

// playerstate
// ����
// �÷��̾� ����
// 0 = �ƹ��͵� ���� �ʴ� ����
// 1 = �ȱ�
// 2 = �޸���
// 3 = �����ϱ�
// 4 = �����ϱ�
// 5 = �ǰݴ��ϱ�

int playerState;
int main() {

	enum PlayerState playerState;
	playerState = Idle;

	while (1)
	{
		scanf("%d", &playerState);

		switch (playerState)
		{
		case Idle:
			printf("�ƹ��͵� ���� �ʱ�\n");
			break;
		case Walk:
			printf("�ȱ�\n");
			break;
		case Run:
			printf("�޸���\n");
			break;
		case Attack:
			printf("�����ϱ�\n");
			break;
		case Jump:
			printf("�����ϱ�\n");
			break;
		case Hurt:
			printf("�ǰݴ��ϱ�\n");
			break;
		default:
			printf("������������ �𸣰���");
			break;
		}
	}	
}