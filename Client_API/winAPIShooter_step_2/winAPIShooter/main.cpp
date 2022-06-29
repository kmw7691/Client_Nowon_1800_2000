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
#include "CActor.h"
#include "CBullet.h"
#include "CEnemy.h"

//k Ref
#include <list>
#include <vector>
using namespace std;

#pragma comment(lib, "winAPIEngine.lib")



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
    CTexture* mpTexture = nullptr;

    //K Bullet
    CTexture* mpTexBullet = nullptr;
    CTexture* mpTexEnemy = nullptr;


    //PF : 프리팹 / 원본객체
    CUnit* PFActor = nullptr;

    //K Bullet
    CUnit* PFBullet = nullptr;

    //Enemy
    CUnit* PFEnemy = nullptr;


    //실제 게임월드에 배치될 주인공 객체
    CActor* mpActor = nullptr;
  
    //K Bullet
    vector<CBullet*> mBullets;

    CEnemy* mpEnemy = nullptr;
  
    vector<CBullet*> mBulletEnemys;
   
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
        PFActor = CreatePrefab<CActor>(mpTexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));


        mpTexBullet = new CTexture();
        mpTexBullet->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbullet.bmp"));
        PFBullet = CreatePrefab<CBullet>(mpTexBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));



        mpTexEnemy = new CTexture();
        mpTexEnemy->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongenemy.bmp"));
        PFEnemy = CreatePrefab<CEnemy>(mpTexEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));
      

      

        //주인공 게임 객체 하나를 복제로 생성
        //mpActor = static_cast<CActor*>(PFActor->clone());
        mpActor = InstantObject<CActor>(PFActor);
        mpActor->AddRef();

        

        CBullet* tpBullet = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBullet = InstantObject<CBullet>(PFBullet);
            tpBullet->AddRef();

            //탄환은 생성시 비활성으로
            tpBullet->SetIsActive(false);



            mBullets.push_back(tpBullet);
            tpBullet->AddRef();

            tpBullet->Release();
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

            tpBulletEnemy->Release();
            tpBulletEnemy = nullptr;
        }

        //mpEnemy->DoFire(mBulletEnemys);


        //윈도우  API에서 제공하는 타이머 설정함수
        //lpTimerFunc 매개변수를 NULL로 두면 윈도우 메시지로 작동
        //정확도가 매우떨어짐
      //  SetTimer(mhWnd, 0, 3000, NULL);



        //test
      /*  CObjectK* tpObject = nullptr;
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
        }*/
    }

    virtual void onDestroy() override
    {
        //윈도우 API에서 제공하는 타이머 해제함수
        //KillTimer(mhWnd, 0);



        vector<CBullet*>::iterator tItorBulletEnemy;
        for (tItorBulletEnemy = mBulletEnemys.begin(); tItorBulletEnemy != mBulletEnemys.end(); ++tItorBulletEnemy)
        {
            DestroyObject(*tItorBulletEnemy);
        }
        mBulletEnemys.clear();


        DestroyObject(mpEnemy);

  
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


        SAFE_DELETE(PFActor)


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

        CAPIEngine::onDestroy();
    }

    virtual void onUpdate(float tDeltaTime) override
    {
        CAPIEngine::onUpdate(tDeltaTime);




        
        CInputMgr::GetInst()->Update();


        if (CInputMgr::GetInst()->KeyPress("OnMoveLeft"))
        {

            // 현재위치 = 이전위치 + 속도
            //mpUnit->mPosition.mX = mpUnit->mPosition.mX - 0.01f;

            mpActor->SetVelocity(SVector2D(-300.0f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
           // mpUnit->mPosition.mX = mpUnit->mPosition.mX + 0.01f;
            mpActor->SetVelocity(SVector2D(+300.0f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyUp("OnFire"))
        {
            OutputDebugString(L"Skill_00\n");

            mpActor->DoFire(mBullets);
        }

        if (CInputMgr::GetInst()->KeyUp("OnTest"))
        {
            OutputDebugString(L"TEST.......................\n");
        }


        //// update
        vector<CBullet*>::iterator t;
        for (t = mBullets.begin(); t != mBullets.end(); ++t)
        {
            (*t)->Update(tDeltaTime);
        }


        mpEnemy->Update(tDeltaTime);

        // enemy dofire


        //목표한 시간에 도달하면
        if (mpEnemy->mTimeTick >= 2.0f)
        {
            mpEnemy->DoFire(mBulletEnemys);

           // mpEnemy->mTimeTick = 0.0f;
            float tDiff = mpEnemy->mTimeTick - 2.0f;
            mpEnemy->mTimeTick = mpEnemy->mTimeTick = tDiff;
        }
        else
        {
            //델타타임을 누적해간다
            mpEnemy->mTimeTick = mpEnemy->mTimeTick + tDeltaTime;
        }


        vector<CBullet*>::iterator tE;
        for (tE = mBulletEnemys.begin(); tE != mBulletEnemys.end(); ++tE)
        {
            (*tE)->Update(tDeltaTime);
        }

        //// render

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

    MSG msg = { 0 };

    msg = tEngine.Run();

    return (int)msg.wParam;
}







