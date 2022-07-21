#pragma once

#include "CUnit.h"

#include <vector>
using namespace std;

class CBullet;


class CEnemy:public CUnit
{
public:
	CEnemy();
	virtual ~CEnemy();

	CEnemy(const CEnemy& tActor);


public:
	//k prototype

	virtual CObjectK* clone() override
	{
		return new CEnemy(*this);
	}

public:
	virtual void Update(float tDeltaTime);

	void DoFire(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;

public:
	float mTimeTick = 0.0f;
};

