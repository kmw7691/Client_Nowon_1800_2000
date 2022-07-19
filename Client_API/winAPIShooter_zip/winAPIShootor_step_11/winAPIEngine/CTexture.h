#pragma once

#include <windows.h>

/*
	��Ʈ���� �ٷ�� Ŭ���� 
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

