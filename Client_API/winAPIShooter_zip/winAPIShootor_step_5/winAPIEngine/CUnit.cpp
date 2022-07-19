#include "CUnit.h"

#include "CAPIEngine.h"
#include "CTexture.h"

//초기화목록 을 이용하여 초기화함
//CUnit::CUnit(): mX(400.0f), mY(500.0f), mRadius(30.0f)
CUnit::CUnit() : CObjectRyu(), mRadius(30.0f), mVelocity()
{

}
CUnit::~CUnit()
{

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
	if (mIsActive)
	{
		mPosition = mPosition + mVelocity * tDeltaTime;
	}
}


void CUnit::Render()
{
	if (mIsActive)
	{
		/*mWidth = mpTexture->mBitmapInfo.bmWidth;
		mHeight = mpTexture->mBitmapInfo.bmHeight;*/

		mDisplayX = mPosition.mX - mWidth * mAnchorX;
		mDisplayY = mPosition.mY - mHeight * mAnchorY;

		mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);



		//debug draw
		//mpEngine->DrawCircle(mPosition.mX, mPosition.mY, mRadius);
	}
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
