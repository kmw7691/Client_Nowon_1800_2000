#include "CDxEngine.h"




HINSTANCE CDxEngine::hInst = nullptr;

CDxEngine::CDxEngine()
{
    memset(szTitle, 0, MAX_LOADSTRING*sizeof(WCHAR));                  // 제목 표시줄 텍스트입니다.
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));            // 기본 창 클래스 이름입니다.
}
CDxEngine::~CDxEngine()
{
}


void CDxEngine::OnCreate()
{
    //MessageBox()
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Create\n");
    OutputDebugStringW(szTemp);

    

}
void CDxEngine::OnDestroy()
{
    

    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Destroy\n");
    OutputDebugStringW(szTemp);

}
void CDxEngine::OnUpdate(float tDeltaTime)
{
    
}


void CDxEngine::Clear(float tR, float tG, float tB)
{
    //XM directX Math
    XMVECTORF32 tColor;
    tColor.f[0] = tR;
    tColor.f[1] = tG;
    tColor.f[2] = tB;

    //render target view를 해당 색상으로 클리어
    mpImmediateContext->ClearRenderTargetView(mpRenderTargetView, tColor);

    //깊이/스텐실버퍼 클리어, 깊이값은 최대 1로 정규화
    mpImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void CDxEngine::Clear(XMVECTORF32 tColor)
{
    mpImmediateContext->ClearRenderTargetView(mpRenderTargetView, tColor);

    //깊이/스텐실버퍼 클리어, 깊이값은 최대 1로 정규화
    mpImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CDxEngine::Present()
{
    //랜더링 수행 명령들을 실제로 수행한다
    //결과적으로 OM에서 모니터로 뿌려진다
    mpSwapChain->Present(0, 0);
}

BOOL CDxEngine::Create(HINSTANCE hInstance, int nCmdShow)
{
    wsprintf(szTitle, L"winAPIShootor");    //매개변수로 받아 설정도 가능하겠다.
    wsprintf(szWindowClass, L"winAPIShootor");    //매개변수로 받아 설정도 가능하겠다.


    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


	return TRUE;
}


MSG CDxEngine::Run()
{
   
    MSG msg = { 0 };


    //mhDC = GetDC(mhWnd);

    InitDevice();

    

    OnCreate();


    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);


    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);
            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
            mTime = tTime;

           

            OnUpdate(mDeltaTime);

        }
    }

    OnDestroy();



    CleanupDevice();

    //ReleaseDC(mhWnd, mhDC);


    return msg;
}









//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM CDxEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // nullptr;//WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPITRANING00));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPITRANING00);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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
BOOL CDxEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.



    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    if (!mhWnd)
    {
        return FALSE;
    }


    SetWindowText(mhWnd, L"CAPIEngine test titlebar text");

    
    RECT tRect = { 0,0,800,600 };
    //다음 함수를 호출하면 타이틀바, 메뉴 등까지 고려하여 다시 계산해준다
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);

    //윈도우 크기를 설정한다
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);



    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}



LRESULT CALLBACK CDxEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
   
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    case WM_TIMER:
    {
        OutputDebugString(L">>>>>>WM_TIMER Enemy DoFire~!!!!!\n");
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


HRESULT CDxEngine::InitDevice()
{
    HRESULT hr = S_OK;



    //win api
    RECT rc;
    GetClientRect(mhWnd, &rc);
    UINT width      = rc.right - rc.left;
    UINT height     = rc.bottom - rc.top;




    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,       //그래픽 카드 장치 하드웨어에서 랜더링 처리
        D3D_DRIVER_TYPE_WARP,           //'고속 성능'의 '소프트웨어 랜더링 처리'. HARDWARE에서 온전히 랜더링 처리가 이루어지지 못하는 경우 최선의 방법으로 소프트웨어적으로 랜더링 처리
        D3D_DRIVER_TYPE_REFERENCE,      //CPU에서 완전히 소프트웨어적으로 랜더링 처리, 매우 느림, 개발용( 앞에 단계의 드라이버들이 모두 실패해도 이것으로 가능 )
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    //피처 레벨: DirectX버전별로 존재하는 임의의 기능집합
    //그래픽 카드에서 지원하는 DirectX기능집합
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,     //DirectX11.1버전
        D3D_FEATURE_LEVEL_11_0,     //DirectX11버전
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);   //ARRAYSIZE 해당 배열의 크기를 얻는 매크로 함수
    //드라이버 종류 갯수만큼 순회
    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        mDriverType = driverTypes[driverTypeIndex];
        //드라이버 타입 과 피처레벨 등을 기반으로 '디바이스'와 '디바이스 컨텍스트'( 랜더링을 담당하는 그래픽 카드 객체 ) 를 만든다.
        hr = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &mpd3dDevice, &mFeatureLevel, &mpImmediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &mpd3dDevice, &mFeatureLevel, &mpImmediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    //DXGI: DirectX Graphic Infra
    // 다이렉트 엑스가 제공하는 그래픽 처리를 위한 일반적인 '기반이 되는 구조'
    // Obtain DXGI factory from device (since we used nullptr for pAdapter above)


    //COM: 바이너리 단위의 호환가능한 부품
    //DirectX도 COM기술을 기반으로 만들어져 있다. 
    //__uuidof 임의의 COM객체의 식별자를 얻는 연산자이다.

    
    //C++에서 제공하는 형변환 연산자
    // static_cast<T>: 정적 형변환
    // dynamic_cast<T>: 동적 형변환
    // const_cast<T>: 상수속성을 제거하는 형변환
    // reinterpret_cast<T>: C++의 형변환 연산자 중 하나. 어느 타입이라도 형변환 가능하다

    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = mpd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;        //그래픽 처리장치(그래픽 카드)를 추상화해놓은 객체, DXGI에서 다루는 개념 
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
    if (FAILED(hr))
        return hr;

    // Create swap chain
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = mpd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&mpd3dDevice1));
        if (SUCCEEDED(hr))
        {
            (void)mpImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&mpImmediateContext1));
        }
        //스왑체인 구조에 대한 설명 정보  작성
        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;                       //버퍼의 너비
        sd.Height = height;                     //버퍼의 높이
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //32비트 색상 정보를 사용
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;                     //back buffer의 갯수
        //스왑체인 객체 생성
        hr = dxgiFactory2->CreateSwapChainForHwnd(mpd3dDevice, mhWnd, &sd, nullptr, nullptr, &mpSwapChain1);
        if (SUCCEEDED(hr))
        {
            hr = mpSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&mpSwapChain));
        }

        dxgiFactory2->Release();
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = mhWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(mpd3dDevice, &sd, &mpSwapChain);
    }
    //풀스크린 전환 단축키 Alt+Enter는 사용하지 않겠다.
    // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
    dxgiFactory->MakeWindowAssociation(mhWnd, DXGI_MWA_NO_ALT_ENTER);

    dxgiFactory->Release();

    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = mpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
        return hr;
    //back buffer를 Render Target View로 만든다.
    //여기서 View라는 개념은 DirectX에서 이미지 데이터를 쓸수 있는 임의의 메모리 를 지칭하는 용어이다.
    hr = mpd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mpRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    //OM: Output Merger 의 줄임말
    //Output Merger에 Render Target View를 설정한다
    mpImmediateContext->OMSetRenderTargets(1, &mpRenderTargetView, nullptr);




    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width                     = width;
    descDepth.Height                    = height;
    descDepth.MipLevels                 = 1;
    descDepth.ArraySize                 = 1;
    descDepth.Format                    = DXGI_FORMAT_D24_UNORM_S8_UINT;//깊이버퍼24, 스텐실8 -->32,      [0,1]의 값으로 정규화되어있다.
    descDepth.SampleDesc.Count          = 1;    //샘플링은 텍스쳐를 다룰때 보자
    descDepth.SampleDesc.Quality        = 0;
    descDepth.Usage                     = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags                 = D3D11_BIND_DEPTH_STENCIL; //깊이/스텐실 버퍼용이다
    descDepth.CPUAccessFlags            = 0;
    descDepth.MiscFlags                 = 0;
    //DirectX에서 깊이/스텐실버퍼는 '텍스쳐' 리소스의 한 종류로 취급한다        
    mpd3dDevice->CreateTexture2D(&descDepth, nullptr, &mpDepthStencil);


    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format              = descDSV.Format;
    descDSV.ViewDimension       = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice  = 0;

    //깊이/스텐실 뷰를 만든다
    mpd3dDevice->CreateDepthStencilView(mpDepthStencil, &descDSV, &mpDepthStencilView);

    //랜더타겟뷰에 깊이스텐실 뷰 설정
    mpImmediateContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);




    // Setup the viewport
    //뷰포트를 설정한다
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    mpImmediateContext->RSSetViewports(1, &vp); //RS Render State

    return S_OK;
}

void CDxEngine::CleanupDevice()
{
    //랜더링 상태들을 클리어
    if (mpImmediateContext) mpImmediateContext->ClearState();

    //객체들을 릴리즈(해제)
    if (mpRenderTargetView) mpRenderTargetView->Release();
    if (mpSwapChain1) mpSwapChain1->Release();
    if (mpSwapChain) mpSwapChain->Release();
    if (mpImmediateContext1) mpImmediateContext1->Release();
    if (mpImmediateContext) mpImmediateContext->Release();
    if (mpd3dDevice1) mpd3dDevice1->Release();
    if (mpd3dDevice) mpd3dDevice->Release();
}


HRESULT CDxEngine::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    //셰이더 소스코드 파일을 컴파일해주는 함수
    //Shader SourceCode File ----> 컴파일 ----> 바이트 코드ByteCode (중간결과물)
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}
