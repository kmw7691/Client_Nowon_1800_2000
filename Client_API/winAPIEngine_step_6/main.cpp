// winAPIEngine_step_0.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "main.h"
#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"

//#define MAX_LOADSTRING 100

// 전역 변수:
//HINSTANCE hInst;                                // 현재 인스턴스입니다.
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

class KwakEngine : public CAPIEngine
{
public:
    CUnit* mpUnit = nullptr;

    CTexture* mpTexture = nullptr;

public:

    KwakEngine()
    {

    }
    virtual ~KwakEngine()
    {

    }

    // 복사생성과 복사대입을 금지하기 위해 private로 접근제한
private:
    KwakEngine(const KwakEngine& tEngnine) {};
    KwakEngine& operator = (const KwakEngine& tEngnine) {};

public:
    virtual void onCreate() override
    {
        CAPIEngine::onCreate();

        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CAPIEngine::Create\n");
        OutputDebugString(szTemp);

        mpUnit = new CUnit();

        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));
    }

    virtual void onDestroy() override
    {
        if (nullptr != mpTexture)
        {
            delete mpTexture;
            mpTexture = nullptr;
        }



        if (nullptr != mpUnit)
        {
            delete mpUnit;
            mpUnit = nullptr;
        }

        CAPIEngine::onDestroy();

     /*   WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CAPIEngine::Destroy\n");
        OutputDebugString(szTemp);*/

        
    }

    virtual void onUpdate() override
    {
        CAPIEngine::onUpdate();


        // input
        // GetAsyncKeyState 는 현재 키의상태 를 알아오는 함수이다
        // GetAsyncKeyState의 리턴값은 다음과 같다
        /*
            0x0000 : 이전에 눌림 없음, 호출 시점에 눌림없음 <- 안눌림
            0x0001 : 이전에 눌림 있음, 호출 시점에 눌림없음 <- 떼어짐
            0x8000 : 이전에 눌림 없음, 호출 시점에 눌림있음 <- 새로눌림
            0x8001 : 이전에 눌림 있음, 호출 시점에 눌림있음 <- 눌리고있음
        */

        if (GetAsyncKeyState('A') & 0x8000)
        {
            // 현재위치 = 이전위치 + 속도
            mpUnit->mX = mpUnit->mX - 0.01f;
        }

        if (GetAsyncKeyState('D') & 0x8000)
        {
            mpUnit->mX = mpUnit->mX + 0.01f;
        }

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            OutputDebugString(L"Skill_00\n");
            MessageBox(NULL, L"Skill_00", L"Skill_00", MB_OK);
        }


        //// update


        //// render

        this->Clear();


        void Present();

        mpUnit->Render(this);


        //// '현재화면 DC'를 기반으로 memory DC를 만든다
        //HDC thDCMem = CreateCompatibleDC(this->mhDC);

        ////설정할 비트맵도구를 생성
        ////여기서는 파일에서 로드하며 만드는 것을 가정
        //HBITMAP thBitmap = (HBITMAP)LoadImage(hInst, TEXT("resources/bongbong_0.bmp"), 
        //                                        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        ////위에서 생성한 비트맵도구를 현재 비트맴도구로 설정한다
        ////리턴값으로는 이전에 사용하던 비트맵도구가 리턴된다
        //HBITMAP thOldBitmap = (HBITMAP)SelectObject(thDCMem, thBitmap);

        ////비트맵 도구의 핸들을 이용
        ////BITMAP info 정보를 얻는다
        //BITMAP tBitmapInfo;
        //GetObject(thBitmap, sizeof(tBitmapInfo), &tBitmapInfo);


       //BitBlt(this->mhDC, //현재화면 DC
       //              //100, 100,
       //              mpUnit->mX,mpUnit->mY,
       //              //0, 0,
       //              mpTexture->mBitmapInfo.bmWidth,mpTexture->mBitmapInfo.bmHeight,
       //              mpTexture->mhDCMem,//메모리DC
       //              0, 0, SRCCOPY);


        //BitBlt(this->mpBackBuffer->mhDCMem, //현재화면 DC
        //             //100, 100,
        //    mpUnit->mX, mpUnit->mY,
        //    //0, 0,
        //    mpTexture->mBitmapInfo.bmWidth, mpTexture->mBitmapInfo.bmHeight,
        //    mpTexture->mhDCMem,//메모리DC
        //    0, 0, SRCCOPY);
       this->DrawTexture(mpUnit->mX, mpUnit->mY, mpTexture);



       /* BitBlt(mhDC,
                0, 0, 
                800, 600, 
                mpBackBuffer->mhDCMem, 
                0, 0, 
                SRCCOPY);*/
        this->Present();



        ////이전에 사용하던 비트맵 도구를 다시 현재 비트맵도구로 설정하고
        //SelectObject(thDCMem, thOldBitmap);
        ////현재 사용하던 비트맵도구는 이제 해제한다
        //DeleteObject(thBitmap);

        ////DC도 해제한다
        //DeleteDC(thDCMem);



        //PAINTSTRUCT ps;
        //// DC (Device Context)의 handle :DC는 그리기에 사용하는 장치 (장치, 장치에 관련된 설정값, 장치의 상태 등)을 추상화 해놓은 것이다
        //HDC hdc = BeginPaint(mhWnd, &ps); // 그리기모드 시작
        //// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...


        //TextOut(hdc, 0, 0, L"test text output.", 17);
        //TextOut(hdc, 0, 25, L"안녕하세요. 곽민우입니다.", 13);
        //TextOut(hdc, 0, 50, L"I am a good boy.", 16);

        //LPCWSTR tString = TEXT("WCHAR Test");
        //TextOut(hdc, 0, 100, tString, 10);


        //////사각형 그리기
        //Rectangle(hdc, 200, 200, 200 + 100, 200 + 50);


        ////// 선분 그리기
        //MoveToEx(hdc, 350, 200, NULL); // 시작점
        //LineTo(hdc, 450, 300); // 끝점

        //MoveToEx(hdc, 200, 50, NULL); // 시작점
        //LineTo(hdc, 400, 100); // 끝점
        //LineTo(hdc, 200, 150); // 끝점


        ////// 원그리기
        //Ellipse(hdc, 400, 100, 400 + 100, 100 + 100);




        // WM_PAINT윈도우 메시지는 플래그성 메시지임
        // WM_PAINT가 발생하면 플래그변수에 1이 설정된다
        // 만약, 이 플래그 변수의 값이 계속 1이면, 계속 WM_PAINT 메시지를 발생시킨다
        // (그리기를 해야하는데 처리되지 않았기 때문)
        // 그래서 CPU연산을 잡아먹게된다
        // ENDPAINT는 호출되면 이러한 플래그 변수의 값을 0으로 설정한다

     //   EndPaint(mhWnd, &ps); //  그리기 모드가 끝났다는 의미
    }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    //OutputDebugString(L"test\n");
    KwakEngine tEngine;
    //CAPIEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);

    /* CAPIEngine tEngine;
     tEngine.Create(hInstance, nCmdShow);*/

    MSG msg = { 0 };

    msg = tEngine.Run();


    // 이런 경우를 허용하지 말자
    //KwakEngine tB = tEngine;


    return (int)msg.wParam;


    // Create

    // TODO: 여기에 코드를 입력합니다.

    //// 전역 문자열을 초기화합니다.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINAPIENGINESTEP0, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    //// 애플리케이션 초기화를 수행합니다:
    //if (!InitInstance (hInstance, nCmdShow))
    //{
    //    return FALSE;
    //}
    //



    // Run

//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));
//
//    MSG msg;
//
//    // 기본 메시지 루프입니다:
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//
//    return (int) msg.wParam;
//    
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIENGINESTEP0));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIENGINESTEP0);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}

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
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // 메뉴 선택을 구문 분석합니다:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
