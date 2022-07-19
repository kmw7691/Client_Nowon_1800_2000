#pragma once

#include "CObjectK.h"


class CAPIEngine;
class CTexture;



class CUnit: public CObjectK
{
public:
	CUnit();
	virtual ~CUnit();
	// ���������
	CUnit(const CUnit& tUnit)
	{
		mX = tUnit.mX;
		mY = tUnit.mY;
		mRadius = tUnit.mRadius;
	}
	//������Կ�����
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
	//�������� 2�������踦 ����
	float mX = 0.0f;
	float mY = 0.0f;

	//������
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

