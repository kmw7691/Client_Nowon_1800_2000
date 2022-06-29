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



//���ΰ� ��ü�� �Ϲ�źȯ �߻�
void CActor::DoFire(vector<CBullet*>& tBullets)
{
	// źȯ�߻�˰���
	/*
		źȯ�� �߻� ���������� ���Ѵ�
		źȯ�� �߻� �ӵ��� �����Ѵ�
		źȯ�� Ȱ��ȭ�Ѵ�
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
