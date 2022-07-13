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
	//유닛의 위치정보를 받아 위치정보를 갱신( 유닛의 콜라이더이므로 )
	mPosition = mpObject->GetPosition();
}

bool CCollider::DoCollisionAABB(CCollider* tOther)
{
	//this
	float tLeftX	= 0.0f;
	float tRightX	= 0.0f;
	float tTopY		= 0.0f;
	float tBottomY	= 0.0f;

	//사각영역의 충돌체의 중심은 항상 정 가운데라고 가정하겠다.
	//( anchor x, anchor y 값을 0.5로 가정 )

	tLeftX		= mPosition.mX - mWidth * 0.5f;
	tRightX		= mPosition.mX - mWidth * 0.5f + mWidth;
	tTopY		= mPosition.mY - mHeight * 0.5f;
	tBottomY	= mPosition.mY - mHeight * 0.5f + mHeight;


	//other
	float tLeftX_Other		= 0.0f;
	float tRightX_Other		= 0.0f;
	float tTopY_Other		= 0.0f;
	float tBottomY_Other	= 0.0f;

	tLeftX_Other	= tOther->GetPosition().mX - tOther->mWidth * 0.5f;
	tRightX_Other	= tOther->GetPosition().mX - tOther->mWidth * 0.5f + tOther->mWidth;
	tTopY_Other		= tOther->GetPosition().mY - tOther->mHeight * 0.5;
	tBottomY_Other	= tOther->GetPosition().mY - tOther->mHeight * 0.5f + tOther->mHeight;




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