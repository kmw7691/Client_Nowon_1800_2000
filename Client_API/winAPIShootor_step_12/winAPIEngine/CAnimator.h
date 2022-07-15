#pragma once
#include <windows.h>
#include <unordered_map>
#include "CAniSeq.h"
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

	//현재 애니메이션 진행을 위한 데이터갱신
	void UpdateAnimation(float t);
	//현재 애니메이션의 결과 포즈를 랜더링
	void Render(CAPIEngine* tpEngine, float tX, float tY);

	//애니메이션 시퀀스를 등록하는 함수
	bool AddAniSeq(const string& tName, float tTimeinterval, int tTotalFramesCount,
								LPCWSTR tpFileName , ANI_PO tPlayOption = ANI_PO::LOOP);

	
	void SetDefaultAniSeq(const string& tStrDefaultAniSeq);
	void PlayAni(const string& tStrAniSeq);

	void LateUpdate();




	//

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

	string mId = "";								//이 애니메이터의 식별자 키

	CAPIEngine* mpEngine = nullptr;					// 엔진의 주소값

	CAniSeq* mpCurAniSeq = nullptr;					//현재 에니메이션 시퀀스의 주소값
	string mStrKeyCurAniSeq;								//현재 애니메이션 시퀀스의 식별자 키
	string mStrKeyPrevAniSeq;

	// 
	CObjectRyu* mpObject = nullptr;
};

