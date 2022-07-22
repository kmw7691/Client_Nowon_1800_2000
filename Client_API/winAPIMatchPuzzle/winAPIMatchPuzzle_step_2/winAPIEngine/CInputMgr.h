#pragma once


#include <windows.h>

#include <vector>
#include <unordered_map>
#include <string>

#include <typeinfo>

#include "ryumacro.h"


using namespace std;

struct SKeyInfo
{
	string mStrName;			//키
	vector<DWORD> mKeyInputs;		//데이터
	//DWORD mKeyInput;					//데이터


	bool mIsDown;
	bool mIsPress;
	bool mIsUp;

	SKeyInfo()
		:mIsDown(false), mIsPress(false), mIsUp(false)
	{
		mStrName = "";
		mKeyInputs.clear();
	}
};


class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)


private:
	HWND mhWnd;

	//해쉬테이블을 만든 것이다. O(1)의 접근이 가능
	unordered_map<string, SKeyInfo*> mMapKeys;

	SKeyInfo* mpKeyInfo = nullptr;

public:
	virtual void Create(HWND hWnd);
	void Update();


	SKeyInfo* FindKey(const string& tStrKey) const
	{
		unordered_map<string, SKeyInfo*>::const_iterator tItor =
			mMapKeys.find(tStrKey);

		if (tItor == mMapKeys.end())
		{
			return nullptr;
		}

		return tItor->second;
	}


	bool KeyDown(const string& tStrKey) const;
	bool KeyPress(const string& tStrKey) const;
	bool KeyUp(const string& tStrKey) const;


	template<typename T>
	bool AddKey(const T& tData)
	{
		const char* tpType = typeid(T).name();

		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0)
		{
			//키 등록
			//DWORD로 변환
			mpKeyInfo->mKeyInputs.push_back((DWORD)tData);
		}
		else
		{
			//추상화 이름 등록 
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(
				make_pair(mpKeyInfo->mStrName, mpKeyInfo)
			);
		}

		return true;
	}



	template<typename T, typename... Types>
	bool AddKey(const T& tData, const Types&... arg)
	{
		if (!mpKeyInfo)
		{
			mpKeyInfo = new SKeyInfo();
		}

		const char* tpType = typeid(T).name();

		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0)
		{
			//키 등록
			//DWORD로 변환
			mpKeyInfo->mKeyInputs.push_back((DWORD)tData);
		}
		else
		{
			//추상화 이름 등록 
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(
				make_pair(mpKeyInfo->mStrName, mpKeyInfo)
			);
		}

		//재귀적으로 호출 recursive case
		AddKey(arg...);


		//여기까지 오면 재귀호출이 끝난 것이다 
		if (mpKeyInfo)
		{
			mpKeyInfo = nullptr;
		}

		return true;
	}

	
};

