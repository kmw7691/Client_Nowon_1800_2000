#pragma once

#include <unordered_map>
using namespace std;

#include <windows.h>

#include "CAniSeq.h"


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

	bool Create(CAPIEngine* tpEngine);
	void Destroy();
	

	void UpdateAnimation(float t);
	void Render(CAPIEngine* tpEngine, float tX, float tY);

	//ryu_ani_spritesheet_i
	bool AddAniSeq(const string& tStrKey, float tTimeInterval, int tTotalFramesCount, ANI_PO tPlayOption = ANI_PO::LOOP, ANI_SO tSpriteOption = ANI_SO::FRAME_FILE, int tRow = 1, int tCol = 1);

	void SetCurAniClip(const string& tStrCurAniClip);
	void ChangeAniClip(const string& tStrClip);

	void SetDefaultAniSeq(const string& tStrDefaultAniSeq);
	void PlayAni(const string& tStrAniSeq);

	void LateUpdate();


	void SetOwnerObject(CObjectRyu* tpObject)
	{
		mpObject = tpObject;
	}
	CObjectRyu* GetOwnerObject() const
	{
		return mpObject;
	}

//protected:	
public:
	//여러 애니메이션클립의 집합
	unordered_map<string, CAniSeq*> mAniSeqs;

	string mId = "";
	CAPIEngine* mpEngine = nullptr;

	CAniSeq* mpCurAniSeq = nullptr;
	string mStrKeyCurAniSeq;


	//ryu_ani_spritesheet_i
	CObjectRyu* mpObject = nullptr;	//
	//CUnit* mpObject = nullptr;


	string mStrKeyPrevAniSeq = "";

};

