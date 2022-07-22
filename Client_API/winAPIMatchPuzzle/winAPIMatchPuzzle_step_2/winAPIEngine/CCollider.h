#pragma once


#include "SVector2D.h"

class CObjectRyu;


#include <list>
using namespace std;

class CCollider
{
public:
	CCollider():
		mPosition(), mWidth(0.0f), mHeight(0.0)
	{
	};
	CCollider(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;

		//원한다면 이렇게 표현도 가능, 물론 주의해야함. shallow copy
		//*this = tCollider;
	};

	~CCollider()
	{
	};


	void operator=(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;

		//원한다면 이렇게 표현도 가능, 물론 주의해야함. shallow copy
		//*this = tCollider;
	}


public:
	//충돌체 간 충돌 처리 함수 
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
	CObjectRyu* GetOwnerObject() const
	{
		return mpObject;
	}


	void AddToCollisions(CCollider* tpCollider)
	{
		mCollisions.push_back(tpCollider);
	}
	void EraseFromCollisions(CCollider* tpCollider)
	{
		list<CCollider*>::iterator tItor;
		for (tItor = mCollisions.begin(); tItor != mCollisions.end(); ++tItor)
		{
			if (*tItor == tpCollider)
			{
				mCollisions.erase(tItor);
				break;
			}
		}
	}
	bool DoCheckBeInCollisions(CCollider* tpCollider)
	{
		list<CCollider*>::iterator tItor;
		for (tItor = mCollisions.begin(); tItor != mCollisions.end(); ++tItor)
		{
			if (*tItor == tpCollider)
			{
				return true;
			}
		}

		return false;
	}



private:
	//
	//축정렬경계상자를 가정하여 작성하겠다.
	bool DoCollisionAABB(CCollider* tOther);

	//원한다면 원 충돌체를 가정한 것도 만들 수 있겠다.


	


private:
	
	//사각영역의 충돌체의 중심은 항상 정 가운데라고 가정하겠다.
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;


	CObjectRyu* mpObject = nullptr;	//이 충돌체의 소유자


	//충돌정보
	list<CCollider*> mCollisions;
};

