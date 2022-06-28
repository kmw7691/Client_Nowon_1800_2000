#pragma once
#include "CUnit.h"

class CBullet: public CUnit
{
public:
	CBullet();
	virtual ~CBullet();

	CBullet(const CBullet& tActor);


public:
	//k prototype

	virtual CObjectK* clone() override
	{
		return new CBullet(*this);
	}
};

