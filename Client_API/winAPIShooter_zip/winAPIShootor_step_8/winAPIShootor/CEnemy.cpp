#include "CEnemy.h"

#include "CBullet.h"
#include <windows.h>

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
	//탄환 발사 알고리즘 
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/
	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);
	tBullets[mCurIndexBullet]->SetIsActive(true);


	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFire %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	//탄환의 연사
	if (mCurIndexBullet < tBullets.size() - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}

void CEnemy::DoFireAimed(vector<CBullet*>& tBullets, CObjectRyu* tpObject)
{
	//탄환 발사 알고리즘 
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/
	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());


	//임의의 크기의 해당 방향의 벡터 구하기 = 목적지점 - 시작지점
	SVector2D tStartP = this->GetPosition();
	SVector2D tTargetP = tpObject->GetPosition();


	SVector2D tVector = tTargetP - tStartP;

	//순수한 방향 벡터를 구한다( 크기가 1인 단위벡터 )
	SVector2D tUnitVector = tVector.Normalize();		//정규화

	float tScalarSpeed = 200.0f;		//속력을 정함
	SVector2D tVelocity = tUnitVector * tScalarSpeed;	//속도를 구함. 벡터의 스칼라곱

	tBullets[mCurIndexBullet]->SetVelocity(tVelocity);
	//tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);
	
	
	
	
	tBullets[mCurIndexBullet]->SetIsActive(true);


	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFire Aimed %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	//탄환의 연사
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
	//탄환 발사 알고리즘 
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/

	for (int ti = 0; ti < 8; ++ti)
	{
		tBullets[ti]->SetPosition(this->GetPosition());

		//원형탄의 속도(벡터)를 결정하자 
		//원형탄의 각각의 축에 속력을 설정
		//'순수한 방향벡터'를 구하자( 크기는 1 )
		float tAngleDegree = 45.0f * ti;
		float tDirX = 1.0f*cosf(tAngleDegree*(3.14159f/180.0f));
		float tDirY = 1.0f*sinf(tAngleDegree * (3.14159f / 180.0f));

		tBullets[ti]->SetVelocity(SVector2D(tDirX, tDirY)*200.0f);

		tBullets[ti]->SetIsActive(true);
	}

}

void CEnemy::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);

	//왼쪽 경계
	if (this->mPosition.mX - this->mWidth * 0.5f < 0.0f)
	{
		this->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}
	//오른쪽 경계
	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->SetVelocity(SVector2D(-1.0f, 0.0f) * 100.0f);
	}
}