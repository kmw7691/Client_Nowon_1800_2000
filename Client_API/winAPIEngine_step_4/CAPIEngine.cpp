#include "CAPIEngine.h"
#include "Resource.h"


HINSTANCE CAPIEngine::hInst = nullptr;




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
    // TODO: 여기에 코드를 입력합니다.

   // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIENGINESTEP0, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
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

void CAPIEngine::onUpdate()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::OnUpdate\n");
    OutputDebugString(szTemp);
}



MSG CAPIEngine::Run()
{
    MSG msg = { 0 };




    mhDC = GetDC(mhWnd);

    onCreate();

    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));


    //    MSG msg;

        //// 기본 메시지 루프입니다:
        //while (GetMessage(&msg, nullptr, 0, 0))
        //{
        //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        //    {
        //        TranslateMessage(&msg);
        //        DispatchMessage(&msg);
        //    }
        //}

    // 즉 윈도우 응용프로그램에 대한 처리는 if절에서 
    // 그 외에 idle time은 게임세꼐의 갱신처리에 쓰겠다 라는 것임
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //게임루프패턴의 기본구조를 작성하였다
            //OutputDebugString(L"game loop\n");
            onUpdate();
        }
    }

    onDestroy();


    ReleaseDC(mhWnd, mhDC);


    // return (int)msg.wParam;

    return msg;
}



ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;     // lpfnWndProc는 전역함수용 함수포인터
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIENGINESTEP0));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIENGINESTEP0);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);

    return ATOM();
}

BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }

    // 클라이언트 영역의 크기를 이것으로 쓸것이다
    RECT tRect = { 0,0,800,600 };
    // 타이틀바, 메뉴 등을 고려하여 전체 윈도우 영역을 다시 계산해준다
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
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // DC (Device Context)의 handle :DC는 그리기에 사용하는 장치 (장치, 장치에 관련된 설정값, 장치의 상태 등)을 추상화 해놓은 것이다
        HDC hdc = BeginPaint(hWnd, &ps); // 그리기모드 시작
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...


        //TextOut(hdc, 0, 0, L"test text output.", 17);
        //TextOut(hdc, 0, 25, L"안녕하세요. 곽민우입니다.", 13);
        //TextOut(hdc, 0, 50, L"I am a good boy.", 16);

        //LPCWSTR tString = TEXT("WCHAR Test");
        //TextOut(hdc, 0, 100, tString, 10);


        ////사각형 그리기
        //Rectangle(hdc, 200, 200, 200 + 100, 200 + 50);


        //// 선분 그리기
        //MoveToEx(hdc, 350, 200, NULL); // 시작점
        //LineTo(hdc, 450, 300); // 끝점

        //MoveToEx(hdc, 200, 50, NULL); // 시작점
        //LineTo(hdc, 400, 100); // 끝점
        //LineTo(hdc, 200, 150); // 끝점


        //// 원그리기
        //Ellipse(hdc, 400, 100, 400 + 100, 100 + 100);




        // WM_PAINT윈도우 메시지는 플래그성 메시지임
        // WM_PAINT가 발생하면 플래그변수에 1이 설정된다
        // 만약, 이 플래그 변수의 값이 계속 1이면, 계속 WM_PAINT 메시지를 발생시킨다
        // (그리기를 해야하는데 처리되지 않았기 때문)
        // 그래서 CPU연산을 잡아먹게된다
        // ENDPAINT는 호출되면 이러한 플래그 변수의 값을 0으로 설정한다

        EndPaint(hWnd, &ps); //  그리기 모드가 끝났다는 의미
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK  CAPIEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



void CAPIEngine::DrawCircle(float tX, float tY, float tRadius)
{
    Ellipse(mhDC, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
}