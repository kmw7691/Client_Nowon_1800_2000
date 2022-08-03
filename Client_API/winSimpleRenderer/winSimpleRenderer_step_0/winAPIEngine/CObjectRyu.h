#pragma once

#include "SVector2D.h"
#include "CRef.h"

#include <string>
using namespace std;

class CAPIEngine;
class CCollider;

class CObjectRyu: public CRef
{
public:
	CObjectRyu();
	virtual ~CObjectRyu();

protected:
	SVector2D mPosition;

	CAPIEngine* mpEngine = nullptr;


	string mTag = "";


public:
	inline SVector2D GetPosition() const
	{
		return mPosition;
	}

	inline void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}
	

	void SetEngine(CAPIEngine* tpEngine);


	string GetTag() const
	{
		return mTag;
	}
	void SetTag(string tTag)
	{
		mTag = tTag;
	}



public:
	virtual CObjectRyu* clone() = 0;


	
	virtual void OnEnterCollision(CCollider* tOther) = 0;

	virtual void OnStayCollision(CCollider* tOther) = 0;
	virtual void OnExitCollision(CCollider* tOther) = 0;

};

