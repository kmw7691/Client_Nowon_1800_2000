#include "CCollider.h"

#include "CObjectRyu.h"

bool CCollider::DoCollision(CCollider* tColliderOther)
{
	bool tResult = false;

	tResult = DoCollisionAABB(tColliderOther);

	return tResult;
}

void CCollider::Create(SVector2D tPosition, float tWidth, float tHeight)
{
	mPosition = tPosition;

	mWidth = tWidth;
	mHeight = tHeight;
}
void CCollider::Update()
{
	mPosition = mpObject->GetPosition();
}


bool CCollider::DoCollisionAABB(CCollider* tOther)
{
	float tLeftX = 0.0f;
	float tRightX = 0.0f;
	float tTopY = 0.0f;
	float tBottomY = 0.0f;

	tLeftX = mPosition.mX - mWidth * 0.5f;
	tRightX = mPosition.mX - mWidth * 0.5f + mWidth;
	tTopY = mPosition.mY - mHeight * 0.5f;
	tBottomY = mPosition.mY - mHeight * 0.5f + mHeight;


	float tLeftX_Other = 0.0f;
	float tRightX_Other = 0.0f;
	float tTopY_Other = 0.0f;
	float tBottomY_Other = 0.0f;

	tLeftX_Other = tOther->mPosition.mX - tOther->mWidth * 0.5f;
	tRightX_Other = tOther->mPosition.mX - tOther->mWidth * 0.5f + tOther->mWidth;
	tTopY_Other = tOther->mPosition.mY - tOther->mHeight * 0.5f;
	tBottomY_Other = tOther->mPosition.mY - tOther->mHeight * 0.5f + tOther->mHeight;


	if (tRightX < tLeftX_Other)
	{
		return false;
	}

	if (tLeftX > tRightX_Other)
	{
		return false;
	}

	if (tBottomY < tTopY_Other)
	{
		return false;
	}

	if (tTopY > tBottomY_Other)
	{
		return false;
	}

	return true;
}