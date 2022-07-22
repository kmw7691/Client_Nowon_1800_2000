#include "CPathMgr.h"
#include "framework.h"


SINGLETON_DEFINITION(CPathMgr)

CPathMgr::CPathMgr()
{
	mPaths.clear();
}

CPathMgr::~CPathMgr()
{
	mPaths.clear();
}

bool CPathMgr::Create()
{
	//실행 파일이 있는 경로룰 얻겠다
	//(현재 실행파일을 기준으로 디렉토리(폴더)를 포함한 전체경로를 얻는다)

	wchar_t tStrPath[MAX_PATH] = { 0 };

	GetModuleFileName(nullptr, tStrPath, MAX_PATH);

	WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath);
	OutputDebugString(szTemp);


	return true;
}

bool CPathMgr::MakePath(const string& tStrKey, const wchar_t* tpPath, const string& tStrBaseKey)
{
	return true;
}

const wchar_t* CPathMgr::FindPath(const string& tStrKey)
{
	return nullptr;
}
