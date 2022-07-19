#pragma once


class CAPIEngine;


class CUnit
{
public:
	CUnit();
	~CUnit();
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

public:
	//�������� 2�������踦 ����
	float mX = 0.0f;
	float mY = 0.0f;

	//������
	float mRadius = 0.0f;
};

