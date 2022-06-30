#include "CUnit.h"
#include "CAPIEngine.h"
#include "CTexture.h"

// �ʱ�ȭ����� �̿��Ͽ� �ʱ�ȭ��
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
	//������ ��� ����
	//������ġ = ������ġ + �ӵ�
	//mPosition = mPosition + mVelocity; // ���ͳ����� ����


	//�ð� ��� ���� : ���⼭ �ð��� ���� ����ð��� ������� �۵��Ѵ�
	if (mIsActive)
	{
		mPosition = mPosition + mVelocity * tDeltaTime;
	}
}
