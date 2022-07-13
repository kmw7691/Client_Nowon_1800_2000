#pragma once

#include "SVector2D.h"


#include <list>
using namespace std;


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
		mPosition	= tCollider.mPosition;

		mWidth		= tCollider.mWidth;
		mHeight		= tCollider.mHeight;

		mpObject	= tCollider.mpObject;
	};

	~CCollider()
	{
	};

	void operator=(const CCollider& tCollider)
	{
		mPosition	= tCollider.mPosition;

		mWidth		= tCollider.mWidth;
		mHeight		= tCollider.mHeight;

		mpObject	= tCollider.mpObject;
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

	SVector2D GetPosition() const
	{
		return mPosition;
	}

	//더블링크드리스트이므로 추가,삭제에 걸리는 시간이 일정하다. O(1)
	//mCollisions 에 원소 추가 
	void AddToCollisions(CCollider* tpCollider)
	{
		mCollisions.push_back(tpCollider);
	}
	//mCollisions 에 원소 삭제
	void EraseFromCollisions(CCollider* tpCollider)
	{
		//탐색은 O(n)
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
	//다른 임의의 콜라이더를 검출한다. 
	//만약 이 목록에 있다면 이전에 충돌이 일어나서 여기에 포함해둔 상태인 것이다
	bool DoCheckBeInCollisions(CCollider* tpCollider)
	{
		//탐색, 순회traverse한다 
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


private:
	//사각영역의 충돌체의 중심은 항상 정 가운데라고 가정하겠다.
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	CObjectRyu* mpObject = nullptr;	//이 충돌체의 소유자



	
	//충돌체 목록 정보: 충돌이 어느 시점에 상태인지 검토를 하기 위해 필요하다.
	list<CCollider*> mCollisions;
};

