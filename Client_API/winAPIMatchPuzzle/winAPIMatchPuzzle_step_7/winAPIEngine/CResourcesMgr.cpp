#include "CResourcesMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CAPIEngine.h"

SINGLETON_DEFINITION(CResourcesMgr)

CResourcesMgr::CResourcesMgr()
{
	mTexs.clear();
}


CResourcesMgr::~CResourcesMgr()
{
	//�ؽ��� �޸𸮵��� �����Ѵ�
	//�ؽ��� �ڿ��� ���������� �̹Ƿ� ���⼭ �Ѳ����� ��ü�ϵ��� �ǵ��ߴ�
	unordered_map<string, CTexture*>::iterator tItor;
	for (tItor = mTexs.begin(); tItor != mTexs.end(); ++tItor)
	{
		SAFE_DELETE(tItor->second);
	}

	mTexs.clear();
}

void CResourcesMgr::Create(CAPIEngine* tpEngine)
{
	mpEngine = tpEngine;
}

CTexture* CResourcesMgr::FindTexture(const string& tStrKey)
{
	unordered_map<string, CTexture*>::iterator tItor;

	tItor = mTexs.find(tStrKey);

	if (mTexs.end() == tItor)
	{
		return nullptr;
	}


	return tItor->second;
}

CTexture* CResourcesMgr::LoadTexture(const string& tStrKey, const wchar_t* tpFileName, const string& tStrPathKey)
{
	CTexture* tpTex = FindTexture(tStrKey);

	if (tpTex)
	{
		return tpTex;
	}

	tpTex = new CTexture();

	const wchar_t * tszTemp = nullptr;
	
	tszTemp = CPathMgr::GetInstance()->FindPath(tStrPathKey);
	wstring tString = tszTemp;
	tString += tpFileName;

	tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), tString.c_str());


	mTexs.insert(make_pair(tStrKey, tpTex));


	return tpTex;
}