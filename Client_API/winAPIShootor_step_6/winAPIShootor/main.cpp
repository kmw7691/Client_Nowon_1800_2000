// winAPIEngine_step_0.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "main.h"


#include "CAPIEngine.h"

#include "CUnit.h"
#include "CTexture.h"

#include "CObjectRyu.h"


#include "ryumacro.h"

#include "CInputMgr.h"

#include "CActor.h"
#include "CBullet.h"

#include "CEnemy.h"     //

//ryu ref
#include <list>
#include <vector>
using namespace std;


#pragma comment(lib, "winAPIEngine.lib")



class CRyuEngine : public CAPIEngine
{
public:
    
    CTexture* mpTexture = nullptr;
    //ryu bullets
    CTexture* mpTexBullet = nullptr;

    //
    CTexture* mpTexEnemy = nullptr;


    //프리팹: 원본객체
    CUnit* PFActor = nullptr;
    //ryu bullets
    CUnit* PFBullet = nullptr;

    //
    CUnit* PFEnemy = nullptr;





    //실제 게임월드에 배치될 주인공 객체
    CActor* mpActor = nullptr;
    //ryu bullets
    vector<CBullet*> mBullets;


    CEnemy* mpEnemy = nullptr;
    vector<CBullet*> mBulletEnemys;



   /* CEnemy* mpEnemyAimed = nullptr;
    vector<CBullet*> mBulletAimeds;


    CEnemy* mpEnemyCircled = nullptr;
    vector<CBullet*> mBulletC;*/




    list<CObjectRyu*> mObjectRyus;
    
    

public:
    CRyuEngine()
    {
    }
    virtual ~CRyuEngine()   //가상소멸자 
    {
    }

    //복사생성과 복사대입을 금지하기 위해서 private로 접근제한하였다.
private:
    CRyuEngine(const CRyuEngine& tEngine) {};
    CRyuEngine& operator=(const CRyuEngine& tEngine) {};


public:
    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();


        CInputMgr::GetInst()->Create(mhWnd);
        CInputMgr::GetInst()->AddKey("OnMoveLeft", 'A');
        CInputMgr::GetInst()->AddKey("OnMoveRight", 'D');
        CInputMgr::GetInst()->AddKey("OnFire", VK_SPACE);

        CInputMgr::GetInst()->AddKey("OnTest", VK_LCONTROL, 'G');





        //todo
        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CRyuEngine::Create\n");
        OutputDebugString(szTemp);

        

        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));
        //원본객체: CActor타입의 프리팹 생성
        PFActor = CreatePrefab<CActor>(mpTexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

        mpTexBullet = new CTexture();
        mpTexBullet->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbullet.bmp"));
        //원본객체: CBullet타입의 프리팹 생성
        PFBullet = CreatePrefab<CBullet>(mpTexBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

        //
        mpTexEnemy = new CTexture();
        mpTexEnemy->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongenemy.bmp"));
        //원본객체: CEnemy타입의 프리팹 생성
        PFEnemy = CreatePrefab<CEnemy>(mpTexEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));




        //주인공 게임 객체 하나를 복제로 생성
        mpActor = InstantObject<CActor>(PFActor);
        mpActor->AddRef();


        //ryu bullets
        CBullet* tpBullet = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {            
            tpBullet = InstantObject<CBullet>(PFBullet);
            tpBullet->AddRef();

            //탄환은 생성시 비활성으로
            tpBullet->SetIsActive(false);




            mBullets.push_back(tpBullet);
            tpBullet->AddRef();           

            tpBullet->Release();    //지역변수 tpBullet에 대한 Release
            tpBullet = nullptr;
        }


        mpEnemy = InstantObject<CEnemy>(PFEnemy);
        mpEnemy->AddRef();
        mpEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);


       



        CBullet* tpBulletEnemy = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBulletEnemy = InstantObject<CBullet>(PFBullet);
            tpBulletEnemy->AddRef();

            //탄환은 생성시 비활성으로
            tpBulletEnemy->SetIsActive(false);




            mBulletEnemys.push_back(tpBulletEnemy);
            tpBulletEnemy->AddRef();

            tpBulletEnemy->Release();    //지역변수 tpBullet에 대한 Release
            tpBulletEnemy = nullptr;
        }






        //mpEnemyAimed = InstantObject<CEnemy>(PFEnemy);
        //mpEnemyAimed->AddRef();
        ////mpEnemyAimed->SetVelocity(SVector2D(+1.0f, 0.0f) * 50.0f);   

        //CBullet* tpBulletAimed = nullptr;
        //for (int ti = 0; ti < 10; ++ti)
        //{
        //    tpBulletAimed = InstantObject<CBullet>(PFBullet);
        //    tpBulletAimed->AddRef();

        //    //탄환은 생성시 비활성으로
        //    tpBulletAimed->SetIsActive(false);




        //    mBulletAimeds.push_back(tpBulletAimed);
        //    tpBulletAimed->AddRef();

        //    tpBulletAimed->Release();    //지역변수 tpBullet에 대한 Release
        //    tpBulletAimed = nullptr;
        //}



        //mpEnemyCircled = InstantObject<CEnemy>(PFEnemy);
        //mpEnemyCircled->AddRef();
        //mpEnemyCircled->SetVelocity(SVector2D(+1.0f, 0.0f) * 25.0f);


        //CBullet* tpBulletC = nullptr;
        //for (int ti = 0; ti < 8*10; ++ti)
        //{
        //    tpBulletC = InstantObject<CBullet>(PFBullet);
        //    tpBulletC->AddRef();

        //    //탄환은 생성시 비활성으로
        //    tpBulletC->SetIsActive(false);




        //    mBulletC.push_back(tpBulletC);
        //    tpBulletC->AddRef();

        //    tpBulletC->Release();    //지역변수 tpBullet에 대한 Release
        //    tpBulletC = nullptr;
        //}
    }
    virtual void OnDestroy() override
    {        
        /*vector<CBullet*>::iterator tItorBulletC;
        for (tItorBulletC = mBulletC.begin(); tItorBulletC != mBulletC.end(); ++tItorBulletC)
        {
            DestroyObject(*tItorBulletC);
        }
        mBulletC.clear();


        DestroyObject(mpEnemyCircled);


        vector<CBullet*>::iterator tItorBulletAimed;
        for (tItorBulletAimed = mBulletAimeds.begin(); tItorBulletAimed != mBulletAimeds.end(); ++tItorBulletAimed)
        {
            DestroyObject(*tItorBulletAimed);
        }
        mBulletAimeds.clear();


        DestroyObject(mpEnemyAimed);*/




        vector<CBullet*>::iterator tItorBulletEnemy;
        for (tItorBulletEnemy = mBulletEnemys.begin(); tItorBulletEnemy != mBulletEnemys.end(); ++tItorBulletEnemy)
        {
            DestroyObject(*tItorBulletEnemy);
        }
        mBulletEnemys.clear();




        DestroyObject(mpEnemy);

        //ryu bullets
        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
            DestroyObject(*tItorBullet);
        }
        mBullets.clear();

        DestroyObject(mpActor);

        DestroyPrefab(PFEnemy);
        DestroyPrefab(PFBullet);
        DestroyPrefab(PFActor);



        if (nullptr != this->mpTexEnemy)
        {
            delete mpTexEnemy;
            mpTexEnemy = nullptr;
        }

        if (nullptr != this->mpTexBullet)
        {
            delete mpTexBullet;
            mpTexBullet = nullptr;
        }

        if (nullptr != mpTexture)
        {
            delete mpTexture;
            mpTexture = nullptr;
        }
               

        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);



        //collision

        //'원 대 원' 충돌 알고리즘 test
        //      '적' vs '주인공기체가 발사한 일반탄환들' 만 가정한다.

        //vector<CBullet*>::iterator tBItor;
        //for (tBItor = mBullets.begin(); tBItor != mBullets.end(); ++tBItor)
        //{
        //    if ((*tBItor)->GetIsActive() )
        //    {
        //        if (mpEnemy->GetIsActive())
        //        {
        //            //원을 이용한 충돌처리

        //            //제곱근은 무한의 개념이 들어있어 연산이 많으므로 제거한다(양변을 거듭제곱)

        //            float tAdd          = ((*tBItor)->GetRadius() + mpEnemy->GetRadius())* ((*tBItor)->GetRadius() + mpEnemy->GetRadius());
        //            float tDistance     =  ((*tBItor)->GetPosition().mX - mpEnemy->GetPosition().mX)* ((*tBItor)->GetPosition().mX - mpEnemy->GetPosition().mX) + ((*tBItor)->GetPosition().mY - mpEnemy->GetPosition().mY)* ((*tBItor)->GetPosition().mY - mpEnemy->GetPosition().mY) ;

        //            //길이의 개념이므로 0을 포함한 양수이다.
        //            //그러므로 거듭제곱해도 그 대소관계가 유지된다.
        //            if (tDistance <= tAdd)
        //            {
        //                OutputDebugString(TEXT("Collision\n"));

        //                break;
        //            }
        //        }
        //    }
        //}


        //AABB충돌 알고리즘 테스트
        /*bool tIsCollision = false;
        vector<CBullet*>::iterator tBItor;
        for (tBItor = mBullets.begin(); tBItor != mBullets.end(); ++tBItor)
        {
            if ((*tBItor)->GetIsActive())
            {
                if (mpEnemy->GetIsActive())
                {   
                    tIsCollision = mpEnemy->Intersects(*(* tBItor));
                    if (tIsCollision)
                    {
                        OutputDebugString(TEXT("Collision\n"));

                        mpEnemy->SetIsActive(false);
                        (*tBItor)->SetIsActive(false);

                        break;
                    }
                }
            }
        }*/

        bool tIsCollision = false;
        vector<CBullet*>::iterator tBItor;
        for (tBItor = mBullets.begin(); tBItor != mBullets.end(); ++tBItor)
        {
            if ((*tBItor)->GetIsActive())
            {
                if (mpEnemy->GetIsActive())
                {
                    tIsCollision = (*tBItor)->mpCollider->DoCollision(mpEnemy->mpCollider);
                    if (tIsCollision)
                    {
                        OutputDebugString(TEXT("Collision\n"));

                        mpEnemy->SetIsActive(false);
                        (*tBItor)->SetIsActive(false);

                        break;
                    }
                }
            }
        }



      
        //input
        CInputMgr::GetInst()->Update();

        if (CInputMgr::GetInst()->KeyPress("OnMoveLeft"))
        {   
            mpActor->SetVelocity(SVector2D(-250.f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
            mpActor->SetVelocity(SVector2D(+250.f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyUp("OnFire"))
        {
            OutputDebugString(L"Skill_00\n");

            mpActor->DoFire(mBullets);
        }

        if (CInputMgr::GetInst()->KeyDown("OnTest"))
        {
            OutputDebugString(L"TEST.................\n");
        }




        //update
        vector<CBullet*>::iterator t;
        for (t = mBullets.begin(); t != mBullets.end(); ++t)
        {
            (*t)->Update(tDeltaTime);
        }


        mpEnemy->Update(tDeltaTime);

        //enemy do fire

        //목표한 시간에 도달하면 
        if ( mpEnemy->mTimeTick >= 2.0f)
        {
            //todo
            mpEnemy->DoFire(mBulletEnemys);

            //mpEnemy->mTimeTick = 0.0f;  //오차가 있을수 있다

            //오차보정
            float tDiff = mpEnemy->mTimeTick - 2.0f;
            mpEnemy->mTimeTick = tDiff;
        }
        else
        {
            //delta time을 누적해간다.
            mpEnemy->mTimeTick = mpEnemy->mTimeTick + tDeltaTime;
        }




        vector<CBullet*>::iterator tE;
        for (tE = mBulletEnemys.begin(); tE != mBulletEnemys.end(); ++tE)
        {
            (*tE)->Update(tDeltaTime);
        }



        //mpEnemyAimed->Update(tDeltaTime);

        //if (mpEnemyAimed->mTimeTick >= 4.0f)
        //{
        //    //todo
        //    mpEnemyAimed->DoFireAimed(mBulletEnemys, mpActor);

        //    float tDiff = mpEnemyAimed->mTimeTick - 4.0f;
        //    mpEnemyAimed->mTimeTick = tDiff;
        //}
        //else
        //{
        //    mpEnemyAimed->mTimeTick = mpEnemyAimed->mTimeTick + tDeltaTime;
        //}



        //vector<CBullet*>::iterator tEAimed;
        //for (tEAimed = mBulletAimeds.begin(); tEAimed != mBulletAimeds.end(); ++tEAimed)
        //{
        //    (*tEAimed)->Update(tDeltaTime);
        //}



        //mpEnemyCircled->Update(tDeltaTime);

        //if (mpEnemyCircled->mTimeTick >= 2.0f)
        //{
        //    //todo
        //    mpEnemyCircled->DoFireCircled(mBulletC);

        //    float tDiff = mpEnemyCircled->mTimeTick - 2.0f;
        //    mpEnemyCircled->mTimeTick = tDiff;
        //}
        //else
        //{
        //    mpEnemyCircled->mTimeTick = mpEnemyCircled->mTimeTick + tDeltaTime;
        //}


        //vector<CBullet*>::iterator tEC;
        //for (tEC = mBulletC.begin(); tEC != mBulletC.end(); ++tEC)
        //{
        //    (*tEC)->Update(tDeltaTime);
        //}




        //render
        this->Clear(0.0f, 0.0f, 0.2f);        
        
        mpActor->Render();
               
        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
            (*tItorBullet)->Render();
        }

        mpEnemy->Render();

        vector<CBullet*>::iterator tItorBulletE;
        for (tItorBulletE = mBulletEnemys.begin(); tItorBulletE != mBulletEnemys.end(); ++tItorBulletE)
        {
            (*tItorBulletE)->Render();
        }


        /*mpEnemyAimed->Render();


        vector<CBullet*>::iterator tItorEAimed;
        for (tItorEAimed = mBulletAimeds.begin(); tItorEAimed != mBulletAimeds.end(); ++tItorEAimed)
        {
            (*tItorEAimed)->Render();
        }


        mpEnemyCircled->Render();

        vector<CBullet*>::iterator tECItor;
        for (tECItor = mBulletC.begin(); tECItor != mBulletC.end(); ++tECItor)
        {
            (*tECItor)->Render();
        }*/

        
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


    CRyuEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);


    MSG msg = { 0 };
    msg = tEngine.Run();


    //이런 경우를 허용하지 말자.
    //CRyuEngine tB = tEngine;        //복사생성자
    //CRyuEngine tA;
    //tEngine = tA;                   //복사대입연산자





    return (int)msg.wParam;


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
////
////   함수: InitInstance(HINSTANCE, int)
////
////   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
////
////   주석:
////
////        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
////        주 프로그램 창을 만든 다음 표시합니다.
////
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

////
////  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  용도: 주 창의 메시지를 처리합니다.
////
////  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
////  WM_PAINT    - 주 창을 그립니다.
////  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
////
////
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
