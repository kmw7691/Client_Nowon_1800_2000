#include "CAnimator.h"
#include "CAniSeq.h"
#include "ryumacro.h"
#include "CAPIEngine.h"
#include "CTexture.h"

CAnimator::CAnimator() :
	mId(""), mpEngine(nullptr),mpCurAniSeq(nullptr),mStrKeyCurAniSeq(""), mStrKeyPrevAniSeq("")
{
	mAniSeqs.clear();
}

CAnimator::CAnimator(const CAnimator& t)
{
	//*this = t;
	mId = t.mId;
	mpEngine = t.mpEngine;
	mpCurAniSeq = t.mpCurAniSeq;
	mStrKeyCurAniSeq = t.mStrKeyCurAniSeq;
	mStrKeyPrevAniSeq = t.mStrKeyPrevAniSeq;
	mpObject = t.mpObject;


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
	mStrKeyPrevAniSeq	 = t.mStrKeyPrevAniSeq;
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
	if (ANI_SO::FRAME_FILE == mpCurAniSeq->mSpriteOption)
	{

		int tIndex = mpCurAniSeq->mCurFrameIndex;
		CTexture* tpTex = mpCurAniSeq->mTexs[tIndex];
		if (tpTex)
		{
			tpEngine->DrawTexture(tX, tY, tpTex);
		}

		LateUpdate();
	}

	else if (ANI_SO::SHEET_FILE == mpCurAniSeq->mSpriteOption)
	{
		int tIndex = mpCurAniSeq->mCurFrameIndex;
		CTexture* tpTex = mpCurAniSeq->mTexs[0];
		if (tpTex)
		{
			tpEngine->DrawTexturePartial(tX, tY, tpTex, mpCurAniSeq->mRow, mpCurAniSeq->mCol, tIndex);
		}

		LateUpdate();
	}
}

bool CAnimator::AddAniSeq(const string& tName, float tTimeinterval, int tTotalFramesCount, 
												LPCWSTR tpFileName, ANI_PO tPlayOption,
												ANI_SO tSpriteOption,
												int tRow, int tCol)
{
	CAniSeq* tpClip = new CAniSeq();

	//ryu
	tpClip->mId = tName;

	tpClip->mPlayOption = tPlayOption;

	tpClip->mTimeInterval = tTimeinterval;
	tpClip->mTotalFramesCount = tTotalFramesCount;


	tpClip->mSpriteOption = tSpriteOption;

	tpClip->mRow = tRow;
	tpClip->mCol = tCol;


	if (ANI_SO::FRAME_FILE == tSpriteOption)
	{
		for (int ti = 0; ti < tTotalFramesCount; ++ti)
		{
			CTexture* tpTex = nullptr;
			tpTex = new CTexture();

			WCHAR szTemp[256] = { 0 };
			wsprintf(szTemp, L"%s_%d.bmp", tpFileName, ti);

			tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);
			tpClip->mTexs.push_back(tpTex);
		}

		tpClip->SetSpriteFrameWH();
	}
	else if (ANI_SO::SHEET_FILE == tSpriteOption)
	{
		CTexture* tpTex = nullptr;
		tpTex = new CTexture();

		WCHAR szTemp[256] = { 0 };
		wsprintf(szTemp, L"%s.bmp", tpFileName);

		tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);
		tpClip->mTexs.push_back(tpTex);

		tpClip->SetSpriteFrameWH(tRow, tCol);
	}

	mAniSeqs.insert(make_pair(tName, tpClip));

	return true;
}


void CAnimator::SetDefaultAniSeq(const string& tStrDefaultAniSeq)
{
	mStrKeyPrevAniSeq = tStrDefaultAniSeq;
	mStrKeyCurAniSeq = tStrDefaultAniSeq;

	if (nullptr != mpCurAniSeq)
	{
		mpCurAniSeq->mCurFrameIndex = 0;
		mpCurAniSeq->mAniTime = 0.0f;
	}
}


void CAnimator::PlayAni(const string& tStrAniSeq)
{
	//현재 애니메이션 시퀀스를 기억시켜두고
		   //(교체된 애니메이션 시퀀스를 플레이하고 이전 애니메이션 시퀀스로 돌아가기 위해)
	mStrKeyPrevAniSeq = mStrKeyCurAniSeq;
	//애니메이션 시퀀스를 교체한다
	mStrKeyCurAniSeq = tStrAniSeq;

	if (nullptr != mpCurAniSeq)
	{
		mpCurAniSeq->mCurFrameIndex = 0;
		mpCurAniSeq->mAniTime = 0.0f;
	}
}


void CAnimator::LateUpdate()
{
	//late update
	switch (mpCurAniSeq->mPlayOption)
	{
	case ANI_PO::LOOP:
	{
	}
	break;
	case ANI_PO::ONCE:
	{
		//마지막 프레임까지 애니메이션 되었다면,
		//					그리고, 애니메이션 시간이 다 되엇다면
		//이전에 하던 애니메이션을 플레이한다
		if (mpCurAniSeq->mCurFrameIndex == mpCurAniSeq->mTotalFramesCount - 1)
		{
			if (mpCurAniSeq->mCurFrameIndex == mpCurAniSeq->mTimeInterval)
			{
				mStrKeyCurAniSeq = mStrKeyPrevAniSeq;


				mpCurAniSeq->mCurFrameIndex = 0;
				mpCurAniSeq->mAniTime = 0.0f;
			}
		}
	}
	break;
	}
}

