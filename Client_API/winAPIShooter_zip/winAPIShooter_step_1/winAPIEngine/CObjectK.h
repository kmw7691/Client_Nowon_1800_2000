#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObjectK:public CRef
{
public:
	CObjectK();
	virtual ~CObjectK();

public:
	virtual CObjectK* clone() = 0;



//public:
protected:
	//��ġ����
	SVector2D mPosition;

	/*

	// ���� ī���� ����
	//int mRef = 0;

	//void AddRef()
	//{
	//	// ����ī��Ʈ�� �ϳ��� �����Ѵ�
	//	++mRef;
	//}
	//
	//int Release()
	//{
	//	//������ �ϳ��� �ٿ��ش�
	//	--mRef;

	//	//���������� ����ī��Ʈ�� 0�̵Ǹ� �޸𸮸� �����ϰ� ����ī��Ʈ0�� �����Ѵ�
	//	if (0 == mRef)
	//	{
	//		delete this;
	//		return 0;
	//	}

	//	return mRef;
	//}
	*/

	// OOP���α׷����� 4���� Ư¡
	/*
		OOP���α׷����� 4���� Ư¡

		�߻�ȭ	abstraction		: �ڵ��� �߻�ȭ + �������� �߻�ȭ -> �������� �߻�ȭ
		����ȭ	encapsulation	: Data Hiding
		��Ӽ�	inheritance		: ����� Ư����	�θ�Ŭ������ �ΰ� �̸� �̾�޾� �ڽ�Ŭ������ �ۼ��ϴ� ��, ȿ������ ����
		������	polymorphysm	: ���� �޽����� �ٸ� ����.
									override + virtual + �θ�Ŭ����Ÿ���� ������
	*/
};

