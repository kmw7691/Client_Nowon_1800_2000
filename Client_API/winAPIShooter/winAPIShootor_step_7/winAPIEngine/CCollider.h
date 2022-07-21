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
	//�����İ����ڸ� �����Ͽ� �ۼ�
	bool DoCollisionAABB(CCollider* tOther);


private:
	//�簢������ �浹ü�� �߽��� �׻� �� ������ �����Ѵ�
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	CObjectRyu* mpObject = nullptr; // �� �浹ü�� ������
};

