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
		// 참조카운트를 하나씩 증가한다
		++mRef;
	}

	int Release()
	{
		//참조를 하나씩 줄여준다
		--mRef;

		//최종적으로 참조카운트가 0이되면 메모리를 해제하고 참조카운트0을 리턴한다
		if (0 == mRef)
		{
			delete this;
			return 0;
		}

		return mRef;
	}
};

