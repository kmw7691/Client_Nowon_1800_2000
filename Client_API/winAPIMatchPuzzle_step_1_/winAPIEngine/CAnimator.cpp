#include "CAnimator.h"

#include "CAniSeq.h"
#include "CTexture.h"
#include "ryumacro.h"

#include "CAPIEngine.h"


CAnimator::CAnimator()
{

}
CAnimator::CAnimator(const CAnimator& t)
{
	

	mId = t.mId;
	mpEngine = t.mpEngine;
	mStrKeyCurAniSeq = t.mStrKeyCurAniSeq;


	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;
		//tpAniClip->mId = tItor->first;


		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}


	mStrKeyPrevAniSeq = t.mStrKeyPrevAniSeq;

}
CAnimator::~CAnimator()
{
	
}



bool CAnimator::Create(CAPIEngine* tpEngine)
{
	mpEngine = tpEngine;

	return true;
}
void CAnimator::Destroy()
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

	mId					= t.mId;
	mpEngine			= t.mpEngine;
	mStrKeyCurAniSeq	= t.mStrKeyCurAniSeq;

	mStrKeyPrevAniSeq = t.mStrKeyPrevAniSeq;


	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;
		//tpAniClip->mId = tItor->first;


		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}
}


void CAnimator::UpdateAnimation(float t)
{
	unordered_map<string, CAniSeq*>::iterator tItor = mAniSeqs.find(mStrKeyCurAniSeq);
	mpCurAniSeq = tItor->second;

	if (mpCurAniSeq)
	{
		mpCurAniSeq->Update(t);
	}
	else
	{
		OutputDebugString(L"mpCurAniSeq is nullptr.");
	}
}
void CAnimator::LateUpdate()
{
	switch (mpCurAniSeq->mPlayOption)
	{
	case ANI_PO::LOOP:
	{

	}
	break;
	case ANI_PO::ONCE:
	{
		if (mpCurAniSeq->mCurFrameIndex == mpCurAniSeq->mTotalFramesCount - 1)
		{
			if (mpCurAniSeq->mAniTime >= mpCurAniSeq->mTimeInterval)
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

void CAnimator::Render(CAPIEngine* tpEngine, float tX, float tY)
{
	if (!mpCurAniSeq)
	{
		return;
	}


	//ryu_ani_spritesheet_i

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
			//tpEngine->DrawTexture(tX, tY, tpTex);

			tpEngine->DrawTexturePartial(tX, tY, tpTex, mpCurAniSeq->mRow, mpCurAniSeq->mCol, tIndex);
		}

		LateUpdate();
	}


	/*int tIndex = mpCurAniSeq->mCurFrameIndex;
	CTexture* tpTex = mpCurAniSeq->mTexs[tIndex];
	if (tpTex)
	{
		tpEngine->DrawTexture(tX, tY, tpTex);
	}

	LateUpdate();*/
}


//ryu_ani_spritesheet_i
//tpFileName: 첫번째 프레임에 해당하는 스프라이트 이미지 파일 이름
//tName: 클립의 이름
//tTimerInterval: 애니메이션 프레임 사이의 시간간격
//tTotalFramesCount: 총 프레임 갯수
//tPlayOption: 루핑인지 한번만 플레이인지
bool CAnimator::AddAniSeq(LPCWSTR tpFileName, const string& tName,
	float tTimeInterval, int tTotalFramesCount, ANI_PO tPlayOption, ANI_SO tSpriteOption, int tRow, int tCol)
{
	CAniSeq* tpSeq			= new CAniSeq();

	tpSeq->mId				= tName;

	tpSeq->mTimeInterval		= tTimeInterval;
	tpSeq->mTotalFramesCount	= tTotalFramesCount;

	tpSeq->mPlayOption		= tPlayOption;

	//ryu_ani_spritesheet_i
	tpSeq->mSpriteOption = tSpriteOption;

	tpSeq->mRow = tRow;
	tpSeq->mCol = tCol;


	
	//ryu_ani_spritesheet_i
	if (ANI_SO::FRAME_FILE == tSpriteOption)
	{
		//프레임 갯수만큼 만들어서 추가한다
		//이름은 뒤에 번호를 붙여 만드는 것으로 규칙을 정하였다.
		for (int ti = 0; ti < tTotalFramesCount; ++ti)
		{
			CTexture* tpTex = nullptr;
			tpTex = new CTexture();


			WCHAR szTemp[256] = { 0 };
			wsprintf(szTemp, L"%s_%d.bmp", tpFileName, ti);

			tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);
			tpSeq->mTexs.push_back(tpTex);
		}

		//ryu_ani_spritesheet_i
		tpSeq->SetSpriteFrameWH();
		/*tpSeq->mSpriteWidth = tpSeq->mTexs[0]->mBitmapInfo.bmWidth / tCol;
		tpSeq->mSpriteHeight = tpSeq->mTexs[0]->mBitmapInfo.bmHeight / tRow;*/
	}
	else if (ANI_SO::SHEET_FILE == tSpriteOption)
	{
		//프레임 갯수만큼 애니메이션 시퀀스를 만들어 추가한다
		//다만 이미지 데이터는 '하나'이다.

		//행과 열 갯수에 기반하여 
		//각각의 스프라이트 프레임의 너비와 높이를 결정한다

		CTexture* tpTex = nullptr;
		tpTex = new CTexture();


		WCHAR szTemp[256] = { 0 };
		wsprintf(szTemp, L"%s.bmp", tpFileName);

		tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);
		tpSeq->mTexs.push_back(tpTex);


		//ryu_ani_spritesheet_i
		tpSeq->SetSpriteFrameWH(tRow, tCol);
		/*tpSeq->mSpriteWidth = tpSeq->mTexs[0]->mBitmapInfo.bmWidth/tCol;
		tpSeq->mSpriteHeight = tpSeq->mTexs[0]->mBitmapInfo.bmHeight / tRow;*/
	}


	mAniSeqs.insert(make_pair(tName, tpSeq));

	return true;
}


void CAnimator::SetCurAniClip(const string& tStrCurAniClip)
{
	ChangeAniClip(tStrCurAniClip);
}

void CAnimator::ChangeAniClip(const string& tStrClip)
{
	if (mStrKeyCurAniSeq == tStrClip)
	{
		return;
	}

	mStrKeyCurAniSeq = tStrClip;

	if (mpCurAniSeq)
	{
		mpCurAniSeq->mTimeInterval = 0.0f;
		mpCurAniSeq->mTotalFramesCount = 0;//======

	}

	/*mpCurAniClip = FindAniClip(tStrClip);

	if( mpCurAniClip)*/
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
	//현재 플레이 중인 애니메이션 시퀀스 키를 저장해둠
	mStrKeyPrevAniSeq				= mStrKeyCurAniSeq;


	//새로 플레이할 애니메이션 시퀀스 정보를 설정
	mStrKeyCurAniSeq				= tStrAniSeq;

	if (nullptr != mpCurAniSeq)
	{
		mpCurAniSeq->mCurFrameIndex = 0;
		mpCurAniSeq->mAniTime = 0.0f;
	}
}

