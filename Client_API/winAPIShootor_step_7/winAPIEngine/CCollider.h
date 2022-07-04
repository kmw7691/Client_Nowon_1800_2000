#pragma once
#include "SVector2D.h"

class CObjectRyu;

class CCollider
{
public:
	CCollider() :
		mPosition(), mWidth(0.0f), mHeight(0.0)
	{
	};

	CCollider(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;
	}

	~CCollider()
	{
	};

	void operator=(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;
	}



	bool DoCollision(CCollider* tColliderOther);

	void Create(SVector2D tPosition, float tWidth, float tHeight);
	void Update();



	void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}

	void SetSize(float tWidth, float tHeight)
	{
		mWidth = tWidth;
		mHeight = tHeight;
	}

	void SetOwnerObject(CObjectRyu* tpObject)
	{
		mpObject = tpObject;
	}

	CObjectRyu* GetOwnerObeject() const
	{
		return mpObject;
	}

	SVector2D GetPosition() const
	{
		return mPosition;
	}


private:
	//축정렬경계상자를 가정하여 작성
	bool DoCollisionAABB(CCollider* tOther);


private:
	//사각영역의 충돌체의 중심은 항상 정 가운데라고 가정한다
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	CObjectRyu* mpObject = nullptr; // 이 충돌체의 소유자
};

