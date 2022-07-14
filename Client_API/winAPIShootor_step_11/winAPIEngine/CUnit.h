#pragma once


//
#include "CObjectRyu.h"
#include "CAnimator.h"
#include "CCollider.h"

class CAnimator;
class CAPIEngine;
class CTexture;
//
class CUnit: public CObjectRyu
{
public:
	CUnit();
	virtual ~CUnit();	//

	//복사생성자
	CUnit(const CUnit& t)
	{
		//CObjectRyu
		mPosition = t.mPosition;

		//CUnit
		mRadius = t.mRadius;


		mAnchorX = t.mAnchorX;
		mAnchorY = t.mAnchorY;

		mDisplayX = t.mDisplayX;
		mDisplayY = t.mDisplayY;

		mWidth = t.mWidth;
		mHeight = t.mHeight;

		mVelocity = t.mVelocity;

		//shallow copy
		//mpTexture, mpEngine은 공유자원이므로 
		mpTexture = t.mpTexture;
		mpEngine = t.mpEngine;

		mIsActive = t.mIsActive;

		//deep copy
		//콜라이더는 유닛마다 가지는 자원이므로 
		mpCollider = new CCollider();
		(*mpCollider) = (*t.mpCollider);

		mpCollider->SetOwnerObject(this);


		mTag = t.mTag;

		if(nullptr != t.mpAnimator)
		{
			//deep copy
			mpAnimator = new CAnimator();
			(*mpAnimator) = (*t.mpAnimator);

			mpAnimator->SetOwnerObject(this);
		}
	}
	//복사대입연산자
	void operator=(const CUnit& t)
	{
		//CObjectRyu
		mPosition = t.mPosition;

		//CUnit
		mRadius = t.mRadius;


		mAnchorX = t.mAnchorX;
		mAnchorY = t.mAnchorY;

		mDisplayX = t.mDisplayX;
		mDisplayY = t.mDisplayY;

		mWidth = t.mWidth;
		mHeight = t.mHeight;

		mVelocity = t.mVelocity;

		//shallow copy
		mpTexture = t.mpTexture;
		mpEngine = t.mpEngine;

		mIsActive = t.mIsActive;

		//deep copy
		//콜라이더는 유닛마다 가지는 자원이므로 
		mpCollider = new CCollider();
		(*mpCollider) = (*t.mpCollider);

		mpCollider->SetOwnerObject(this);

		mTag = t.mTag;


		if (nullptr != t.mpAnimator)
		{
			//deep copy
			mpAnimator = new CAnimator();
			(*mpAnimator) = (*t.mpAnimator);

			mpAnimator->SetOwnerObject(this);
		}
		
	}
public:
	//void Render();

	virtual void Create(CAPIEngine* tpEngine);
	virtual void Destroy();

	virtual void Update(float tDeltaTime);
	virtual void Render();






	void SetTexture(CTexture* tpTexture);

	void SetAnchors(float tAnchorX = 0.5f, float tAnchorY = 0.5f);



	void SetVelocity(SVector2D tVelocity)
	{
		mVelocity = tVelocity;
	}
	SVector2D GetVelocity() const
	{
		return mVelocity;
	}

	/*void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}
	SVector2D GetPosition() const
	{
		return mPosition;
	}*/

	//void Update();

	void SetEngine(CAPIEngine* tpEngine)
	{
		mpEngine = tpEngine;
	}

	void SetIsActive(bool tIsActive)
	{
		mIsActive = tIsActive;
	}
	bool GetIsActive() const
	{
		return mIsActive;
	}

	void SetRadius(float tRadius)
	{
		mRadius = tRadius;
	}
	float GetRadius() const
	{
		return mRadius;
	}



	

	//ryu prototype
public:
	virtual CObjectRyu* clone() = 0;
	

	virtual void OnEnterCollision(CCollider* tOther) override {};
	virtual void OnStayCollision(CCollider* tOther) override {};
	virtual void OnExitCollision(CCollider* tOther) override {};

	//땜빵
	void SetColliderPosition()
	{
		mpCollider->SetPosition(this->GetPosition());
	}

public:	
	//반지름
	float mRadius = 0.0f;

	//pivot
	float mAnchorX = 0.5f;
	float mAnchorY = 0.5f;

	float mDisplayX = 0.0f;
	float mDisplayY = 0.0f;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	SVector2D mVelocity;

	CTexture* mpTexture = nullptr;
	CAPIEngine* mpEngine = nullptr;

	//활성 여부 
	bool mIsActive = false;


public:
	//충돌체는 하나라고 가정하겠다. ( 물론 여러개를 만들 수도 있다 )
	CCollider* mpCollider = nullptr;


public:
	CAnimator* mpAnimator = nullptr;


public:
	CAnimator* CreateAnimation(const string& tId, CAPIEngine* tpEngine);
	void DestroyAnimation();
};

