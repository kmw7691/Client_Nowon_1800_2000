#include "CAPIEngine.h"

//#include "Resource.h"

#include "CTexture.h"

#include "CInputMgr.h"
#include "CCollisionMgr.h"




//HINSTANCE CAPIEngine::hInst = nullptr;


CAPIEngine::CAPIEngine()
{
    memset(szWindowClass, 0, MAX_LOADSTRING*sizeof(WCHAR));            // �⺻ â Ŭ���� �̸��Դϴ�.
    memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));                // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
}
CAPIEngine::~CAPIEngine()
{

}


BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow)
{

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    /*LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIENGINESTEP0, szWindowClass, MAX_LOADSTRING);*/
    wsprintf(szTitle, L"winAPIEngine");
    wsprintf(szWindowClass, L"winAPIEngineWC");

    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


	return TRUE;
}
MSG CAPIEngine::Run()
{
	MSG msg = { 0 };




    mhDC = GetDC(mhWnd);

    mpBackBuffer = new CTexture();
   /* mpBackBuffer->LoadTexture(hInst, mhDC, TEXT("resources/backbuffer_0.bmp"));*/
    mpBackBuffer->CreateBackBuffer(hInst, mhDC);
        
    CInputMgr::GetInst();
    CCollisionMgr::GetInst();


    OnCreate();


    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));
    //HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));


    //ryu deltatime
    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);


    while (WM_QUIT != msg.message)
    {
        //PeekMessage
        //������ �޽��� ť�� �޽����� ������ �������� true �� �����Ѵ�
        //������ �޽��� ť�� �޽����� ������ �׳� false�� �����Ѵ�( �ͺ� )
        //
        //PM_REMOVE ������ �޽��� ť���� �޽����� ���� ���, �ش� �޽����� ť���� �����Ѵ�
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //DeltaTime( �� �����ӿ� �ɸ��� �ð� ) �� ���Ѵ�
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);

            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

            mTime = tTime;



            CCollisionMgr::GetInst()->Update(mDeltaTime);

            //���ӷ��������� �⺻ ������ �ۼ��Ͽ���.
            //OutputDebugString(L"game loop\n");
            OnUpdate(mDeltaTime);
        }
    }



    OnDestroy();

    CCollisionMgr::GetInst()->ReleaseInst();
    CInputMgr::GetInst()->ReleaseInst();


    if (nullptr != mpBackBuffer)
    {
        delete mpBackBuffer;
        mpBackBuffer = nullptr;
    }


    ReleaseDC(mhWnd, mhDC);


    //return (int)msg.wParam;

	return msg;
}


void CAPIEngine::OnCreate()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::Create\n");
    OutputDebugString(szTemp);

}
void CAPIEngine::OnDestroy()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::Destroy\n");
    OutputDebugString(szTemp);
}
void CAPIEngine::OnUpdate(float tDeltaTime)
{
    //WCHAR szTemp[256] = { 0 };
    //wsprintf(szTemp, L"CAPIEngine::OnUpdate\n");
    //OutputDebugString(szTemp);
}






//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;         //lpfnWndProc�� �����Լ��� �Լ��������̴�.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPIENGINESTEP0));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPIENGINESTEP0);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    /*HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);*/
    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }

    //Ŭ���̾�Ʈ ������ ũ�⸦ �̰����� �� ���̴�.
    RECT tRect = { 0, 0, 800, 600 };    
    //Ÿ��Ʋ��, �޴� ���� ����Ͽ� ��ü ������ ������ �ٽ� ������ش�.
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);
    //������ ����� ���� ������, ������ ũ��� ��ġ�� �ٽ� �����Ѵ�.
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);




    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}


//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK CAPIEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
   
    //������ ������� ���, ȭ�鿡 �׸� �ʿ伺�� �ִٸ�, �� �޽����� ���´�.
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        //DC ( Device Context )�� handle: DC�� �׸��⿡ ����Ѵ� ��ġ( ��ġ, ��ġ�� ���õ� ������, ��ġ�� ����) �� �߻�ȭ�س��� ���̴�.
        HDC hdc = BeginPaint(hWnd, &ps);    //�׸��� ��带 �����ϰھ�
       
        EndPaint(hWnd, &ps);    //�׸��� ��尡 �����ٴ� �ǹ�
    }
    break;
    case WM_TIMER:
    {
        OutputDebugString(L">>>>>>WM_TIMER Enemy DoFire~!!!!!\n");
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
//INT_PTR CALLBACK CAPIEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}


void CAPIEngine::DrawCircle(float tX, float tY, float tRadius)
{
    //Ellipse(mhDC, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
    Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
}

void CAPIEngine::DrawTexture(float tX, float tY, CTexture* tpTexture, COLORREF tColorKey)
{
    //BitBlt(this->mpBackBuffer->mhDCMem,//�޸�dc
    //    tX, tY,
    //    tpTexture->mBitmapInfo.bmWidth, tpTexture->mBitmapInfo.bmHeight,
    //    tpTexture->mhDCMem,//�޸� DC
    //    0, 0, SRCCOPY);

    TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTexture->mBitmapInfo.bmWidth, tpTexture->mBitmapInfo.bmHeight,
        tpTexture->mhDCMem,

        0, 0,
        tpTexture->mBitmapInfo.bmWidth, tpTexture->mBitmapInfo.bmHeight,
        RGB(255, 255, 255)); // white
}

void CAPIEngine::DrawTexturePartial(float tX, float tY, CTexture* tpTex, int tRow, int tCol, int tIndex, COLORREF tColorKey)
{
    int tSrcWidth = tpTex->mBitmapInfo.bmWidth / tCol;
    int tSrcHeight = tpTex->mBitmapInfo.bmHeight / tRow;


    int tCurRow = tIndex / tCol;
    int tCurCol = tIndex % tCol;

    int tSrcX = tCurCol * tSrcWidth;
    int tSrcY = tCurRow * tSrcHeight;

    TransparentBlt(this->mpBackBuffer->mhDCMem,

        tX, tY,
        tSrcWidth, tSrcHeight,

        tpTex->mhDCMem,

        tSrcX, tSrcY,
        tSrcWidth, tSrcHeight,

        tColorKey);
}


void CAPIEngine::Clear(float tR, float tG, float tB)
{
    //Rectangle(mhDC, 0, 0, 800, 600);
    //Rectangle(mpBackBuffer->mhDCMem, 0, 0, 800, 600);


     //������ ���� ������ ���������ϴ�. 
    HPEN hPen;  //���ο� ���ڵ�
    HPEN hPenOld;//������ ���� ���ڵ� ����

    HBRUSH hBrush;  //���ο� �귯�� �ڵ�
    HBRUSH hBrushOld;   //������ ���� �귯�� �ڵ� ����

    //�����θ� �� �׸���
    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR * 255, tG * 255, tB * 255));   //RGB��ũ�δ� 256�ܰ��� ������ �䱸�Ѵ�
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255));	// �� ��Ÿ��, ����, ����
    //hbr = (HBRUSH)GetStockObject(NULL_BRUSH);	//���� ä���� ������ �Ѵٸ� �̰�����
    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);


        Rectangle(thDC, 0, 0, 800, 600);


    hBrush = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPen = (HPEN)::SelectObject(thDC, hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPIEngine::Present()
{
    BitBlt(mhDC,//���� dc
        0, 0,
        800, 600,
        mpBackBuffer->mhDCMem,
        0, 0,
        SRCCOPY);
}