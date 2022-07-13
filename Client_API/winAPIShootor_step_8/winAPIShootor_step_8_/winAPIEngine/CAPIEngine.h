#pragma once

#include <windows.h>

#include "SVector2D.h"
#include "CUnit.h"

#include "CCollisionMgr.h"

#define MAX_LOADSTRING 100

//클래스 전방선언, 클래스의 이름만 알려준다.
//포인터 변수의 크기는 컴파일러가 이미 알고 있기 때문에 
//가능한 표현이다.
class CTexture;

class CAPIEngine
{
public:

	CAPIEngine();
	virtual ~CAPIEngine();	//가상소멸자 

	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	//ryu	
	virtual void OnCreate();
	virtual void OnDestroy();

	virtual void OnUpdate(float tDeltaTime);

	//원그리기 기능은 엔진에서 구현
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	//화면을 클리어하는 함수
	void Clear(float tR = 1.0f, float tG = 1.0f, float tB = 1.0f);

	void Present();



	float GetDeltaTime() const
	{
		return mDeltaTime;
	}




	//프리팹 생성과 해지에는 ref 개념을 적용하지 않겠다.
	template<typename T>
	T* CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
	{
		T* tpPrefab = new T();

		//tpPrefab->SetEngine(this);
		tpPrefab->Create(this);
		tpPrefab->SetTexture(tpTex);
		tpPrefab->SetAnchors(tAnchorX, tAnchorY);
		tpPrefab->SetPosition(tPosition);
		
		//땜빵
		tpPrefab->SetColliderPosition();

		tpPrefab->SetIsActive(true);	//활성을 기본값으로 하겠다.

		return tpPrefab;
	}

	void DestroyPrefab(CUnit*& tPrefab)
	{
		//SAFE_DELETE(tPrefab)
		if (nullptr != tPrefab)
		{
			tPrefab->Destroy();

			delete tPrefab;
			tPrefab = nullptr;
		}
	}

	template<typename T>
	T* InstantObject(CUnit* tpPrefab)
	{
		T* tpUnit = nullptr;

		tpUnit = static_cast<T*>(tpPrefab->clone());
		//tpUnit->AddRef();
		//tpUnit->Release();


		CCollisionMgr::GetInst()->AddUnit(tpUnit);
		
		return tpUnit;
	}

	template<typename T>
	void DestroyObject(T*& tUnit)
	{
		//CCollisionMgr::GetInst()->Delete


		if (nullptr != tUnit)
		{
			tUnit->Release();
			tUnit = nullptr;
		}
	}




	//복사생성과 복사대입을 금지하기 위해서 private로 접근제한하였다.
private:
	CAPIEngine(const CAPIEngine& tEngine) {};
	CAPIEngine& operator=(const CAPIEngine& tEngine) {};

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	//전역적인 성격을 가지도록 해당 멤버함수들을 static 예약어를 적용했다.
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	//static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


public:
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.

	//정적멤버함수인 WndProc에서 사용하고 있으므로 static예약어를 적용했다.
	//static HINSTANCE hInst;                                // 현재 인스턴스입니다.
	HINSTANCE hInst;                                // 현재 인스턴스입니다.


	//OnUpdate에서 그리기를 수행하기 위해 선언
	HWND mhWnd;
	HDC mhDC;


	CTexture* mpBackBuffer = nullptr;



	//시간기반진행을 위한 프레임당 시간

	//시간기반 진행을 위해 
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime = 0.0f;
};

