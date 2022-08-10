#include "CResourcesMgr.h"

//
#include "CTexture.h"
#include "CPathMgr.h"
#include "CAPIEngine.h"


SINGLETON_DEFINITION(CResourcesMgr)


CResourcesMgr::CResourcesMgr()
{
	mTexs.clear();
}

CResourcesMgr::~CResourcesMgr()
{
	//텍스쳐 메모리들을 해제한다
	//텍스쳐 자원은 공유데이터이므로 여기서 한꺼번에 해제하도록 의도했다. 
	unordered_map<string, CTexture*>::iterator tItor;
	for (tItor = mTexs.begin();tItor != mTexs.end();++tItor)
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

	//이미 등록되어 있는 텍스쳐 리소스라면 찾은 것을 바로 리턴 
	if (tpTex)
	{
		return tpTex;
	}


	// mpTexUISelect = new CTexture();
	//mpTexUISelect->LoadTexture(hInst, mhDC, L"resources/select_0.bmp");

	//등록된 것이 아니라면
	//파일에서 이미지 데이터를 로드하여 가져와 등록 하고 리턴 
	tpTex = new CTexture();

	const wchar_t* tszTemp = nullptr;
	tszTemp = CPathMgr::GetInstance()->FindPath(tStrPathKey);
	wstring tString = tszTemp;
	tString += tpFileName;

	tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), tString.c_str());


	mTexs.insert(make_pair(tStrKey, tpTex));

	return tpTex;
}