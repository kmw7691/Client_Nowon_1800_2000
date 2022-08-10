#pragma once

#include <windows.h>

/*
	비트맵 이미지 데이터를 다루는 클래스

*/
class CTexture
{
public:
	HDC mhDCMem;
	HBITMAP mhBitmap;
	HBITMAP mhOldBitmap;

	BITMAP mBitmapInfo;		//비트맵 인포


public:
	CTexture();
	~CTexture();
	


	bool LoadTexture(HINSTANCE hInst, HDC hDC, const wchar_t* tpFileName);

	bool CreateBackBuffer(HINSTANCE hInst, HDC hDC);

};

