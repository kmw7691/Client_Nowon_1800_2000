#include "CUnit.h"
#include "CAPIEngine.h"
#include "CTexture.h"

// 초기화목록을 이용하여 초기화함
//CUnit::CUnit() : mX(400.0f), mY(500.0f), mRadius(30.0f)
CUnit::CUnit() : CObjectK(), mRadius(30.0f), mVelocity()
{

}

CUnit::~CUnit()
{

}


void CUnit::Render()
{
	/*
	//tpEngine->DrawCircle(mX, mY, mRadius);

	//tpEngine->DrawTexture(mX, mY, mpTexture);

	float tWidth = 0.0f;
	float tHeight = 0.0f;
	*/
	if (mIsActive)
	{
		/*mWidth = mpTexture->mBitmapInfo.bmWidth;
		mHeight = mpTexture->mBitmapInfo.bmHeight;*/

		mDisplayX = mPosition.mX - mWidth * mAnchorX;
		mDisplayY = mPosition.mY - mHeight * mAnchorY;



		mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);
	}
	//mpEngine->DrawCircle(mPosition.mX, mPosition.mY, mRadius);
}

void CUnit::SetTexture(CTexture* tpTexture)
{
	mpTexture = tpTexture;

	mWidth = mpTexture->mBitmapInfo.bmWidth;
	mHeight = mpTexture->mBitmapInfo.bmHeight;
}

void CUnit::SetAnchors(float tAnchorX, float tAnchorY)
{
	mAnchorX = tAnchorX;
	mAnchorY = tAnchorY;
}


void CUnit::Create(CAPIEngine* tpEngine)
{
	SetEngine(tpEngine);
}

void CUnit::Destroy()
{

}



void CUnit::Update(float tDeltaTime)
{
	//프레임 기반 진행
	//현재위치 = 이전위치 + 속도
	//mPosition = mPosition + mVelocity; // 벡터끼리의 덧셈


	//시간 기반 진행 : 여기서 시간은 실제 진행시간을 기반으로 작동한다
	if (mIsActive)
	{
		mPosition = mPosition + mVelocity * tDeltaTime;
	}
}
