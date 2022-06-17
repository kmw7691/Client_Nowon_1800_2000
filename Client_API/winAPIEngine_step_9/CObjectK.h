#pragma once
class CObjectK
{
public:
	CObjectK();
	~CObjectK();


public:
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
