#pragma once
class CRef
{



//public:
protected:
	int mRef = 0;

public:
	CRef():mRef(0)
	{
	}
	virtual ~CRef()
	{
	}

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

