#pragma once


#include "ryumacro.h"
#include <list>
using namespace std;

class CUnit;


class CCollisionMgr
{
private:
	//모든 유닛에 대해 순회를 해야 한다
	//유닛들을 이 자료구조에 등록하고 해지하는 것이 빈번하다
	//<-- 이러한 특성이 링크드리스트와 적합하다
	//왜냐하면, 링크드리스트는 추가삭제에 걸리는 시간이 O(1)이다
	list<CUnit*> mCollisionUnits;

public:
	void AddUnit(CUnit* t);
	void Update(float tDeltaTime);

private:
	bool DoCollision(CUnit* tThis, CUnit* tOther);



	//싱글턴 패턴 적용
	SINGLETON_DECLARE(CCollisionMgr)
};

