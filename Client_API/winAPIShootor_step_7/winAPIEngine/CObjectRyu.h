#pragma once


#include "SVector2D.h"

#include "CRef.h"

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


//public:
protected:
	//��ġ ���� 
	SVector2D mPosition;

};

/*
	OOP���α׷����� 4���� Ư¡


	�߻�ȭ abstraction: �ڵ��� �߻�ȭ + �������� �߻�ȭ ---> �������� �߻�ȭ
	����ȭ encapsulation: Data Hiding 
	��Ӽ� inheritance: ����� Ư���� �θ�Ŭ������ �ΰ� �̸� �̾�޾� �ڽ�Ŭ������ �ۼ��ϴ� ��, ȿ������ ���� 
	������ polymorphysm: ���� �޽����� �ٸ� ����.
		override + virtual + �θ�Ŭ����Ÿ���� ������

*/