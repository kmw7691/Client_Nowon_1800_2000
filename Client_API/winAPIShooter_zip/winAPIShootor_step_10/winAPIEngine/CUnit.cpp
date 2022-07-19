#include "CUnit.h"
#include "CAnimator.h"
#include "CAPIEngine.h"
#include "CTexture.h"

//초기화목록 을 이용하여 초기화함
//CUnit::CUnit(): mX(400.0f), mY(500.0f), mRadius(30.0f)
CUnit::CUnit() : CObjectRyu(), mRadius(30.0f), mVelocity()
{

}
CUnit::~CUnit()
{
	if (nullptr != mpCollider)
	{
		delete mpCollider;
		mpCollider = nullptr;
	}
}


void CUnit::Create(CAPIEngine* tpEngine)
{
	SetEngine(tpEngine);

	mpCollider = new CCollider();
	//크기는 기본값으로 지정하겠다.
	mpCollider->Create(this->GetPosition(), 100.0f, 100.0f);
	mpCollider->SetOwnerObject(this);
}
void CUnit::Destroy()
{
	if (nullptr != mpCollider)
	{
		delete mpCollider;
		mpCollider = nullptr;
	}
}



void CUnit::Update(float tDeltaTime)
{
	if (mIsActive)
	{
		mPosition = mPosition + mVelocity * tDeltaTime;

		mpCollider->Update();
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
		
		if (nullptr != mpAnimator)
		{
			mpAnimator->UpdateAnimation(mpEngine->GetDeltaTime());
			mpAnimator->Render(mpEngine, mDisplayX, mDisplayY);
		}

		else
		{
			mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);
		}
		



		//debug draw
		//mpEngine->DrawCircle(mPosition.mX, mPosition.mY, mRadius);
	}
}



void CUnit::SetTexture(CTexture* tpTexture)
{
	mpTexture = tpTexture;


	mWidth = mpTexture->mBitmapInfo.bmWidth;
	mHeight = mpTexture->mBitmapInfo.bmHeight;



	mpCollider->SetSize(this->mWidth, this->mHeight);

}

void CUnit::SetAnchors(float tAnchorX, float tAnchorY)
{
	mAnchorX = tAnchorX;
	mAnchorY = tAnchorY;
}

CAnimator* CUnit::CreateAnimation(const string& tId, CAPIEngine* tpEngine)
{
	mpAnimator = new CAnimator();

	mpAnimator->SetId(tId);
	if (!mpAnimator->Create(tpEngine))
	{
		return nullptr;
	}

	return mpAnimator;
}

void CUnit::DestroyAnimation()
{
	if (mpAnimator)
	{
		mpAnimator->Destroy();
	}

	if (mpAnimator)
	{
		delete mpAnimator;
		mpAnimator = nullptr;
	}
}
