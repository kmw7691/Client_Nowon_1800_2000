#pragma once



// �̱��� ����

/*
	�̱��� ������ ���� : ��ü�� �ִ� ���������� 1���� ����
						  (�ΰ������� �������� ������ �����͵��� ������ �������ε� ����)

	������ ������ �������� �̷������.
		- �ش� Ŭ���� ������ Ÿ���� mpInstance ������ static���� ����ȴ�
		- �����ڴ� public�� �ƴϴ�
		- GetInstance() �Լ��� ���ǿ��� ��ü�� �ִ� ���������� 1���� �����ϴ� �Ǵ�������� ��ġ�Ѵ�
*/

//step 0

//class CInputMgr
//{
//private:
//	//static Ű����� ������ ������ �����͸޸𸮿����� ��ġ�Ѵ�
//	//Ŭ������ ����� �ƴϹǷ�? Ŭ������ ��� �ʱ�ȭ ������ ���� �� ����
//
//	static CInputMgr* mpInstance; //= nullptr;
//
//	CInputMgr();
//	~CInputMgr();
//
//public:
//	static CInputMgr* GetInst();
//	static void ReleaseInst();
//};

#include "Kmacro.h"

class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)
};
