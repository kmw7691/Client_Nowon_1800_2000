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
#include "CCollisionMgr.h"
#include "CAnimator.h"

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


    // Test
    //CTexture* testTexs[2] = {nullptr, nullptr};

    int mTotalFramesCount = 2;      //총 프레임 갯수
    float mTimeInterval = 1.0f;     //애니메이션 프레임간 시간

    int mCurFrameIndex = 0;         //현재 프레임순번
    float mAniTime = 0.0f;          //애니메이션 진행 시간(틱)




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

        //CCollisionMgr::GetInst();


        CInputMgr::GetInst()->Create(mhWnd);
        CInputMgr::GetInst()->AddKey("OnMoveLeft", 'A');
        CInputMgr::GetInst()->AddKey("OnMoveRight", 'D');
        CInputMgr::GetInst()->AddKey("OnFire", VK_SPACE);

        CInputMgr::GetInst()->AddKey("OnTest_0", VK_LCONTROL, 'G');
        CInputMgr::GetInst()->AddKey("OnTest_1", VK_LCONTROL, 'H');





        //todo
        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CRyuEngine::Create\n");
        OutputDebugString(szTemp);

        

        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));
        //원본객체: CActor타입의 프리팹 생성
        PFActor = CreatePrefab<CActor>(mpTexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

             CAnimator* tpAnimActor = PFActor->CreateAnimation("AnimActor", this);
             tpAnimActor->SetOwnerObject(PFActor);
             tpAnimActor->AddAniSeq("ani_idle_actor", 1.0f, 2, L"resources/bongbong");
             tpAnimActor->AddAniSeq("ani_super_actor", 1.0f, 1, L"resources/bongbong_super");

            //PFActor->mpAnimator->mStrKeyCurAniSeq = "ani_idle_actor";
             PFActor->SetDefaultAniSeq("ani_idle_actor");

        mpTexBullet = new CTexture();
        mpTexBullet->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbullet.bmp"));
        //원본객체: CBullet타입의 프리팹 생성
        PFBullet = CreatePrefab<CBullet>(mpTexBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));
            
        CAnimator* tpAnimBullet = PFBullet->CreateAnimation("AnimBullet", this);
        tpAnimBullet->SetOwnerObject(PFBullet);   
        tpAnimBullet->AddAniSeq("ani_idle_bullet", 0.01f, 4 * 8, L"resources/explosionFull", ANI_PO::LOOP, ANI_SO::SHEET_FILE, 4, 8);
        PFBullet->SetDefaultAniSeq("ani_idle_bullet");

        //
        mpTexEnemy = new CTexture();
        mpTexEnemy->LoadTexture(this->hInst, this->mhDC, TEXT("resources/paladin_idle_0.bmp"));
        //원본객체: CEnemy타입의 프리팹 생성
        PFEnemy = CreatePrefab<CEnemy>(mpTexEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));


        CAnimator* tpAnimEnemy = PFEnemy->CreateAnimation("AnimEnemy", this);
        tpAnimEnemy->SetOwnerObject(PFEnemy);
        tpAnimEnemy->AddAniSeq("ani_idle_enemy", 0.05f, 7, L"resources/paladin_idle");
      //  tpAnimEnemy->AddAniSeq("ani_attack_enemy", 0.08f, 7, L"resources/paladin_attack", ANI_PO::ONCE);
        tpAnimEnemy->AddAniSeq("ani_attack_enemy", 0.08f, 11, L"resources/paladin_attack", ANI_PO::ONCE);
        


        /*PFEnemy->mpAnimator->mStrKeyPrevAniSeq = "ani_idle_enemy";
        PFEnemy->mpAnimator->mStrKeyCurAniSeq = "ani_idle_enemy";*/
        PFEnemy->SetDefaultAniSeq("ani_idle_enemy");



        //주인공 게임 객체 하나를 복제로 생성
        mpActor = InstantObject<CActor>(PFActor);
        mpActor->AddRef();


        //test
        /*CAnimator* tpAnimActor = mpActor->CreateAnimation("AnimActor", this);
        tpAnimActor->AddAniSeq("ani_idle_actor", 1.0f, 2, L"resources/bongbong");*/


        //ryu bullets
        CBullet* tpBullet = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {            
            tpBullet = InstantObject<CBullet>(PFBullet);
            tpBullet->AddRef();

            //탄환은 생성시 비활성으로
            tpBullet->SetIsActive(false);

            //
            //CCollisionMgr::GetInst()->AddUnit(tpBullet);

            //여기서는 인스턴스에 개별적으로 모두 태그를 붙임
            //프리팹에 붙여넣고 인스턴싱하면 모두 붙게 할 수도 있다.
            tpBullet->SetTag("tagActorBullet");

            mBullets.push_back(tpBullet);
            tpBullet->AddRef();           

            tpBullet->Release();    //지역변수 tpBullet에 대한 Release
            tpBullet = nullptr;
        }


        mpEnemy = InstantObject<CEnemy>(PFEnemy);
        mpEnemy->AddRef();
        mpEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
        //
        //CCollisionMgr::GetInst()->AddUnit(mpEnemy);
       



        CBullet* tpBulletEnemy = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBulletEnemy = InstantObject<CBullet>(PFBullet);
            tpBulletEnemy->AddRef();

            //탄환은 생성시 비활성으로
            tpBulletEnemy->SetIsActive(false);

                    //test
                    //CCollisionMgr::GetInst()->AddUnit(tpBulletEnemy);


            mBulletEnemys.push_back(tpBulletEnemy);
            tpBulletEnemy->AddRef();

            tpBulletEnemy->Release();    //지역변수 tpBullet에 대한 Release
            tpBulletEnemy = nullptr;
        }




        //test
        /*testTexs[0] = new CTexture();
        testTexs[0]->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));

        testTexs[1] = new CTexture();
        testTexs[1]->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_1.bmp"));*/


      
    }
    virtual void OnDestroy() override
    {        
        //test
       /* for (int ti = 0; ti < 2; ++ti)
        {
            SAFE_DELETE(testTexs[ti]);
        }*/




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
               


        //CCollisionMgr::ReleaseInst();

        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);



      
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

        if (CInputMgr::GetInst()->KeyDown("OnTest_0"))
        {
           // OutputDebugString(L"TEST.................\n");
            mpActor->mpAnimator->mStrKeyCurAniSeq = "ani_super_actor";
        }

        if (CInputMgr::GetInst()->KeyDown("OnTest_1"))
        {
            // OutputDebugString(L"TEST.................\n");
            mpActor->mpAnimator->mStrKeyCurAniSeq = "ani_idle_actor";
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
        if ( mpEnemy->mTimeTick >= 10.0f)
        {
            //todo
            mpEnemy->DoFire(mBulletEnemys);


            ////현재 애니메이션 시퀀스를 기억시켜두고
            ////(교체된 애니메이션 시퀀스를 플레이하고 이전 애니메이션 시퀀스로 돌아가기 위해)
            //mpEnemy->mpAnimator->mStrKeyPrevAniSeq = mpEnemy->mpAnimator->mStrKeyCurAniSeq;
            ////애니메이션 시퀀스를 교체한다
            //mpEnemy->mpAnimator->mStrKeyCurAniSeq = "ani_attack_enemy";
            //mpEnemy->mpAnimator->mpCurAniSeq->mCurFrameIndex = 0;
            //mpEnemy->mpAnimator->mpCurAniSeq->mAniTime = 0.0f;

            mpEnemy->PlayAni("ani_attack_enemy");





            //mpEnemy->mTimeTick = 0.0f;  //오차가 있을수 있다

            //오차보정
            float tDiff = mpEnemy->mTimeTick - 1.0f;
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




        //animation update
        if (mAniTime >= mTimeInterval)
        {
            if (mCurFrameIndex < mTotalFramesCount - 1)
            {
                mCurFrameIndex = mCurFrameIndex + 1;
            }

            else
            {
                mCurFrameIndex = 0;
            }

            mAniTime = 0.0f;
        }

        else
        {
            mAniTime = mAniTime + tDeltaTime;
        }





        //animation render
       /* this->DrawTexture(mpActor->mDisplayX, mpActor->mDisplayY, testTexs[1]);*/




        
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
