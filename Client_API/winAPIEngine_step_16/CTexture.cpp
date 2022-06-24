#include "CTexture.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
    //이전에 사용하던 비트맵 도구를 다시 현재 비트맵도구로 설정하고
    SelectObject(mhDCMem, mhOldBitmap);
    //현재 사용하던 비트맵도구는 이제 해제한다
    DeleteObject(mhBitmap);

    //DC도 해제한다
    DeleteDC(mhDCMem);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC thDC, LPCWSTR tFileName)
{
    mhDCMem = CreateCompatibleDC(thDC);

    //설정할 비트맵도구를 생성
    //여기서는 파일에서 로드하며 만드는 것을 가정
    mhBitmap = (HBITMAP)LoadImage(hInst, tFileName,//TEXT("resources/bongbong_0.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    //위에서 생성한 비트맵도구를 현재 비트맴도구로 설정한다
    //리턴값으로는 이전에 사용하던 비트맵도구가 리턴된다
    mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

    //비트맵 도구의 핸들을 이용
    //BITMAP info 정보를 얻는다
    mBitmapInfo;
    GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);


	return true;
}

bool CTexture::CreateBackBuffer(HINSTANCE hIUnst, HDC thDC)
{
    mhDCMem = CreateCompatibleDC(thDC);

    //현재화면DC와 호환되는 비트맵 이미지를 만드는 함수
    mhBitmap = CreateCompatibleBitmap(thDC, 800, 600);

    mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

    mBitmapInfo;
    GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);



    return true;
}
