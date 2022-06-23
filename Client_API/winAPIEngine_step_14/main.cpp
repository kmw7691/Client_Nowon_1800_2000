// winAPIEngine_step_0.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "main.h"
#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectK.h"
#include "CRef.h"
#include "Kmacro.h"
#include "CInputMgr.h"

//k Ref
#include <list>
using namespace std;
/*
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
*/

// 디자인패턴 : 프로그램구조 설계방법 모음집
/*
    디자인패턴 <- OOP를 기반으로한다.
                -> OOP의 모범답안집

    c언어의 프로그래밍 패러다임 : 구조화 프로그래밍 structured programming
    c++언어에서의 도입된 프로그래밍 패러다임 : OOP(Object Oriented Programming 객체지향 프로그램)
    타입을 매개변수로 다루는 기법
        - 일반화 프로그래밍 General Programming

    c++은 "멀티프로그래밍 패러다임"의 언어이다.
*/

class KwakEngine : public CAPIEngine
{
public:
    CUnit* mpUnit = nullptr;

    CTexture* mpTexture = nullptr;

   /*
    // k ref
    /*
    * Template  : 일반화 프로그래밍 기법을 c++에 문법으로 만들어놓은것
    *  <-- 타입을 매개변수로 다루는 기법
    * 
    * Standard Template Library
    * STL 의 3가지 구성요소
    * 1)컨테이너 : 자료구조를 일반화시켜 만들어놓은것
    * 2)반복자
    * 3)알고리즘
    */
   
    list<CObjectK*> mObjectKs;



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



        CInputMgr::GetInst()->Create(mhWnd);
        CInputMgr::GetInst()->AddKey("OnMoveLeft", 'A');
        CInputMgr::GetInst()->AddKey("OnMoveRight", 'D');


        CInputMgr::GetInst()->AddKey("OnFire", VK_SPACE);

        CInputMgr::GetInst()->AddKey("OnTest", VK_CONTROL, 'G');



        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CAPIEngine::Create\n");
        OutputDebugString(szTemp);

   

        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));

        mpUnit = new CUnit();
        mpUnit->SetTexture(mpTexture);
        mpUnit->SetAnchors(0.5f, 0.5f);
        mpUnit->SetPosition(SVector2D(400.0f, 500.0f));



        //test
        CObjectK* tpObject = nullptr;
        tpObject = new CObjectK();
        tpObject->AddRef();


        CObjectK* tpA = nullptr;
        tpA = tpObject;
        tpA->AddRef();



        mObjectKs.push_back(tpObject);
        tpObject->AddRef();




        if (nullptr != tpA)
        {
            tpA->Release();
            tpA = nullptr;
        }

        if (nullptr != tpObject)
        {
            tpObject->Release();
            tpObject = nullptr;
        }
    }

    virtual void onDestroy() override
    {
        for (list<CObjectK*>::iterator titor = mObjectKs.begin(); titor != mObjectKs.end(); ++titor)
        {
            if (nullptr != (*titor))
            {
                (*titor)->Release();
                (*titor) = nullptr;
            }
        }


      /*  if (nullptr != mpUnit)
        {
            delete mpUnit;
            mpUnit = nullptr;
        }*/

        SAFE_DELETE(mpUnit)



        if (nullptr != mpTexture)
        {
            delete mpTexture;
            mpTexture = nullptr;
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

        
        CInputMgr::GetInst()->Update();


        if (CInputMgr::GetInst()->KeyPress("OnMoveLeft"))
        {
            // 현재위치 = 이전위치 + 속도
            //mpUnit->mPosition.mX = mpUnit->mPosition.mX - 0.01f;

            mpUnit->SetVelocity(SVector2D(-0.01f, 0.0f));
            mpUnit->Update();
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
           // mpUnit->mPosition.mX = mpUnit->mPosition.mX + 0.01f;
            mpUnit->SetVelocity(SVector2D(+0.01f, 0.0f));
            mpUnit->Update();
        }

        if (CInputMgr::GetInst()->KeyUp("OnFire"))
        {
            OutputDebugString(L"Skill_00\n");
        }

        if (CInputMgr::GetInst()->KeyUp("OnTest"))
        {
            OutputDebugString(L"TEST.......................\n");
        }


        //// update


        //// render

        this->Clear(0.0f, 0.0f, 0.2f);


       

        mpUnit->Render(this);

        
       //this->DrawTexture(mpUnit->mX, mpUnit->mY, mpTexture);



        this->Present();
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
}

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
