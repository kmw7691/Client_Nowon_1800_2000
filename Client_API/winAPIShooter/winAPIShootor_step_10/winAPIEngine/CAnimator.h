#pragma once
#include <windows.h>
#include <unordered_map>
using namespace std;


class CAniSeq;
class CAPIEngine;
class CObjectRyu;

class CAnimator
{
public:
	CAnimator();
	CAnimator(const CAnimator& t);
	~CAnimator();

	void operator=(const CAnimator& t);


	void SetId(string tId)
	{
		mId = tId;
	}

	bool Create(CAPIEngine* tpEngine)
	{
		mpEngine = tpEngine;

		return true;
	}

	void Destroy()
	{

	}

	//���� �ִϸ��̼� ������ ���� �����Ͱ���
	void UpdateAnimation(float t);
	//���� �ִϸ��̼��� ��� ��� ������
	void Render(CAPIEngine* tpEngine, float tX, float tY);

	//�ִϸ��̼� �������� ����ϴ� �Լ�
	bool AddAniSeq(const string& tName, float tTimeinterval, int tTotalFramesCount, LPCWSTR tpFileName);

	
	void SetOwnerObject(CObjectRyu* tpObject)
	{
		mpObject = tpObject;
	}

	CObjectRyu* GetOwnerObject() const
	{
		return mpObject;
	}




public:

	unordered_map<string, CAniSeq*> mAniSeqs;

	string mId = "";								//�� �ִϸ������� �ĺ��� Ű

	CAPIEngine* mpEngine = nullptr;					// ������ �ּҰ�

	CAniSeq* mpCurAniSeq = nullptr;					//���� ���ϸ��̼� �������� �ּҰ�
	string mStrKeyCurAniSeq;								//���� �ִϸ��̼� �������� �ĺ��� Ű


	// 
	CObjectRyu* mpObject = nullptr;
};
