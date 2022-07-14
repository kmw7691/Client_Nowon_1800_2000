#pragma once

#include "CUnit.h"
#include <windows.h>

#include <vector>
using namespace std;

class CBullet;

class CEnemy:public CUnit
{

public:
	CEnemy();
	virtual ~CEnemy();

	CEnemy(const CEnemy& t);

public:
	//ryu prototype
	virtual CObjectRyu* clone() override
	{
		return new CEnemy(*this);
	}
	//엔진부에서 충돌검출을 수행하고
	//다형성을 이용해서 
	//응용프로그램 레벨에서는 원하는 CUnit계통의 클래스에서 
	//OnEnterCollision, OnStayCollision, OnExitCollision등을 상황에 맞게 정의하여 사용하면 된다.
	virtual void OnEnterCollision(CCollider* tOther) override 
	{
		if (tOther->GetOwnerObject()->GetTag() == "tagActorBullet")
		{
			OutputDebugString(L"CEnemy::OnEnterCollision\n");

			/*this->SetIsActive(false);
			((CUnit*)tOther->GetOwnerObject())->SetIsActive(false);*/
		}
	}

	virtual void OnExitCollision(CCollider* tOther) override
	{
		if (tOther->GetOwnerObject()->GetTag() == "tagActorBullet")
		{
			OutputDebugString(L"CEnemy::OnExitCollision\n");

			this->SetIsActive(false);
			((CUnit*)tOther->GetOwnerObject())->SetIsActive(false);
		}
	}




public:

	virtual void Update(float tDeltaTime) override;

	void DoFire(vector<CBullet*>& tBullets);

	void DoFireAimed(vector<CBullet*>& tBullets, CObjectRyu* tpObject);
	void DoFireCircled(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;

public:
	//delta time 을 누적할 변수
	float mTimeTick = 0.0f;
};

