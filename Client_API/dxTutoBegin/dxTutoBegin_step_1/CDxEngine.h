#pragma once

#include "framework.h"

#define MAX_LOADSTRING 100

class CDxEngine
{
public:
	CDxEngine();
	virtual ~CDxEngine();

private:
	CDxEngine(const CDxEngine&) {};

	CDxEngine& operator=(const CDxEngine&) {};


public:
	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();


	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate(float tDeltaTime);

	void Clear(float tR = 0.0f, float tG = 0.0f, float tB = 0.0f);
	void Clear(XMVECTORF32 tColor);
	void Present();

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	
	float GetDeltaTime() const
	{
		return mDeltaTime;
	}


	HINSTANCE GetHInst() const
	{
		return hInst;
	}
	HDC GetHDC() const
	{
		return mhDC;
	}

	int ScreenWidth()
	{
		return 800;
	}
	int ScreenHeight()
	{
		return 600;
	}

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);


	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	

protected:
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

	static HINSTANCE hInst;                                // 현재 인스턴스입니다.

	HWND mhWnd;
	HDC mhDC;

protected:
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime;





	//D3D: Direct3D
	//드라이버: 하드웨어에 밀착된 소프트웨어
	D3D_DRIVER_TYPE         mDriverType = D3D_DRIVER_TYPE_NULL;				//드라이버 프로그램의 종류
	D3D_FEATURE_LEVEL       mFeatureLevel = D3D_FEATURE_LEVEL_11_0;			//피처레벨: 임의의 장치가 지원하는 DirectX의 기능집합 수준

	//디바이스(장치): 그래픽 처리장치(그래픽 카드)를 추상화해놓은 객체: 멀티스레딩(명령문을 동시처리하는 기능)을 고려하지 않는다
	ID3D11Device* mpd3dDevice = nullptr;			
	ID3D11Device1* mpd3dDevice1 = nullptr;

	//디바이스 컨텍스트(장치 컨텍스트): 그래픽 처리장치(그래픽 카드)를 추상화해놓은 객체: 멀티스레딩(명령문을 동시처리하는 기능)을 고려하여 디바이스 개념과 분리되어 있다.
	ID3D11DeviceContext* mpImmediateContext = nullptr;
	ID3D11DeviceContext1* mpImmediateContext1 = nullptr;

	//스왑체인: 더블버퍼링 구조가 존재하고 이 두 버퍼가 서로 교환되는 구조의 추상화된 객체이다
	//window api때 수동으로 작성해본 더블 버퍼 구조는 버퍼 두개가 존재하고 ( back buffer, front buffer) back buffer에서 front buffer로 이미지 데이터를 복사하는 형태로 작동했었다면 
	//여기 DirectX에서 제공하는 더블버퍼는 좀더 진화된 개념으로써 
	//이 두 버퍼가 서로 교환된다
	//이러한 동작이 마치 사슬처럼 보여 
	//SwapChain 이라 명명되었다 
	IDXGISwapChain* mpSwapChain = nullptr;
	IDXGISwapChain1* mpSwapChain1 = nullptr;

	//랜더 타겟 뷰 객체는 back buffer후면버퍼를 이미지 데이터를 랜더링할수 있는 형태로 추상화해놓은 객체이다 
	ID3D11RenderTargetView* mpRenderTargetView = nullptr;


public:
	HRESULT InitDevice();
	void CleanupDevice();

};

