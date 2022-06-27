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


	//CObjectK
	//mPosition = t.mPosition;

	////CUnit
	//mRadius = t.mRadius;



	//
	// mAnchorX = t.mAnchorX;
	// mAnchorY = t.mAnchorY;


	// mDisplayX = t.mDisplayX;
	// mDisplayY = t.mDisplayY;


	// mWidth = t.mWidth;
	// mHeight = t.mHeight;


	// mVelocity = t.mVelocity;

	// //shallow copy
	//mpTexture = t.mpTexture;
	//mpEngine = t.mpEngine;
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
