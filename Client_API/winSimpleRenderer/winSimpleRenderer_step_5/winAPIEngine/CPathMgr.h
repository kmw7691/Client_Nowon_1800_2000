#pragma once

#include "ryumacro.h"

#include <windows.h>

#include <unordered_map>
using namespace std;


class CPathMgr
{
private:
	//키: 문자열 타입
	//값: 유니코드 문자열 타입 
	unordered_map<string, wstring> mPaths;

public:
	bool Create();

	//임의의 경로를 만드는 함수
	bool MakePath(const string& tStrKey, const wchar_t* tpPath, const string& tStrBaseKey);

//private:
public:
	//Path 검색 
	const wchar_t* FindPath(const string& tStrKey);



SINGLETON_DECLARE(CPathMgr)
};

