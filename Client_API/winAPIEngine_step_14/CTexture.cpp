#include "CTexture.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
    //������ ����ϴ� ��Ʈ�� ������ �ٽ� ���� ��Ʈ�ʵ����� �����ϰ�
    SelectObject(mhDCMem, mhOldBitmap);
    //���� ����ϴ� ��Ʈ�ʵ����� ���� �����Ѵ�
    DeleteObject(mhBitmap);

    //DC�� �����Ѵ�
    DeleteDC(mhDCMem);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC thDC, LPCWSTR tFileName)
{
    mhDCMem = CreateCompatibleDC(thDC);

    //������ ��Ʈ�ʵ����� ����
    //���⼭�� ���Ͽ��� �ε��ϸ� ����� ���� ����
    mhBitmap = (HBITMAP)LoadImage(hInst, tFileName,//TEXT("resources/bongbong_0.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    //������ ������ ��Ʈ�ʵ����� ���� ��Ʈ�ɵ����� �����Ѵ�
    //���ϰ����δ� ������ ����ϴ� ��Ʈ�ʵ����� ���ϵȴ�
    mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

    //��Ʈ�� ������ �ڵ��� �̿�
    //BITMAP info ������ ��´�
    mBitmapInfo;
    GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);


	return true;
}

bool CTexture::CreateBackBuffer(HINSTANCE hIUnst, HDC thDC)
{
    mhDCMem = CreateCompatibleDC(thDC);

    //����ȭ��DC�� ȣȯ�Ǵ� ��Ʈ�� �̹����� ����� �Լ�
    mhBitmap = CreateCompatibleBitmap(thDC, 800, 600);

    mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

    mBitmapInfo;
    GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);



    return true;
}
