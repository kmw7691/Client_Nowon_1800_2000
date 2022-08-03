#include "CAniSeq.h"

#include "CTexture.h"


void CAniSeq::Update(float fElapsedTime)
{
	if (mAniTime >= mTimeInterval)
	{
		if (mCurFrameIndex < mTotalFramesCount - 1)
		{
			mCurFrameIndex = mCurFrameIndex + 1;
		}
		else
		{
			mCurFrameIndex = 0;
		}


		mAniTime = 0.0f;
	}
	else
	{
		mAniTime = mAniTime + fElapsedTime;
	}
}

void CAniSeq::SetSpriteFrameWH(int tRow, int tCol)
{
	this->mSpriteWidth = this->mTexs[0]->mBitmapInfo.bmWidth / tCol;
	this->mSpriteHeight = this->mTexs[0]->mBitmapInfo.bmHeight / tRow;
}