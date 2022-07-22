#include "CUnit.h"

#include "CAPIEngine.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAniSeq.h"

CUnit::CUnit() : CObjectRyu(), mRadius(30.0f)
{

}
CUnit::~CUnit()
{
	/*if (mpAnimator)
	{
		delete mpAnimator;
		mpAnimator = nullptr;
	}*/
	SAFE_DELETE(mpAnimator);

	/*if (nullptr != mpCollider)
	{
		delete mpCollider;
		mpCollider = nullptr;
	}*/
	SAFE_DELETE(mpCollider);


}

void CUnit::SetVelocity(SVector2D tVelocity)
{
	mVelocity = tVelocity;
}

void CUnit::Create(CAPIEngine* tpEngine)
{
	SetEngine(tpEngine);

	mpCollider = new CCollider();
	//크기는 기본값으로 지정하겠다.
	mpCollider->Create(this->GetPosition(), 100.0f, 100.0f);
	mpCollider->SetOwnerObject(this);


	//mpAnimator->SetOwnerObject(this);

}
void CUnit::Destroy()
{
	/*list<CCollider*>::iterator tItor;
	for (tItor = mColliders.begin(); tItor != mColliders.end(); ++tItor)
	{
		if (nullptr != (*tItor))
		{
			delete (*tItor);
			(*tItor) = nullptr;
		}
	}

	mColliders.clear();*/
	if (nullptr != mpCollider)
	{
		delete mpCollider;
		mpCollider = nullptr;
	}

	if (mpAnimator)
	{
		mpAnimator->Destroy();

		delete mpAnimator;
		mpAnimator = nullptr;
	}

}

void CUnit::Update(float tDeltaTime)
{
	if (mIsActive)
	{
		mPosition = mPosition + mVelocity * tDeltaTime;


		/*for (list<CCollider*>::iterator tItor = mColliders.begin(); tItor != mColliders.end(); ++tItor)
		{
			(*tItor)->Update();
		}*/
		mpCollider->Update();

	}
}
//void CUnit::Render()
//{
//	if (mIsActive)
//	{
//		float tWidth = 0.0f;
//		float tHeight = 0.0f;
//		
//		//ryu_ani_spritesheet_i
//		tWidth = mpTexture->mBitmapInfo.bmWidth;
//		tHeight = mpTexture->mBitmapInfo.bmHeight;
//
//
//
//
//
//		this->mDisplayX = this->mPosition.mX - tWidth * mAnchorX;
//		this->mDisplayY = this->mPosition.mY - tHeight * mAnchorY;
//
//
//
//
//		//mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);
//
//		
//
//		if (nullptr != mpAnimator)
//		{
//			mpAnimator->UpdateAnimation(mpEngine->GetDeltaTime());
//			mpAnimator->Render(mpEngine, mDisplayX, mDisplayY);
//		}
//		else
//		{
//			mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);
//		}
//
//
//		//debug draw
//		mpEngine->DrawCircle(this->mPosition.mX, this->mPosition.mY, this->mRadius);
//	}
//}


void CUnit::Render()
{
	if (mIsActive)
	{
		float tWidth = 0.0f;
		float tHeight = 0.0f;

		
		if (nullptr != mpAnimator)
		{
			mpAnimator->UpdateAnimation(mpEngine->GetDeltaTime());


			//ryu_ani_spritesheet_i
			tWidth = mpAnimator->mpCurAniSeq->mSpriteWidth;
			tHeight = mpAnimator->mpCurAniSeq->mSpriteHeight;
			this->mDisplayX = this->mPosition.mX - tWidth * mAnchorX;
			this->mDisplayY = this->mPosition.mY - tHeight * mAnchorY;


			mpAnimator->Render(mpEngine, mDisplayX, mDisplayY);
		}
		else
		{
			//ryu_ani_spritesheet_i
			tWidth = mpTexture->mBitmapInfo.bmWidth;
			tHeight = mpTexture->mBitmapInfo.bmHeight;
			this->mDisplayX = this->mPosition.mX - tWidth * mAnchorX;
			this->mDisplayY = this->mPosition.mY - tHeight * mAnchorY;

			mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);
		}


		//debug draw
		mpEngine->DrawCircle(this->mPosition.mX, this->mPosition.mY, this->mRadius);
	}
}


void CUnit::SetAnchorPoint(float tXAnchorRatio, float tYAnchorRatio)
{
	mAnchorX = tXAnchorRatio;
	mAnchorY = tYAnchorRatio;
}

void CUnit::SetTexture(CTexture* tpTexture)
{
	mpTexture = tpTexture;


	this->mWidth = mpTexture->mBitmapInfo.bmWidth;
	this->mHeight = mpTexture->mBitmapInfo.bmHeight;




	/*CCollider* tpCollider = nullptr;
	tpCollider = new CCollider();
	tpCollider->Create(this->GetPosition(), this->mWidth, this->mHeight);
	tpCollider->SetOwnerObject(this);
	mColliders.push_back(tpCollider);*/

	//비트맵 이미지 정보를 바탕으로 조정하겠다.
	mpCollider->SetSize(this->mWidth, this->mHeight);
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


void CUnit::SetDefaultAniSeq(const string& tStrDefaultAniSeq)
{
	mpAnimator->SetDefaultAniSeq(tStrDefaultAniSeq);
}

void CUnit::PlayAni(const string& tStrAniSeq)
{
	mpAnimator->PlayAni(tStrAniSeq);
}