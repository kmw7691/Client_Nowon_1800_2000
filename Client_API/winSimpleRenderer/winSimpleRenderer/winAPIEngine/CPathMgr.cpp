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

	/*WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath);
	OutputDebugString(szTemp);*/


	int tCount = lstrlen(tStrPath); // 문자열의 길이를 구한다
	for (int ti = tCount - 1; ti >= 0; --ti)
	{
		// "/" 전통적인 폴더 구분자
		// "\\" 윈도우에서의 폴더구분자
		if ('/' == tStrPath[ti] || '\\' == tStrPath[ti])
		{
			//다음 이라고 가정하고 살펴보자
			//				c"\ryu\t.exe
			//
			//문자의 총갯수는 12개
			// 첫인덱스는 0, 마지막인덱스는 11
			//뒤에서부터 검사해서 처음 발견한 \ 는 인덱스 6
			// 6 + 1 = 7 인덱스 문자부터
			// MAX_PATH(260)  -  (6+1)



			//메모리 설정 함수 : 임의의 값으로 해당 메모리를 채운다
			memset(tStrPath + (ti + 1), 0, sizeof(wchar_t) * (MAX_PATH - (ti + 1)));

			break;
		}
	}

	WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath);
	OutputDebugString(szTemp);


	//실행 파일이 있는 전체경로를 ROOT_PATH로 등록하였다
	mPaths.insert(make_pair(ROOT_PATH, tStrPath));



	return true;
}

bool CPathMgr::MakePath(const string& tStrKey, const wchar_t* tpPath, const string& tStrBaseKey)
{
	const wchar_t* tpBasePath = FindPath(tStrBaseKey);

	if (!tpBasePath)
	{
		return false;
	}

	wstring tStrPath;

	if (tpBasePath)
	{
		tStrPath = tpBasePath; // 형변환 c스타일 문자열 --> wstring 타입
	}


	tStrPath = tStrPath + tpPath + L'\\';


	WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath.c_str());
	OutputDebugString(szTemp);


	mPaths.insert(make_pair(tStrKey, tStrPath));


	return true;
}

const wchar_t* CPathMgr::FindPath(const string& tStrKey)
{
	unordered_map<string, wstring>::iterator tItor;

	tItor = mPaths.find(tStrKey);

	if (mPaths.end() == tItor)
	{
		return nullptr;
	}


	//c스타일 문자열을 리턴
	return tItor->second.c_str();
}
