#pragma once

#include "CObjectK.h"


class CAPIEngine;
class CTexture;



class CUnit: public CObjectK
{
public:
	CUnit();
	virtual ~CUnit();
	// 복사생성자
	CUnit(const CUnit& tUnit)
	{
		mX = tUnit.mX;
		mY = tUnit.mY;
		mRadius = tUnit.mRadius;
	}
	//복사대입연산자
	void operator=(const CUnit& tUnit)
	{
		mX = tUnit.mX;
		mY = tUnit.mY;
		mRadius = tUnit.mRadius;

	}

public:
	void Render(CAPIEngine* tpEngine);
	void SetTexture(CTexture* tpTexture);


	void SetAnchors(float tAnchorX = 0.5f, float tAnchorY = 0.5f);

public:
	//연속적인 2차원세계를 가정
	float mX = 0.0f;
	float mY = 0.0f;

	//반지름
	float mRadius = 0.0f;

	CTexture* mpTexture = nullptr;



	//pivot
	float mAnchorX = 0.5f;
	float mAnchorY = 0.5f;


	float mDisplayX = 0.0f;
	float mDisplayY = 0.0f;


	float mWidth = 0.0f;
	float mHeight = 0.0f;


};

