// winAPITraning00.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

/*
    Window API
    윈도우 운영체제에서 제공하는 기능들을 다룰 수 있는 API( Application Programming Interface )


    DirectX API
    그래픽 카드 장치를 빠르게 접근하여 제공하는 기능들을 다룰 수 있는 API
*/

#include "framework.h"

#include "CDxEngine.h"

using namespace std;

class CRyuEngine : public CDxEngine
{   
public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};

    virtual void OnCreate() override
    {
        CDxEngine::OnCreate();
    }
    virtual void OnDestroy() override
    {
        
        CDxEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CDxEngine::OnUpdate(tDeltaTime);


        //this->Clear(0.1f, 0.1f, 0.3f);    
        this->Clear(Colors::MediumPurple);

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


