// winAPITraning00.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

/*

    이 예시 코드는 
	3 color match 알고리즘 테스트를 위해 

	2차원 격자 형태로 '퍼즐 피스'를 나열하고 ( 게임보드 )
	플레이어의 선택UI를 표시하는 기능을 가진다

    -5행5열의 2차원 격자 형태의 게임보드를 가정한다
    -타일(퍼즐피스) 1개의 크기는 96pixel by 96pixel 으로 가정
    -게임보드의 시작위치는 100, 100 으로 가정 

*/

#include "framework.h"

#include "CPiece.h"
#include "CSelect.h"


#include <list>
using namespace std;

#pragma comment(lib, "winAPIEngine.lib")




class CRyuEngine : public CAPIEngine
{
private:  

    CTexture* mpTexDefaultPiece = nullptr;      //퍼즐 피스의 기본 대표 이미지
    CTexture* mpTexUISelect = nullptr;          //선택UI 기본 대표 이미지 

    CUnit* PFPiece = nullptr;                   //퍼즐 피스 프리팹
    CUnit* PFUISelect = nullptr;                //선택UI 프리팹 

private:

    //퍼즐피스 6종을 준비했다.
    //(처음 BLACK은 빈칸이라고 가정한다. 그러므로 유효한 퍼즐피스는 총 5개 종류이다 )
    string mColor[6] = {"BLACK", "PINK", "RED", "GREEN", "BLUE", "YELLOW"};

    //게임보드 속성 테이블 
    //각각의 셀(칸)에는 어떤 종류의 퍼즐피스가 들어있는지에 대한 정보가 기록되어 있다 
    unsigned int mBoardAttrib[5][5] =
    {
        5,5,1,1,3,
        5,2,2,2,3,
        5,4,2,3,2,
        4,4,2,3,3,
        4,1,1,3,3
    };

    //선택UI의 위치
    int mCurX = 0;
    int mCurY = 0;

private:
    CPiece* mPieceBoard[5][5] =
    {
        nullptr
    };

    CSelect* mpUISelect = nullptr;

    
public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};

    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();

        CInputMgr::GetInstance()->AddKey("OnMoveLt", VK_LEFT);
        CInputMgr::GetInstance()->AddKey("OnMoveRt", VK_RIGHT);
        CInputMgr::GetInstance()->AddKey("OnMoveUp", VK_UP);
        CInputMgr::GetInstance()->AddKey("OnMoveDown", VK_DOWN);

        CInputMgr::GetInstance()->AddKey("OnSelectHit", VK_SPACE);


        //todo
        //텍스쳐 로드
        mpTexDefaultPiece = new CTexture();
        mpTexDefaultPiece->LoadTexture(hInst, mhDC, L"resources/block_0.bmp");

        mpTexUISelect = new CTexture();
        mpTexUISelect->LoadTexture(hInst, mhDC, L"resources/select_0.bmp");

        //프리팹 생성
        PFPiece = CreatePrefab<CPiece>(mpTexDefaultPiece, 0.5f, 0.5f, SVector2D(0.0f, 0.0f));
            CAnimator* tpAnimator = PFPiece->CreateAnimation("AnimPiece", this);
            tpAnimator->SetOwnerObject(PFPiece);
            tpAnimator->AddAniSeq(L"resources/block_0", "BLACK", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            tpAnimator->AddAniSeq(L"resources/block_1", "PINK", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            tpAnimator->AddAniSeq(L"resources/block_2", "RED", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            tpAnimator->AddAniSeq(L"resources/block_3", "GREEN", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            tpAnimator->AddAniSeq(L"resources/block_4", "BLUE", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            tpAnimator->AddAniSeq(L"resources/block_5", "YELLOW", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            PFPiece->SetDefaultAniSeq("BLACK");


        PFUISelect = CreatePrefab<CSelect>(mpTexUISelect, 0.5f, 0.5f, SVector2D::ZERO);
            CAnimator* tpAnimatorSelect = PFUISelect->CreateAnimation("AnimSelect", this);
            tpAnimatorSelect->SetOwnerObject(PFUISelect);
            tpAnimatorSelect->AddAniSeq(L"resources/select_0", "IDLE", 0.0f, 1, ANI_PO::LOOP, ANI_SO::SHEET_FILE);
            tpAnimatorSelect->AddAniSeq(L"resources/select", "CLICK", 0.5f, 2, ANI_PO::LOOP, ANI_SO::FRAME_FILE);
            PFUISelect->SetDefaultAniSeq("CLICK");
        

       for (int tRow = 0; tRow < 5; ++tRow)
       {
           for (int tCol = 0; tCol < 5; ++tCol)
           {
               mPieceBoard[tRow][tCol] = InstantObject<CPiece>(PFPiece);
           }
       }

       mpUISelect = InstantObject<CSelect>(PFUISelect);
       mpUISelect->AddRef();


    }
    virtual void OnDestroy() override
    {
        DestroyObject(mpUISelect);

        for (int tRow = 0; tRow < 5; ++tRow)
        {
            for (int tCol = 0; tCol < 5; ++tCol)
            {
                DestroyObject(mPieceBoard[tRow][tCol]);
            }
        }

        //todo
        DestroyPrefab(PFUISelect);
        DestroyPrefab(PFPiece);

        SAFE_DELETE(mpTexUISelect);
        SAFE_DELETE(mpTexDefaultPiece);



        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);


        //input
        CInputMgr::GetInstance()->Update();
        if (CInputMgr::GetInstance()->KeyUp("OnMoveLt"))
        {
            if (mCurX > 0)
            {
                mCurX = mCurX - 1;
            }
        }

        if (CInputMgr::GetInstance()->KeyUp("OnMoveRt"))
        {
            if (mCurX < 4)
            {
                mCurX = mCurX + 1;
            }
        }
        
        if (CInputMgr::GetInstance()->KeyUp("OnMoveUp"))
        {
            if (mCurY > 0)
            {
                mCurY = mCurY - 1;
            }
        }

        if (CInputMgr::GetInstance()->KeyUp("OnMoveDown"))
        {
            if (mCurY < 4)
            {
                mCurY = mCurY + 1;
            }
        }

        if (CInputMgr::GetInstance()->KeyUp("OnSelectHit"))
        {
            OutputDebugString(L"Select Hit!!!!!!!!!\n");
        }

        //update
        for (int tRow = 0; tRow < 5; ++tRow)
        {
            for (int tCol = 0; tCol < 5; ++tCol)
            {
                //보드판의 시작위치지점은 100,100
                int tBoardStartX = 100;
                int tBoardStartY = 100;


                //퍼즐피스의 위치선정
                //행과 열기반의 좌표 --> 픽셀기반의 좌표
                
                int tX = tBoardStartX + tCol * 96;
                int tY = tBoardStartY + tRow * 96;

                mPieceBoard[tRow][tCol]->SetPosition(SVector2D(tX, tY));


                //퍼즐피스의 색상 선정
                int tColorIndex = mBoardAttrib[tRow][tCol];

                string tKey = mColor[tColorIndex];          //색상을 나타내는 문자열 정보
                mPieceBoard[tRow][tCol]->PlayAni(tKey);

;            }
        }

        int tBoardStartX = 100;
        int tBoardStartY = 100;


        //퍼즐피스의 위치선정
        //행과 열기반의 좌표 --> 픽셀기반의 좌표

        int tX = tBoardStartX + mCurX * 96;
        int tY = tBoardStartY + mCurY * 96;


        mpUISelect->SetPosition(SVector2D(tX, tY));
        mpUISelect->Update(tDeltaTime);





        //render
        this->Clear(0.1f, 0.1f, 0.3f);       
       
              for (int tRow = 0; tRow < 5; ++tRow)
              {
                  for (int tCol = 0; tCol < 5; ++tCol)
                  {
                      mPieceBoard[tRow][tCol]->Render();
                  }
              }

              mpUISelect->Render();
        
        this->Present();
    }

private:
    CRyuEngine(const CRyuEngine&) {};
    CRyuEngine& operator=(const CRyuEngine&) {};
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

    return (int) msg.wParam;
}

