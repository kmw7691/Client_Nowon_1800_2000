#pragma once

#include"CUnit.h"
#include <vector>
using namespace std;

class CBullet;


class CActor: public CUnit
{
public:
	CActor();
	virtual ~CActor();

	CActor(const CActor& tActor);


public:
	//k prototype

	virtual CObjectK* clone() override
	{
		return new CActor(*this);
	}

public:
	void DoFire(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;
};

