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




//// 정보 대화 상자의 메시지 처리기입니다.
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



//
//template<typename T>
//T* CAPIEngine::CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
//{
//    // 프리팹들을 만들어둔다( 원본객체 )
//    T* tpPrefab = new T();
//
//    tpPrefab->SetTexture(tpTex);
//    tpPrefab->SetAnchorPoint(tAnchorX, tAnchorY);
//    tpPrefab->SetPosition(tPosition);
//
//    return tpPrefab;
//}
//void CAPIEngine::DestroyPrefab(CObjectRyu*& tPrefab)
//{
//    if (nullptr != tPrefab)
//    {
//        delete tPrefab;
//        tPrefab = nullptr;
//    }
//}