#include "CInputMgr.h"
//#include "Kmacro.h"


//static변수이므로 전역공간에서 초기화 표현
//CInputMgr* CInputMgr::mpInstance = nullptr;
//
//CInputMgr* CInputMgr::GetInst()
//{
//	if (nullptr == mpInstance)
//	{
//		mpInstance = new CInputMgr();
//	}
//
//	return mpInstance;
//}
//
//void CInputMgr::ReleaseInst()
//{
//	if (nullptr != mpInstance)
//	{
//		delete mpInstance;
//		//요즘 컴파일러에서는 이 표현도 문법통과
//		//mpInstance = nullptr;
//	}
//}


SINGLETON_DEFINITION(CInputMgr)

CInputMgr::CInputMgr()
{
	//요즘 컴파일러에서는 이 표현도 문법통과
	//mpInstance = nullptr;

	mhWnd = 0;

	mMapKeys.clear();

	mpKeyInfo = nullptr;
}

CInputMgr::~CInputMgr()
{
	unordered_map<string, SKeyInfo*>::const_iterator tItor;

	for (tItor = mMapKeys.begin();tItor != mMapKeys.end();++tItor)
	{
		if (nullptr != tItor->second)
		{
			delete tItor->second;
		}
	}

	mMapKeys.clear();
}

void CInputMgr::Create(HWND hWnd)
{
	mhWnd = hWnd;
}

void CInputMgr::Update()
{
	unordered_map<string, SKeyInfo*>::const_iterator tItor;

	for (tItor = mMapKeys.begin();tItor != mMapKeys.end();++tItor)
	{
		int tPushCount = 0;

		for (int ti = 0;ti < tItor->second->mKeyInputs.size();++ti)
		{
			if (GetAsyncKeyState(tItor->second->mKeyInputs[ti]) & 0X8000)
			{
				++tPushCount;
			}
		}


		if (tPushCount == tItor->second->mKeyInputs.size())
		{
			if (!tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//처음눌린것이다 Down
				tItor->second->mIsDown = true;
			}
			else if (tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//눌리고 잇는 중이다. Press
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = true;
			}
		}
		else // 여기까지왔다면, 현재 눌린상태가 아니라는 것
		{
			if (tItor->second->mIsDown || tItor->second->mIsPress)
			{
				//떼어지고있는중
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = true;
			}
			else if (tItor->second->mIsUp)
			{
				//아무입력도 없는 상태이다
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = false;
			}
		}
	}
}

SKeyInfo* CInputMgr::FindKey(const string& tStrKey) const
{
	//0(1)로 검색
	unordered_map<string, SKeyInfo*>::const_iterator tItor = mMapKeys.find(tStrKey);

	if (tItor == mMapKeys.end())
	{
		return nullptr;
	}

	//first: 키, second : 값(실제데이터)
	return tItor->second;
}

bool CInputMgr::KeyDown(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (nullptr == tpInfo)
	{
		return false;
	}

	return tpInfo->mIsDown;
}

bool CInputMgr::KeyPress(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (nullptr == tpInfo)
	{
		return false;
	}

	return tpInfo->mIsPress;
}

bool CInputMgr::KeyUp(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (nullptr == tpInfo)
	{
		return false;
	}

	return tpInfo->mIsUp;
}
