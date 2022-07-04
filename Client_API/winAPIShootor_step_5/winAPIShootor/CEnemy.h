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

	CEnemy(const CEnemy& t);

public:
	//ryu prototype
	virtual CObjectRyu* clone() override
	{
		return new CEnemy(*this);
	}

public:

	virtual void Update(float tDeltaTime) override;

	void DoFire(vector<CBullet*>& tBullets);

	void DoFireAimed(vector<CBullet*>& tBullets, CObjectRyu* tpObject);
	void DoFireCircled(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;

public:
	//delta time 을 누적할 변수
	float mTimeTick = 0.0f;
};

