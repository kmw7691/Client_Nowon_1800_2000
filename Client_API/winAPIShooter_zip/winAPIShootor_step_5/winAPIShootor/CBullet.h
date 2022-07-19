#pragma once

#include "CUnit.h"


class CBullet: public CUnit
{

public:
	CBullet();
	virtual ~CBullet();

	CBullet(const CBullet& t);

public:
	//ryu prototype
	virtual CObjectRyu* clone() override
	{
		return new CBullet(*this);
	}
};

