#include "CEnemy.h"
#include "CBullet.h"
#include <Windows.h>

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

CEnemy::CEnemy(const CEnemy& t)
{
	*this = t;
}


void CEnemy::DoFire(vector<CBullet*>& tBullets)
{
	// 탄환발사알고리즘
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/
	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, 1.0f) * 200.0f);
	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFire %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	if (mCurIndexBullet < tBullets.size() - 1)
	{
		mCurIndexBullet++;
	}

	else
	{
		mCurIndexBullet = 0;
	}
}

void CEnemy::DoFireAimed(vector<CBullet*>& tBullets, CObjectK* tpObject)
{
	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());


	//임의의 크기의 해당 방향의 벡터구하기 = 목적지점 - 시작지점
	SVector2D tStartP = this->GetPosition();
	SVector2D tTargetP = tpObject->GetPosition();


	SVector2D tVector = tTargetP - tStartP;

	//순수한 방향 벡터를 구한다(크기가 1인벡터)
	SVector2D tUnitVector = tVector.Normalize();  // 정규화

	float tScalarSpeed = 200.0f;  // 속력을 구함
	SVector2D tVelocity = tUnitVector * tScalarSpeed; // 속도를구함, 벡터의 스칼라곱


	tBullets[mCurIndexBullet]->SetVelocity(tVelocity);
	//tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, 1.0f) * 200.0f);


	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFire %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	if (mCurIndexBullet < tBullets.size() - 1)
	{
		mCurIndexBullet++;
	}

	else
	{
		mCurIndexBullet = 0;
	}
}



void CEnemy::DoFireCircled(vector<CBullet*>& tBullets)
{
	for (int ti = 0; ti < 8; ++ti)
	{
		tBullets[ti]->SetPosition(this->GetPosition());




		tBullets[ti]->SetIsActive(true);
	}
}



void CEnemy::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);


	//왼쪽경계
	if (this->mPosition.mX - this->mWidth * 0.5f < 0.0f)
	{
		this->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}
	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->SetVelocity(SVector2D(-1.0f, 0.0f) * 100.0f);
	}
}