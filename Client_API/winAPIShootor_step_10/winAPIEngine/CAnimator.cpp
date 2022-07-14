#include "CAnimator.h"
#include "CAniSeq.h"
#include "ryumacro.h"
#include "CAPIEngine.h"
#include "CTexture.h"

CAnimator::CAnimator() :
	mId(""), mpEngine(nullptr),mpCurAniSeq(nullptr),mStrKeyCurAniSeq("")
{
	mAniSeqs.clear();
}

CAnimator::CAnimator(const CAnimator& t)
{
	*this = t;

	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;

		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}
}

CAnimator::~CAnimator()
{
	unordered_map<string, CAniSeq*>::iterator tItor;
	for (tItor = mAniSeqs.begin(); tItor != mAniSeqs.end(); ++tItor)
	{
		SAFE_DELETE(tItor->second);
	}

	mAniSeqs.clear();
}

void CAnimator::operator=(const CAnimator& t)
{
	//*this = t;

	mId								 = t.mId;
	mpEngine					 = t.mpEngine;
	mpCurAniSeq				 = t.mpCurAniSeq;
	mStrKeyCurAniSeq		 = t.mStrKeyCurAniSeq;
	mpObject						 = t.mpObject;


	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;

		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}
}

void CAnimator::UpdateAnimation(float t)
{
	//test
	//this->mStrKeyCurAniSeq = "ani_idle_actor";


	unordered_map<string, CAniSeq*>::iterator tItor = mAniSeqs.find(mStrKeyCurAniSeq);
	mpCurAniSeq = tItor->second;

	mpCurAniSeq->Update(t);
}

void CAnimator::Render(CAPIEngine* tpEngine, float tX, float tY)
{
	int tIndex = mpCurAniSeq->mCurFrameIndex;
	CTexture* tpTex = mpCurAniSeq->mTexs[tIndex];
	if (tpTex)
	{
		tpEngine->DrawTexture(tX, tY, tpTex);
	}
}

bool CAnimator::AddAniSeq(const string& tName, float tTimeinterval, int tTotalFramesCount, LPCWSTR tpFileName)
{
	CAniSeq* tpClip = new CAniSeq();

	//ryu
	tpClip->mId = tName;


	tpClip->mTimeInterval = tTimeinterval;
	tpClip->mTotalFramesCount = tTotalFramesCount;


	for (int ti = 0; ti < tTotalFramesCount; ++ti)
	{
		CTexture* tpTex = nullptr;
		tpTex = new CTexture();

		WCHAR szTemp[256] = { 0 };
		wsprintf(szTemp, L"%s_%d.bmp", tpFileName, ti);

		tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);
		tpClip->mTexs.push_back(tpTex);
	}

	mAniSeqs.insert(make_pair(tName, tpClip));

	return true;
}

