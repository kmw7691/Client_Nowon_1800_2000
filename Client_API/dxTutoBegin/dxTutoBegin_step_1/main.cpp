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

//이것은 정점을 나타내는 구조체의 정의이다
//float 데이터 3개로 구성된 벡터이다
// 이 정의는 시스템 메모리에 만들 데이터의 형식을 정의하는 것이다
struct SimpleVertex
{
    XMFLOAT3 Pos;
    //XMFLOAT4 Pos;
};



class CRyuEngine : public CDxEngine
{   
    ID3D11VertexShader* mpVertexShader = nullptr;   //vertex shader 담당 객체
    ID3D11PixelShader* mpPixelShader = nullptr;     //pixel shader 담당 객체

    ID3D11InputLayout* mpVertexLayout = nullptr;    //input layout 객체
    //랜더링에 사용할 자원
    ID3D11Buffer* mpVertexBuffer = nullptr;         //비디오램에 있는 임의의 데이터, 이 예시에서는 삼각형 데이터를 담을 것이다


public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};

    virtual void OnCreate() override
    {
        CDxEngine::OnCreate();

        HRESULT hr = S_OK;


        /*
                HLSL : High Level Shader Language : 마이크로 소프트에서 만든 DirectX용 셰이더 언어

                GLSL : Open GL용 셰이더 언어
                CG : 엔디비아에서 ㅁ나든 셰이더 언어
        */

        //compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        //셰이더 소스코드를 컴파일하며 'Blob'객체에 담는다(담긴 내용은 Byte Code형식이다)
        hr = CompileShaderFromFile(L"VertexShader.hlsl", "main", "vs_4_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
           // return hr;
        }

        // Create the vertex shader
        //Vertex Shader 객체를 생성한다(Blob 객체를 참고하여 만든다)
        hr = mpd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &mpVertexShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
           // return hr;
        }



        //SEMENTIC 시맨틱 : 셰이더(랜더링파이프라인)에서 어떤 용도이냐를 나타내는 꼬리표
        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            //시맨틱 이름, 시맨틱 인덱스, 타입, 정점버퍼메모리의 슬롯인덱스(0~15), 오프셋, 고급옵션, 고급옵션
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        UINT numElements = ARRAYSIZE(layout);

 /*       D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = ARRAYSIZE(layout);*/

        // Create the input layout
        hr = mpd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
            pVSBlob->GetBufferSize(), &mpVertexLayout);
        pVSBlob->Release();
        //if (FAILED(hr))
           // return hr;

        // Set the input layout
        mpImmediateContext->IASetInputLayout(mpVertexLayout);









        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        //셰이더 소스코드를 컴파일하며 'Blob'객체에 담는다(담긴 내용은 Byte Code형식이다)
        hr = CompileShaderFromFile(L"PixelShader.hlsl", "main", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            //return hr;
        }


        // Create the pixel shader
        //Pixel Shader 객체( mpVertexShader )를 생성한다(Blob 객체를 참고하여 만든다)
        hr = mpd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &mpPixelShader);
        pPSBlob->Release();


        ////삼각형의 정점 3개의 데이터를 설정
        ////지역변수(시스템 메모리에 있는 것이다)
        SimpleVertex vertices[] = 
        {
            XMFLOAT3(0.0f,0.0f,0.5f),   //생성자 호출
            XMFLOAT3(0.0f,1.0f,0.5f),
            XMFLOAT3(1.0f,0.0f,0.5f)
        };

        D3D11_BUFFER_DESC bd = {};
        bd.Usage                    = D3D11_USAGE_DEFAULT;      //버퍼는 기본용도 버퍼로 사용하겠다
        bd.ByteWidth                = sizeof(SimpleVertex)*3;   //정점 세개 크기의 데이터이다
        bd.BindFlags                = D3D11_BIND_VERTEX_BUFFER; //vertex buffer용도로 사용하겠다
        bd.CPUAccessFlags           = 0;                        //cpu의 접근은 불허한다

        D3D11_SUBRESOURCE_DATA InitData = {};
        InitData.pSysMem = vertices;

        //bd와 InitData를 찹고하여 mpVertexBuffer를 생성한다
        //vertexbuffer는 기하도형을 그리기 위해 필요한 데이터이다
        mpd3dDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);






        UINT stride = sizeof(SimpleVertex);     //메모리를 해석하는 경계
        UINT offset = 0;                        //얼마나 떨어졌는지

        mpImmediateContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

        //mpImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ////도형을 어떤 방식으로 그릴지 방법을 정하는 것이다
        ////여기서는 정점 3개를 모아서 하나의 삼각형을 구성하는 형태로 랜더링한다

    }
    virtual void OnDestroy() override
    {
        if (mpVertexShader) mpVertexShader->Release();
        if (mpPixelShader) mpPixelShader->Release();

        if (mpVertexLayout) mpVertexLayout->Release();

        if (mpVertexBuffer) mpVertexBuffer->Release();





        CDxEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CDxEngine::OnUpdate(tDeltaTime);


        //this->Clear(0.1f, 0.1f, 0.3f);    
        this->Clear(Colors::MediumPurple);

        //vertex shader 단계에 vertex shader 객체 설정
        mpImmediateContext->VSSetShader(mpVertexShader, nullptr, 0);
        //pixel shader 단계에 pixel shader 객체 설정
        mpImmediateContext->PSSetShader(mpPixelShader, nullptr, 0);

        //장치즉시컨텍스트에게 정점버퍼의 내용을(기하도형) 기반으로 그리라고 (랜더링을)지시한다
        mpImmediateContext->Draw(3, 0);
        //GPU에 보낼 정점의 갯수, 보내기 시작할 첫번째 정점의 인덱스

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


