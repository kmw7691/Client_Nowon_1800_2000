#pragma once
class CRef
{
public:
	CRef();
	virtual ~CRef();

protected:
	int mRef;

public:
	void AddRef()
	{
		++mRef;
	}

	int Release()
	{
		--mRef;

		if (0 == mRef)
		{
			delete this;
			return 0;
		}

		return mRef;
	}
};

