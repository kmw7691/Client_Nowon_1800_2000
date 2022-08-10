#pragma once

#include "ryumacro.h"

#include <windows.h>

#include <unordered_map>
using namespace std;

class CTexture;
class CAPIEngine;

class CResourcesMgr
{
private:
	//텍스쳐(이미지 데이터)들을 관리하기 위한 자료구조
	//키: 문자열 타입
	//값: CTexture객체의 주소값
	unordered_map<string, CTexture*> mTexs;

	CAPIEngine* mpEngine = nullptr;

public:

	void Create(CAPIEngine* tpEngine);

	CTexture* FindTexture(const string& tStrKey);

	//tStrKey: 해당 텍스쳐 데이터의 검색 키, 문자열 타입 
	//tpFileName: 해당 텍스쳐 데이터(이미지 데이터)가 담긴 파일이름, 유니코드를 고려한 C 스타일 문자열
	//tStrPathKey: 파일 경로 의 키, 문자열 타입 
	CTexture* LoadTexture(const string& tStrKey, const wchar_t* tpFileName, const string& tStrPathKey);



	SINGLETON_DECLARE(CResourcesMgr)
};

