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

//typeid�� ����
#include <typeinfo>

#include <windows.h>
#include <string>
#include <unordered_map>			// �ؽ����̺� �ڷᱸ���� �����̳ʷ� �������� ��. �˻��ӵ��� 0(1)
#include <vector>
using namespace std;


//Ű ������ ǥ���ϱ����� ����ü
struct SKeyInfo
{
	string mStrName = "";		//Ű
	vector<DWORD> mKeyInputs;	//������
	//DWORD mKeyInput = 0;			//������


	bool mIsDown = false;
	bool mIsPress = false;
	bool mIsUp = false;

	SKeyInfo()
		:mIsDown(false), mIsPress(false), mIsUp(false)
	{
		mKeyInputs.clear();
	}
};

class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)

private:
	HWND mhWnd;

	//�ؽ����̺��� ������̴� 0(1)�� ������ ����
	unordered_map<string, SKeyInfo*> mMapKeys;

	SKeyInfo* mpKeyInfo = nullptr;

public:
	virtual void Create(HWND hWnd);
	
	void Update();				// Ű���� �Է� ���¸� �����ϱ����� ���ӷ����󿡼� ��� ���ŵǴ� �Լ�

	SKeyInfo* FindKey(const string& tStrKey) const;			//���ϴ� Ű�Է��� �˻��ϴ� �Լ�


	bool KeyDown(const string& tStrKey) const;			//Down  ������ ����
	bool KeyPress(const string& tStrKey) const;			//Press  ������ �ִ� ����
	bool KeyUp(const string& tStrKey) const;			//Up  �������� ����


	// �߻�ȭ�� �Է� �̸��� ���� Ű�Է������� ���ν��Ѽ� ����ϴ� �Լ�
	//  (char Ÿ�԰� int Ÿ���� ��� ó���ϱ����� ���ø��Լ��� �ۼ�)
	//template<typename T>
	//bool AddKey(const string& tInputName, const T& tData)
	//{
	//	if (!mpKeyInfo)
	//	{
	//		mpKeyInfo = new SKeyInfo(); // ���ο� Ű���� �Է�������ü�ϳ��� �����Ѵ�
	//	}


	//	//typeid Ÿ�Կ� ������ �˾ƿ��� ������

	//	const char* tpType = typeid(T).name();	// Ÿ���� �̸��� ���´�


	//	if (strcmp(tpType, "char") == 0 || strcmp(tpType, "int") == 0)
	//	{
	//		mpKeyInfo->mKeyInput = (DWORD)tData;			// Ű�����Է�������ü�� Ű�Է�
	//	}
	//	else
	//	{
	//		return false;
	//	}

	//	//�߻�ȭ �̸� ���
	//	//Ű
	//	mpKeyInfo->mStrName = tInputName;
	//	//�߻�ȭ �̸��� Ű��, ���� Ű�Է��� �����ͷ� ���
	//	mMapKeys.insert(make_pair(mpKeyInfo->mStrName, mpKeyInfo));	//Ű, ��(����������) ���� ������(Ű�����Է�������ü)�� �ؽ����̺� �߰�


	//	if (mpKeyInfo)
	//	{
	//		mpKeyInfo = nullptr;
	//	}

	//	return true;
	//}

	//base case
	// ��������� ȣ��� ���� �������� �Լ�

	template<typename T>
	bool AddKey(const T& tData)
	{
		////typeid Ÿ�Կ� ������ �˾ƿ��� ������

		const char* tpType = typeid(T).name();	// Ÿ���� �̸��� ���´�


		if (strcmp(tpType, "char") == 0 || strcmp(tpType, "int") == 0)
		{
			//Ű���
			//DWORD�� ��ȯ
			mpKeyInfo->mKeyInputs.push_back( (DWORD)tData );			// Ű�����Է�������ü�� Ű�Է�
		}
		else
		{
			//�߻�ȭ �̸� ���
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(make_pair(mpKeyInfo->mStrName, mpKeyInfo));
		}

		return true;
	}







	// �������� ���ø� : �Ű�����(Ÿ��)�� ������ ���������� �Է¹޴� ���ø� ����
	template<typename T, typename... Types>
	bool AddKey(const T& tData, const Types&... arg)
	{
		if (!mpKeyInfo)
		{
			mpKeyInfo = new SKeyInfo(); // ���ο� Ű���� �Է�������ü�ϳ��� �����Ѵ�
		}


		////typeid Ÿ�Կ� ������ �˾ƿ��� ������

		const char* tpType = typeid(T).name();	// Ÿ���� �̸��� ���´�


		if (strcmp(tpType, "char") == 0 || strcmp(tpType, "int") == 0)
		{
			//Ű���
			//DWORD�� ��ȯ
			mpKeyInfo->mKeyInputs.push_back( (DWORD)tData );			// Ű�����Է�������ü�� Ű�Է�
		}
		else
		{
			//�߻�ȭ �̸� ���
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(make_pair(mpKeyInfo->mStrName, mpKeyInfo));
		}


		//��������� ȣ�� recursive case
		AddKey(arg...);


		//����������� ���ȣ���� ��� ���� ���̴�
		if (mpKeyInfo)
		{
			mpKeyInfo = nullptr;
		}

		return true;
	}
};
