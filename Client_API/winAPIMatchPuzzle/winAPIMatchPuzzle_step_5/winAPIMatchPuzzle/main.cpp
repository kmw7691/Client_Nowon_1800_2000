// winAPITraning00.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//



#include "framework.h"
#include "CPiece.h"
#include "CSelect.h"
#include <stack>
#include <list>
#include <time.h>
#include "CPathMgr.h"
#include "CResourcesMgr.h"

using namespace std;

#pragma comment(lib, "winAPIEngine.lib")

#define MAX_ROW 6
#define MAX_COL 6

//STL 이 제공하는 컨테이너 중에서 스택을 이용하였다
typedef stack<int> CIntStack;



class CRyuEngine : public CAPIEngine
{
    CIntStack mIntStack;


    int mGrid[MAX_ROW][MAX_COL];

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

    //색상검토용 테이블
    unsigned int mCheckVisit[5][5] =
    {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    };

private:
    CPiece* mPieceBoard[5][5] =
    {
        nullptr
    };

    CSelect* mpUISelect = nullptr;

    
public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};

    int DoCheckBlockAttrib(int tCol, int tRow, unsigned int tColorIndex);

    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();


        // test

        CPathMgr::GetInstance()->MakePath(RESOUCES_PATH, L"resources", ROOT_PATH);
        //CPathMgr::GetInstance()->Create();


        //난수
        srand(time(nullptr));


        CInputMgr::GetInstance()->AddKey("OnMoveLt", VK_LEFT);
        CInputMgr::GetInstance()->AddKey("OnMoveRt", VK_RIGHT);
        CInputMgr::GetInstance()->AddKey("OnMoveUp", VK_UP);
        CInputMgr::GetInstance()->AddKey("OnMoveDown", VK_DOWN);

        CInputMgr::GetInstance()->AddKey("OnSelectHit", VK_SPACE);


        //todo
        //텍스쳐 로드
        mpTexDefaultPiece = new CTexture();
        mpTexDefaultPiece->LoadTexture(hInst, mhDC, L"resources/block_0.bmp");







       /*mpTexUISelect = new CTexture();
        mpTexUISelect->LoadTexture(hInst, mhDC, L"resources/select_0.bmp");*/
        CTexture* tpTex = nullptr;
        tpTex = CResourcesMgr::GetInstance()->LoadTexture("select_0", L"select_0.bmp", RESOUCES_PATH);
        if (!tpTex)
        {
            OutputDebugString(L"bitmap image file load failed");

            return;
        }







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



            mpTexUISelect = CResourcesMgr::GetInstance()->FindTexture("select_0");





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

        //SAFE_DELETE(mpTexUISelect);
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

            //현재 선택된 퍼즐피스의 색상을 얻는다
            int tColorIndex = mBoardAttrib[mCurY][mCurX];

            WCHAR szTemp[256] = { 0 };
            wsprintf(szTemp, L"color index : \t %d\n", tColorIndex);
            OutputDebugString(szTemp);

            //퍼즐피스들이 연속색상인지 검토한다
            int tCount = DoCheckBlockAttrib(mCurX, mCurY, tColorIndex);

            //연속된 색상 퍼즐피스가 3개 이상이라면
            if (tCount >= 3)
            {
                WCHAR szTemp[256] = { 0 };
                wsprintf(szTemp, L"conneting block count is over 3---->%d\n", tCount);
                OutputDebugString(szTemp);


                //해당 색상 퍼즐피스들을 없앤다
                for (int tRow = 0; tRow < 5; ++tRow)
                {
                    for (int tCol = 0; tCol < 5; ++tCol)
                    {
                        if(1 == mCheckVisit[tRow][tCol])
                        mBoardAttrib[tRow][tCol] = 0;       //빈칸은 검정색으로 가정
                    }
                }
            }


            //비워진 셀에 새로운 퍼즐피스들을 랜덤하게 생성
            for (int tRow = 0; tRow < 5; ++tRow)
            {
                for (int tCol = 0; tCol < 5; ++tCol)
                {
                    if (0 == mBoardAttrib[tRow][tCol])
                    {
                        //1번 ~ 5번색상까지 랜덤하게 선택하여 퍼즐피스 색상결정
                        int tRandAttrib = rand() % 5 + 1;

                        mBoardAttrib[tRow][tCol] = tRandAttrib;
                    }
                }
            }
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




///////////////////////////////////////////////////





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


int CRyuEngine::DoCheckBlockAttrib(int tCol, int tRow, unsigned int tColorIndex)
{
    int tCount = 0;



    //clear CheckVisit
    for (int tR = 0; tR < 5; ++tR)
    {
        for (int tC = 0;  tC < 5; ++tC)
        {
            mCheckVisit[tR][tC] = 0;
        }
    }





    //clear stack
    while (false == mIntStack.empty())
    {
        mIntStack.pop();
    }


    mIntStack.push(tCol);
    mIntStack.push(tRow);


    while (false == mIntStack.empty())
    {
        //셀의 위치정보를 꺼낸다
        //1개를 꺼낸다.
        tRow = mIntStack.top();
        mIntStack.pop();

        tCol = mIntStack.top();
        mIntStack.pop();

        //이미 칠한 곳이거나 경계라면 아무것도 하지 않고 다음 것으로 넘어간다.
     /*   if (1 == mGrid[tRow][tCol] || 2 == mGrid[tRow][tCol])
        {
            continue;
        }*/


        //경계처리 좌우
        if (tCol < 0 || tCol > 4)
        {
            continue;
        }

        //경계처리 상하
        if (tRow < 0 || tRow > 4)
        {
            continue;
        }

        //선별된 셀의 퍼즐 피스 색상이 주어진 색상이 아니라면
        if (tColorIndex != mBoardAttrib[tRow][tCol])
        {
            continue;
        }

        //이미 검토한 셀이라면
        if (1 == mCheckVisit[tRow][tCol])
        {
            continue;
        }




        //검토한 것을 기억한다
        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"remember block : %d, %d\n", tRow, tCol);
        OutputDebugString(szTemp);

        mCheckVisit[tRow][tCol] = 1;


        //연속된 색상퍼즐피스 갯수를 카운트한다
        ++tCount;



        //4개를 넣는다.
        mIntStack.push(tCol - 1);
        mIntStack.push(tRow);

        mIntStack.push(tCol + 1);
        mIntStack.push(tRow);

        mIntStack.push(tCol);
        mIntStack.push(tRow - 1);

        mIntStack.push(tCol);
        mIntStack.push(tRow + 1);

    }


    return tCount;
}
