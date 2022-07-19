#include "CInputMgr.h"
//#include "Kmacro.h"


//static�����̹Ƿ� ������������ �ʱ�ȭ ǥ��
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
//		//���� �����Ϸ������� �� ǥ���� �������
//		//mpInstance = nullptr;
//	}
//}


SINGLETON_DEFINITION(CInputMgr)

CInputMgr::CInputMgr()
{
	//���� �����Ϸ������� �� ǥ���� �������
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
				//ó���������̴� Down
				tItor->second->mIsDown = true;
			}
			else if (tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//������ �մ� ���̴�. Press
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = true;
			}
		}
		else // ��������Դٸ�, ���� �������°� �ƴ϶�� ��
		{
			if (tItor->second->mIsDown || tItor->second->mIsPress)
			{
				//���������ִ���
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = true;
			}
			else if (tItor->second->mIsUp)
			{
				//�ƹ��Էµ� ���� �����̴�
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = false;
			}
		}
	}
}

SKeyInfo* CInputMgr::FindKey(const string& tStrKey) const
{
	//0(1)�� �˻�
	unordered_map<string, SKeyInfo*>::const_iterator tItor = mMapKeys.find(tStrKey);

	if (tItor == mMapKeys.end())
	{
		return nullptr;
	}

	//first: Ű, second : ��(����������)
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
