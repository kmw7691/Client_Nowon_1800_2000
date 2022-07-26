#pragma once
#include "SVector2D.h"


class CObjectK
{
public:
	CObjectK();
	~CObjectK();


public:
	//��ġ����
	SVector2D mPosition;



	// ���� ī���� ����
	int mRef = 0;

	void AddRef()
	{
		// ����ī��Ʈ�� �ϳ��� �����Ѵ�
		++mRef;
	}
	
	int Release()
	{
		//������ �ϳ��� �ٿ��ش�
		--mRef;

		//���������� ����ī��Ʈ�� 0�̵Ǹ� �޸𸮸� �����ϰ� ����ī��Ʈ0�� �����Ѵ�
		if (0 == mRef)
		{
			delete this;
			return 0;
		}

		return mRef;
	}
};
