// winAPITraning00.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//



#include "framework.h"
#include <stack>
#include <list>
#include <time.h>
#include "CPathMgr.h"
#include "CResourcesMgr.h"

using namespace std;

#pragma comment(lib, "winAPIEngine.lib")


//STL 이 제공하는 컨테이너 중에서 스택을 이용하였다
typedef stack<int> CIntStack;



class CRyuEngine : public CAPIEngine
{

public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};

    int DoCheckBlockAttrib(int tCol, int tRow, unsigned int tColorIndex);

    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();

    }
    virtual void OnDestroy() override
    {
       
        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);

        //render
        this->Clear(0.1f, 0.1f, 0.3f);       
        

        // 정점의 나열 순서는 (0,1),(0,100),(100,0) 으로 CCW가정                       CCW : Counter Clock Wise(반시계)
        DrawTriangle(0.0f,0.0f,
                     0.0f,100.0f,
                     100.0f,0.0f );

        DrawTriangle(200.0f, 200.0f,
            200.0f, 300.0f,
            300.0f, 200.0f);

        FillTriangle(400.0f, 400.0f,
            400.0f, 500.0f,
            500.0f, 400.0f);

        


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
