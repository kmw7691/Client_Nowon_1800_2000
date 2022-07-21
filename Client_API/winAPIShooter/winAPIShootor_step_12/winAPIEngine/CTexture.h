#pragma once

#include <windows.h>

/*
	비트맵을 다루는 클래스 
*/

class CTexture
{

public:

	HDC mhDCMem;

	HBITMAP mhBitmap;

	HBITMAP mhOldBitmap;
	BITMAP mBitmapInfo;



public:
	CTexture();
	~CTexture();


	bool LoadTexture(HINSTANCE hInst, HDC thDC, LPCWSTR tFileName);

	bool CreateBackBuffer(HINSTANCE hInst, HDC thDC);
};

