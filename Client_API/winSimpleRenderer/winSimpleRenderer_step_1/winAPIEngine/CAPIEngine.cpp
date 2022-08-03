#include "CAPIEngine.h"
//#include "Resource.h"
#include "CTexture.h"
#include "CInputMgr.h"
#include "CObjectRyu.h"
#include "CCollisionMgr.h"

#include "CPathMgr.h"
#include "CResourcesMgr.h"


HINSTANCE CAPIEngine::hInst = nullptr;

CAPIEngine::CAPIEngine()
{
    memset(szTitle, 0, MAX_LOADSTRING*sizeof(WCHAR));                  // 제목 표시줄 텍스트입니다.
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));            // 기본 창 클래스 이름입니다.
}
CAPIEngine::~CAPIEngine()
{
}


void CAPIEngine::OnCreate()
{
    //MessageBox()
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Create\n");
    OutputDebugStringW(szTemp);

    

}
void CAPIEngine::OnDestroy()
{
    

    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Destroy\n");
    OutputDebugStringW(szTemp);

}
void CAPIEngine::OnUpdate(float tDeltaTime)
{
    
}

void CAPIEngine::DrawCircle(float tX, float tY, float tRadius)
{
    //Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);




    HPEN hPen;
    HPEN hPenOld;

    HBRUSH hBrush;
    HBRUSH hBrushOld;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));	// 선 스타일, 굵기, 색상
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	//색을 채우지 않으려 한다면 이것으로
    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);


        Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);


    hBrush = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPen = (HPEN)::SelectObject(thDC, hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPIEngine::Clear(float tR, float tG, float tB)
{
    HPEN hPen;
    HPEN hPenOld;

    HBRUSH hBrush;
    HBRUSH hBrushOld;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR*255, tG*255, tB*255));
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255));	// 선 스타일, 굵기, 색상
    //hbr = (HBRUSH)GetStockObject(NULL_BRUSH);	//색을 채우지 않으려 한다면 이것으로
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
    BitBlt(mhDC,
        0, 0,
        800, 600,
        mpBackBuffer->mhDCMem,
        0, 0,
        SRCCOPY);
}

void CAPIEngine::DrawTexture(float tX, float tY, CTexture* tpTex, COLORREF tColorKey)
{
    //ryu_colorkey
    /*BitBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0, SRCCOPY);*/


    TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0,

        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        //tColorKey);
        RGB(255,0,255));
}


//ryu_ani_spritesheet_i
void CAPIEngine::DrawTexturePartial(float tX, float tY, CTexture* tpTex, int tRow, int tCol,int tIndex, COLORREF tColorKey)
{
    //한 스프라이트 프레임의 너비와 높이를 구한다
    int tSrcWidth = tpTex->mBitmapInfo.bmWidth/tCol;
    int tSrcHeight = tpTex->mBitmapInfo.bmHeight/tRow;


    //현재 행과 열을 구한다
    int tCurRow = tIndex / tCol;
    int tCurCol = tIndex % tCol;
    //현재 스프라이트 프레임의 위치를 구한다
    int tSrcX = tCurCol*tSrcWidth;
    int tSrcY = tCurRow*tSrcHeight;


    TransparentBlt(this->mpBackBuffer->mhDCMem,
        
        tX, tY,
        tSrcWidth, tSrcHeight,
        
        tpTex->mhDCMem,
     
        tSrcX, tSrcY,
        tSrcWidth, tSrcHeight,
       
        //tColorKey);
        RGB(255, 0, 255));




    /*TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0,

        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tColorKey);*/
}





BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow)
{
    /*LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPITRANING00, szWindowClass, MAX_LOADSTRING);*/

    wsprintf(szTitle, L"winAPIShootor");    //매개변수로 받아 설정도 가능하겠다.
    wsprintf(szWindowClass, L"winAPIShootor");    //매개변수로 받아 설정도 가능하겠다.


    MyRegisterClass(hInstance);

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
    mpBackBuffer->CreateBackBuffer(hInst, mhDC);
    //mpBackBuffer->LoadTexture(hInst, mhDC, TEXT("resources/backbuffer_0.bmp"));


    CPathMgr::GetInstance()->Create();
    CResourcesMgr::GetInstance()->Create(this);

    CInputMgr::GetInstance();
    CCollisionMgr::GetInstance();

    OnCreate();


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
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);
            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
            mTime = tTime;

            CCollisionMgr::GetInstance()->Update(mDeltaTime);

            OnUpdate(mDeltaTime);

        }
    }

    OnDestroy();


    CPathMgr::ReleaseInstance();
    CResourcesMgr::ReleaseInstance();


    CCollisionMgr::ReleaseInstance();

    CInputMgr::ReleaseInstance();

    if (nullptr != mpBackBuffer)
    {
        delete mpBackBuffer;
        mpBackBuffer = nullptr;
    }

    ReleaseDC(mhWnd, mhDC);


    return msg;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // nullptr;//WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPITRANING00));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPITRANING00);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.



    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    if (!mhWnd)
    {
        return FALSE;
    }


    SetWindowText(mhWnd, L"CAPIEngine test titlebar text");

    
    RECT tRect = { 0,0,800,600 };
    //다음 함수를 호출하면 타이틀바, 메뉴 등까지 고려하여 다시 계산해준다
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);

    //윈도우 크기를 설정한다
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);



    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}



LRESULT CALLBACK CAPIEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //case WM_COMMAND:
    //{
    //    int wmId = LOWORD(wParam);
    //    // 메뉴 선택을 구문 분석합니다:
    //    switch (wmId)
    //    {
    //    case IDM_ABOUT:
    //        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //        break;
    //    case IDM_EXIT:
    //        DestroyWindow(hWnd);
    //        break;
    //    default:
    //        return DefWindowProc(hWnd, message, wParam, lParam);
    //    }
    //}
    //break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    case WM_TIMER:
    {
        OutputDebugString(L">>>>>>WM_TIMER Enemy DoFire~!!!!!\n");
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void CAPIEngine::DrawTriangle(int x_0, int y_0, int x_1, int y_1, int x_2, int y_2, float tR, float tG, float tB)
{
    int tThickness = 1;

    HPEN hPen;
    HPEN hPenOld;

    hPen = CreatePen(PS_SOLID, tThickness, RGB(tR * 255, tG * 255, tB * 255));
    hPenOld = (HPEN)::SelectObject(this->mpBackBuffer->mhDCMem, (HGDIOBJ)hPen);

    POINT tPoint = { 0,0 };
    MoveToEx(this->mpBackBuffer->mhDCMem, x_0, y_0, &tPoint);
    LineTo(this->mpBackBuffer->mhDCMem, x_1, y_1);
    LineTo(this->mpBackBuffer->mhDCMem, x_2, y_2);
    LineTo(this->mpBackBuffer->mhDCMem, x_0, y_0);

    hPen = (HPEN)::SelectObject(this->mpBackBuffer->mhDCMem, hPenOld);

    DeleteObject(hPen);
}

void CAPIEngine::FillTriangle(int x_0, int y_0, int x_1, int y_1, int x_2, int y_2, float tR, float tG, float tB)
{
    //정점의 정보를 구축
    //정점의 정보
    TRIVERTEX vertex[3];
    vertex[0].x = x_0;
    vertex[0].y = y_0;
    vertex[0].Red = 0xffff * tR;
    vertex[0].Green = 0xffff * tG;
    vertex[0].Blue = 0xffff * tB;
    vertex[0].Alpha = 0x0000;


    vertex[1].x = x_1;
    vertex[1].y = y_1;
    vertex[1].Red = 0xffff * tR;
    vertex[1].Green = 0xffff * tG;
    vertex[1].Blue = 0xffff * tB;
    vertex[1].Alpha = 0x0000;


    vertex[2].x = x_2;
    vertex[2].y = y_2;
    vertex[2].Red = 0xffff * tR;
    vertex[2].Green = 0xffff * tG;
    vertex[2].Blue = 0xffff * tB;
    vertex[2].Alpha = 0x0000;


    GRADIENT_TRIANGLE tTriangle;

    tTriangle.Vertex1 = 0;
    tTriangle.Vertex2 = 1;
    tTriangle.Vertex3 = 2;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    GradientFill(this->mpBackBuffer->mhDCMem, vertex, 3, &tTriangle, 1, GRADIENT_FILL_TRIANGLE);
}