#pragma once


class CAPIEngine;


class CUnit
{
public:
	CUnit();
	~CUnit();
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

public:
	//연속적인 2차원세계를 가정
	float mX = 0.0f;
	float mY = 0.0f;

	//반지름
	float mRadius = 0.0f;
};

