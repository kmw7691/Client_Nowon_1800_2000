#pragma once


#include "SVector2D.h"

#include "CRef.h"
#include <string>
using namespace std;

class CCollider;

class CObjectRyu: public CRef
{
public:
	CObjectRyu();
	virtual ~CObjectRyu();


public:
	virtual CObjectRyu* clone() = 0;

	void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}
	SVector2D GetPosition() const
	{
		return mPosition;
	}


	virtual void OnEnterCollision(CCollider* tOther) = 0;
	virtual void OnStayCollision(CCollider* tOther) = 0;
	virtual void OnExitCollision(CCollider* tOther) = 0;

	string GetTag() const
	{
		return mTag;
	}
	void SetTag(const string& tTag)
	{
		mTag = tTag;
	}

//public:
protected:
	//��ġ ���� 
	SVector2D mPosition;

	string mTag = "";

};

/*
	OOP���α׷����� 4���� Ư¡


	�߻�ȭ abstraction: �ڵ��� �߻�ȭ + �������� �߻�ȭ ---> �������� �߻�ȭ
	����ȭ encapsulation: Data Hiding 
	��Ӽ� inheritance: ����� Ư���� �θ�Ŭ������ �ΰ� �̸� �̾�޾� �ڽ�Ŭ������ �ۼ��ϴ� ��, ȿ������ ���� 
	������ polymorphysm: ���� �޽����� �ٸ� ����.
		override + virtual + �θ�Ŭ����Ÿ���� ������

*/