#pragma once

#include "CUnit.h"

class CSelect : public CUnit
{
public:
	CSelect()
	{

	}
	virtual ~CSelect()	//가상소멸자 
	{

	}
	CSelect(const CSelect& t) :CUnit(t)
	{

	}

	void operator=(const CSelect& t)
	{
		CUnit::operator=(t);
	}

public:
	virtual CObjectRyu* clone() override
	{
		return new CSelect(*this);
	};
};

