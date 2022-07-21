#pragma once

#include <windows.h>

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

	bool CreateBackBuffer(HINSTANCE hIUnst, HDC  thDC);
};

