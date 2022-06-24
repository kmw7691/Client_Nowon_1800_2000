#pragma once

#include"CUnit.h"

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
};

