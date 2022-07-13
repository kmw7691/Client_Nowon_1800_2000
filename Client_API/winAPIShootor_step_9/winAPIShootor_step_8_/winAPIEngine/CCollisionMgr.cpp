#include "CCollisionMgr.h"

#include "CUnit.h"

#include <windows.h>


//싱글턴 패턴 적용
SINGLETON_DEFINITION(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::AddUnit(CUnit* t)
{
	mCollisionUnits.push_back(t);
}

void CCollisionMgr::Update(float tDeltaTime)
{
	if (mCollisionUnits.size() < 2)
	{
		return;
	}

	list<CUnit*>::iterator tItor;
	for (tItor = mCollisionUnits.begin(); tItor != mCollisionUnits.end(); ++tItor)
	{
		list<CUnit*>::iterator tItor_0 = tItor;
		++tItor_0;

		for (; tItor_0 != mCollisionUnits.end(); ++tItor_0)
		{
			if ((*tItor)->GetIsActive() && (*tItor_0)->GetIsActive())
			{
				DoCollision(*tItor, *tItor_0);
			}
		}

	}
}


bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* tOther)
{
	//CUnit에 설정되어 있는 collider들을 가져온다
	CCollider* tpThis	= tThis->mpCollider;
	CCollider* tpOther	= tOther->mpCollider;


	bool tRyu = tpThis->DoCollision(tpOther);
	if (tRyu)
	{		
		//OutputDebugString(L"collision\n");
		bool tIsBe = tpThis->DoCheckBeInCollisions(tpOther);		
		if (!tIsBe)	
		{
			//충돌이 현재 된 상태인데, 충돌체 목록에는 아직 등록되지 않았다
			//--> 처음 충돌이 되고 있는 중이다.

			tpThis->AddToCollisions(tpOther);
			tpOther->AddToCollisions(tpThis);

			//OutputDebugString(L"Enter Collision\n");

			/*tThis->SetIsActive(false);
			tOther->SetIsActive(false);*/
			tpThis->GetOwnerObject()->OnEnterCollision(tpOther);
			tpOther->GetOwnerObject()->OnEnterCollision(tpThis);

		}
		else
		{
			//충돌이 현재 된 상태인데, 충돌체 목록에 이미 등록되어 있다.
			//--> 충돌 중이다.

			//OutputDebugString(L"Stay Collision\n");
			tpThis->GetOwnerObject()->OnStayCollision(tpOther);
			tpOther->GetOwnerObject()->OnStayCollision(tpThis);
		}

		//return true;
	}
	else if (tpThis->DoCheckBeInCollisions(tpOther))
	{
		//현재는 충돌상태가 아니지만, 이전에는 충돌이었다.
		//-->충돌이 끝나고 있는 상태이다.

		tpThis->EraseFromCollisions(tpOther);
		tpOther->EraseFromCollisions(tpThis);

		//OutputDebugString(L"Exit Collision\n");

		tpThis->GetOwnerObject()->OnExitCollision(tpOther);
		tpOther->GetOwnerObject()->OnExitCollision(tpThis);

		/*tThis->SetIsActive(false);
		tOther->SetIsActive(false);*/
	}



	return false;
}
