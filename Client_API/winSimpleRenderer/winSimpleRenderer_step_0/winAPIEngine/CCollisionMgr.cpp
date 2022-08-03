#include "CCollisionMgr.h"



#include "CUnit.h"

#include <windows.h>


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

		for (/*tItor_0 = mCollisionUnits.begin()*/; tItor_0 != mCollisionUnits.end(); ++tItor_0)
		{
			if ((*tItor)->GetIsActive() && (*tItor_0)->GetIsActive())
			{
				DoCollision((*tItor), (*tItor_0));
			}
		}

		//mCollisionUnits.clear();

	}

	
}


bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* tOther)
{
	//CUnit에 설정되어 있는 collider들을 가져온다
	CCollider* tpThis = tThis->mpCollider;
	CCollider* tpOther = tOther->mpCollider;


	bool tIsCollision = false;
	
	bool tRyu = tpThis->DoCollision(tpOther);
	if (tRyu)
	{
		//현재 충돌 상태이다.
		tIsCollision = true;

			bool tIsBe = tpThis->DoCheckBeInCollisions(tpOther);
			//처음 충돌하는것이다
			if (!tIsBe)
			{
				tpThis->AddToCollisions(tpOther);
				tpOther->AddToCollisions(tpThis);

				//OutputDebugString(L"Enter Collision\n");

				//활성화된 경우에만 호출하면 더욱 좋겠다.
				tpThis->GetOwnerObject()->OnEnterCollision(tpOther);
				tpOther->GetOwnerObject()->OnEnterCollision(tpThis);

			}
			else//충돌중인 것이다
			{
				////OutputDebugString(L"Stay Collision\n");
			}
	}
	else if (tpThis->DoCheckBeInCollisions(tpOther) )	//충돌이 끝난 것이다 
	{
		tpThis->EraseFromCollisions(tpOther);
		tpOther->EraseFromCollisions(tpThis);

		//OutputDebugString(L"Exit Collision\n");

		//활성화된 경우에만 호출하면 더욱 좋겠다.
		tpThis->GetOwnerObject()->OnExitCollision(tpOther);
		tpOther->GetOwnerObject()->OnExitCollision(tpThis);
	}
		

	return false;

}



//bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* tOther)
//{
//	//CUnit에 설정되어 있는 collider들을 가져온다
//	const list<CCollider*>* tpThis = tThis->GetCollider();
//	const list<CCollider*>* tpOther = tOther->GetCollider();
//
//	
//
//	list<CCollider*>::const_iterator tItorThis;
//	list<CCollider*>::const_iterator tItorOther;
//
//
//	bool tIsCollision = false;
//
//	for (tItorThis = tpThis->begin(); tItorThis != tpThis->end(); ++tItorThis)
//	{
//		for (tItorOther = tpOther->begin(); tItorOther != tpOther->end(); ++tItorOther)
//		{
//
//			bool tRyu = (*tItorThis)->DoCollision((*tItorOther));
//			if (tRyu)
//			{
//				tIsCollision = true;
//
//
//				bool tIsBe = (*tItorThis)->DoCheckBeInCollisions(*tItorOther);
//				
//				//처음 충돌하는것이다
//				if (!tIsBe)
//				{
//					(*tItorThis)->AddToCollisions(*tItorOther);
//					(*tItorOther)->AddToCollisions(*tItorThis);
//
//					OutputDebugString(L"Enter Collision");
//				}
//				else//충돌중인 것이다
//				{
//					OutputDebugString(L"Stay Collision");
//
//				}
//			}
//			else if( (*tItorThis)->DoCheckBeInCollisions(*tItorOther) )	//충돌이 끝난 것이다 
//			{
//				(*tItorThis)->EraseFromCollisions(*tItorOther);
//				(*tItorOther)->EraseFromCollisions(*tItorThis);
//
//				OutputDebugString(L"Exit Collision");
//
//			}
//		}
//	}
//
//
//
//
//	return false;
//
//}
