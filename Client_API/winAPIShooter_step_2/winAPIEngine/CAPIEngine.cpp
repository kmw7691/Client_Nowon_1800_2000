#include "CAPIEngine.h"

#include "CTexture.h"
#include "CInputMgr.h"


CAPIEngine::CAPIEngine()
{
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));

    memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
}

CAPIEngine::~CAPIEngine()
{
}

BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow)
{
    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

   // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
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

void CAPIEngine::onCreate()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::Create\n");
    OutputDebugString(szTemp);
}

void CAPIEngine::onDestroy()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::Destroy\n");
    OutputDebugString(szTemp);
}

void CAPIEngine::onUpdate(float tDeltaTime)
{
    /*WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::OnUpdate\n");
    OutputDebugString(szTemp);*/
}



MSG CAPIEngine::Run()
{
    MSG msg = { 0 };




    mhDC = GetDC(mhWnd);


    mpBackBuffer = new CTexture();
    //mpBackBuffer->LoadTexture(hInst, mhDC, TEXT("resources/backbuffer_0.bmp"));


    mpBackBuffer->CreateBackBuffer(hInst, mhDC);


    CInputMgr::GetInst();



    onCreate();

    HACCEL hAccelTable = LoadAccelerators(hInst, nullptr);//MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));


    //K DeltaTime
    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);

  
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //DeltaTime(�� �����ӿ� �ɸ��� �ð�)�� ���Ѵ�
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);

            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

            mTime = tTime;

            //���ӷ��������� �⺻������ �ۼ��Ͽ���
            //OutputDebugString(L"game loop\n");
            onUpdate(mDeltaTime);
        }
    }

    onDestroy();


    CInputMgr::GetInst()->ReleaseInst();


    if (nullptr != mpBackBuffer)
    {
        delete mpBackBuffer;
        mpBackBuffer = nullptr;
    }


    ReleaseDC(mhWnd, mhDC);


    // return (int)msg.wParam;

    return msg;
}



ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;     // lpfnWndProc�� �����Լ��� �Լ�������
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPIENGINESTEP0));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIENGINESTEP0);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);// MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);

    return ATOM();
}

BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }

    // Ŭ���̾�Ʈ ������ ũ�⸦ �̰����� �����̴�
    RECT tRect = { 0,0,800,600 };
    // Ÿ��Ʋ��, �޴� ���� ����Ͽ� ��ü ������ ������ �ٽ� ������ش�
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);





    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;

    return 0;
}

LRESULT CALLBACK  CAPIEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
  
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // DC (Device Context)�� handle :DC�� �׸��⿡ ����ϴ� ��ġ (��ġ, ��ġ�� ���õ� ������, ��ġ�� ���� ��)�� �߻�ȭ �س��� ���̴�
        HDC hdc = BeginPaint(hWnd, &ps); // �׸����� ����
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

       
        EndPaint(hWnd, &ps); //  �׸��� ��尡 �����ٴ� �ǹ�
        
    }
    break;
    case WM_TIMER:
    {
        OutputDebugString(L">>>>>>>>>>>WM_TIMER Endemy Fire\n");
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





void CAPIEngine::DrawCircle(float tX, float tY, float tRadius)
{
    //Ellipse(mhDC, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
    Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
}

void CAPIEngine::DrawTexture(float tX, float tY, CTexture* tpTexture)
{
    BitBlt(this->mpBackBuffer->mhDCMem, //����ȭ�� DC
                     //100, 100,
        tX, tY,
        //0, 0,
        tpTexture->mBitmapInfo.bmWidth, tpTexture->mBitmapInfo.bmHeight,
        tpTexture->mhDCMem,//�޸�DC
        0, 0, SRCCOPY);
}


void CAPIEngine::Clear(float tR, float tG, float tB)
{
    ////���������� ������ ���� �����ϴ�
    HPEN hPen;  // ���ο� ���ڵ�
    HPEN hPenOld; // ������ ���� ���ڵ� ����

    HBRUSH hBrush; // ���ο� �귯�� �ڵ�
    HBRUSH hBrushOld; // ������ ���� �귯�� �ڵ� ������

    //�����θ� ���׸���
    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR * 255, tG * 255, tB * 255));
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255));

    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);

    Rectangle(thDC, 0, 0, 800, 600);

    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPIEngine::Present()
{
    BitBlt(mhDC,
        0, 0,
        800, 600,
        mpBackBuffer->mhDCMem,
        0, 0,
        SRCCOPY);
}

