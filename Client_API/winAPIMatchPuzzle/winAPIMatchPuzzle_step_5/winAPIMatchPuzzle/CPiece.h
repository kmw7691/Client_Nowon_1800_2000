#pragma once

#include "CUnit.h"


class CPiece: public CUnit
{
public:
	CPiece()
	{

	}
	virtual ~CPiece()	//가상소멸자 
	{

	}
	CPiece(const CPiece& t):CUnit(t)
	{

	}

	void operator=(const CPiece& t)
	{
		CUnit::operator=(t);
	}

public:
	virtual CObjectRyu* clone() override
	{
		return new CPiece(*this);
	};
};

