#include "CActor.h"
#include "CBullet.h"
#include <windows.h>

CActor::CActor()
{
}

CActor::~CActor()
{
}

CActor::CActor(const CActor& t)
{
	*this = t;
}



//주인공 기체의 일반탄환 발사
void CActor::DoFire(vector<CBullet*>& tBullets)
{
	// 탄환발사알고리즘
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/
	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, -1.0f) * 200.0f);
	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"DoFire %d\n", mCurIndexBullet);
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

void CActor::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);

	if (this->mPosition.mX - this->mWidth * 0.5f < 0.0f)
	{
		this->mPosition.mX = 0.0f + this->mWidth * 0.5f;
	}

	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->mPosition.mX = 800.0f - this->mWidth * 0.5f;
	}
}
