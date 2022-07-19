#include "CAniSeq.h"

void CAniSeq::Update(float tDeltaTime)
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
		mAniTime = mAniTime + tDeltaTime;
	}
}
