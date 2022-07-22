#include "CInputMgr.h"






SINGLETON_DEFINITION(CInputMgr)
//CInputMgr* CInputMgr::mpInstance = nullptr;

CInputMgr::CInputMgr()
{
	mhWnd = 0;

	mMapKeys.clear();

	mpKeyInfo = nullptr;
}
CInputMgr::~CInputMgr()
{
}



void CInputMgr::Create(HWND hWnd)
{
	mhWnd = hWnd;

}

void CInputMgr::Update()
{
	unordered_map<string, SKeyInfo*>::iterator tItor;

	for (tItor = mMapKeys.begin(); tItor != mMapKeys.end(); ++tItor)
	{
		int tPushCount = 0;

		//키입력이 여러개임을 고려
		for (int ti = 0; ti < tItor->second->mKeyInputs.size(); ++ti)
		{
			// 0x8000 이전에 눌림없음, 호출당시에 눌림있음
			if (GetAsyncKeyState(tItor->second->mKeyInputs[ti]) & 0x8000)
			{
				++tPushCount;
			}
		}


		//if (1 <= tPushCount) //==
		//키입력이 여러개임을 고려, 키조합의 키갯수만큼, 즉 키조합 입력에 대해 
		if( tPushCount == tItor->second->mKeyInputs.size() )
		{
			if (!tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//처음 눌린 것이다
				tItor->second->mIsDown = true;
			}
			else if (tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//눌리고 있는 중이다
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = true;
			}
		}
		else
		{
			if (tItor->second->mIsDown || tItor->second->mIsPress)
			{
				//떼어진 것이다
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = true;
			}
			else if (tItor->second->mIsUp)
			{
				//이제 아무 입력도 없는 것이다
				tItor->second->mIsUp = false;
			}
		}
	}


}



bool CInputMgr::KeyDown(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (!tpInfo)
	{
		return false;
	}

	return tpInfo->mIsDown;
}
bool CInputMgr::KeyPress(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (!tpInfo)
	{
		return false;
	}

	return tpInfo->mIsPress;
}
bool CInputMgr::KeyUp(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (!tpInfo)
	{
		return false;
	}

	return tpInfo->mIsUp;
}
