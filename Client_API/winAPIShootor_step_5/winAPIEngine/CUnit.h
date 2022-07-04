#pragma once


//
#include "CObjectRyu.h"


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
		mpTexture = t.mpTexture;
		mpEngine = t.mpEngine;

		mIsActive = t.mIsActive;

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



	bool Intersects(const CUnit& tOther) const
	{
		//this
		float tLeftX			= 0.0f;
		float tRightX			= 0.0f;
		float tTopY				= 0.0f;
		float tBottomY			= 0.0f;


		tLeftX					= mPosition.mX - mWidth * mAnchorX;
		tRightX					= mPosition.mX - mWidth * mAnchorX + mWidth;
		tTopY					= mPosition.mY - mHeight * mAnchorY;
		tBottomY				= mPosition.mY - mHeight * mAnchorY + mHeight;


		//other
		float tLeftX_Other		= 0.0f;
		float tRightX_Other		= 0.0f;
		float tTopY_Other		= 0.0f;
		float tBottomY_Other	= 0.0f;

		tLeftX_Other			= tOther.GetPosition().mX - tOther.mWidth * tOther.mAnchorX;
		tRightX_Other			= tOther.GetPosition().mX - tOther.mWidth * tOther.mAnchorX + tOther.mWidth;
		tTopY_Other				= tOther.GetPosition().mY - tOther.mHeight * tOther.mAnchorY;
		tBottomY_Other			= tOther.GetPosition().mY - tOther.mHeight * tOther.mAnchorY + tOther.mHeight;




		if (tRightX < tLeftX_Other)
		{
			return false;
		}

		if (tLeftX > tRightX_Other)
		{
			return false;
		}

		if (tBottomY < tTopY_Other)
		{
			return false;
		}

		if (tTopY > tBottomY_Other)
		{
			return false;
		}

		return true;
	}

	//ryu prototype
public:
	virtual CObjectRyu* clone() = 0;
	

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
};

