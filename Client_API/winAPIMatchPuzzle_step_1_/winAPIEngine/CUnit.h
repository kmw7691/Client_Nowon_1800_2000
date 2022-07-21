#pragma once

#include "CObjectRyu.h"

#include "CCollider.h"

#include "CAnimator.h"

#include <list>
using namespace std;

class CAPIEngine;
class CTexture;
class CCollider;
class CAnimator;

class CUnit: public CObjectRyu
{
public:
	CUnit();
	virtual ~CUnit(); 

	CUnit(const CUnit& tUnit)
	{
		mPosition.mX = tUnit.mPosition.mX;
		mPosition.mY = tUnit.mPosition.mY;
		mRadius = tUnit.mRadius;

		mpEngine = tUnit.mpEngine;

		mIsActive = tUnit.mIsActive;

		
		mpCollider = new CCollider();
		(*mpCollider) = (*tUnit.mpCollider);

		mpCollider->SetOwnerObject(this);




		mTag = tUnit.mTag;


		//mpAnimator = tUnit.mpAnimator;

		if (nullptr != tUnit.mpAnimator)
		{
			mpAnimator = new CAnimator();
			(*mpAnimator) = (*tUnit.mpAnimator);

			mpAnimator->SetOwnerObject(this);
		}


	}

	void operator=(const CUnit& tUnit)
	{
		mPosition.mX = tUnit.mPosition.mX;
		mPosition.mY = tUnit.mPosition.mY;
		mRadius = tUnit.mRadius;

		mpEngine = tUnit.mpEngine;

		mIsActive = tUnit.mIsActive;


		mpCollider = new CCollider();
		(*mpCollider) = (*tUnit.mpCollider);

		mpCollider->SetOwnerObject(this);



		mTag = tUnit.mTag;

	}

public:
	
	void SetVelocity(SVector2D tVelocity);


	virtual void Create(CAPIEngine* tpEngine);
	virtual void Destroy();

	virtual void Update(float tDeltaTime);
	virtual void Render();

	void SetAnchorPoint(float tXAnchorRatio = 0.5f, float tYAnchorRatio = 0.5f);
	void SetTexture(CTexture* tpTexture);

	void SetIsActive(bool tIsAlive)
	{
		mIsActive = tIsAlive;
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

	

	virtual CObjectRyu* clone() = 0;


	virtual void OnEnterCollision(CCollider* tOther) override {};
	virtual void OnStayCollision(CCollider* tOther) override {};
	virtual void OnExitCollision(CCollider* tOther) override {};


	void SetDefaultAniSeq(const string& tStrDefaultAniSeq);
	void PlayAni(const string& tStrAniSeq);



protected:
	SVector2D mVelocity;


	float mRadius = 0.0f;

	float mAnchorX = 0.5f;
	float mAnchorY = 0.5f;

	float mDisplayX = 0.0f;
	float mDisplayY = 0.0f;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	CTexture* mpTexture = nullptr;

	//
	bool mIsActive = false;

//test를 위해 public
public:
	//충돌체는 하나라고 가정하겠다. ( 물론 여러개를 만들 수도 있다 )
	//list<CCollider*> mColliders;
	CCollider* mpCollider = nullptr;


public:
	CAnimator* mpAnimator = nullptr;

public:
	CAnimator* CreateAnimation(const string& tId, CAPIEngine* tpEngine);
	void DestroyAnimation();


};

