#pragma once

#include "ryumacro.h"

#include <list>
using namespace std;

class CUnit;

class CCollisionMgr
{
private:
	list<CUnit*> mCollisionUnits;

public:
	void AddUnit(CUnit* t);
	void Update(float tDeltaTime);

private:
	bool DoCollision(CUnit* tThis, CUnit* tOther);

	SINGLETON_DECLARE(CCollisionMgr)

};

