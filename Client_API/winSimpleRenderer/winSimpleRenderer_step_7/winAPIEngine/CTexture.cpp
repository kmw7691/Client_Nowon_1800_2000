#include "CTexture.h"

CTexture::CTexture(): mhDCMem(NULL)
{

}
CTexture::~CTexture()
{
	//이전에 사용하던 비트맵 도구를 다시 현재 비트맵 도구로 설정하고 
	SelectObject(mhDCMem, mhOldBitmap);
	//현재 사용하던 비트맵 도구는 이제 해제한다
	DeleteObject(mhBitmap);

	//DC도 해제한다
	DeleteDC(mhDCMem);

	//화면 DC는 Release이지만 ( 지우면 안됨 )
	//이것은 메모리 DC이므로 해제한다
}


bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const wchar_t* tpFileName)
{
	//다음의 과정을 거쳐 비트맵을 로드하자
	//window api가 제공하는 기능을 이용한다

	//memory dc 를 만든다
	mhDCMem = CreateCompatibleDC(hDC);

	//설정할 비트맵도구를 생성한다. 
	//여기서는 파일에서 로드하여 만드는 것을 가정하고 있다
	mhBitmap = (HBITMAP)LoadImage(hInst, tpFileName, 
		IMAGE_BITMAP, 
		0, 0, 
		LR_LOADFROMFILE);

	//위에서 생성한 비트맵 도구를 현재 비트맵 도구로 설정한다
	//리턴값으로는 이전에 사용하던 비트맵 도구가 리턴된다 
	mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

	//비트맵 도구의 핸들을 이용하여 
	//BITMAP info 정보를 얻는다 
	GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);

	return TRUE;
}



bool CTexture::CreateBackBuffer(HINSTANCE hInst, HDC hDC)
{
	//memory dc 를 만든다
	mhDCMem = CreateCompatibleDC(hDC);

	//DDB

	//직접 데이터를 설정하여 생성 
	//다음 함수를 사용하면 DC에 호환되는 DDB를 바로 만들어준다. (편의성이 좋다)
	mhBitmap = (HBITMAP)CreateCompatibleBitmap(hDC, 800, 600);//hDC에 nullptr을 넣어도 같음



	//위에서 생성한 비트맵 도구를 현재 비트맵 도구로 설정한다
	//리턴값으로는 이전에 사용하던 비트맵 도구가 리턴된다 
	mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

	//비트맵 도구의 핸들을 이용하여 
	//BITMAP info 정보를 얻는다 
	GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);


	return TRUE;
}
