#pragma once
#include <windows.h>

#define MAX_LOADSTRING 100


class CTexture;

//클래스 전방선언, 클래스의 이름만 알려준다.
//포인터변수의 크기는 컴파일러가 이미 알고있기 때문에
//가능한 표현이다
class CAPIEngine
{
public:

	CAPIEngine();
	virtual ~CAPIEngine(); // 가상소멸자

	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	virtual void onCreate();
	virtual void onDestroy();
	virtual void onUpdate();


	//원그리기 기능은 엔진에서 구현
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	//화면을 클리어하는 함수
	void Clear();
	void Present();


	// 복사생성과 복사대입을 금지하기 위해 private로 접근제한
private:
	CAPIEngine(const CAPIEngine& tEngnine) {};
	CAPIEngine& operator = (const CAPIEngine& tEngnine) {};

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	// 전역적인 성격을 가지도록 해당 멤버함수들을 static예약어를 적용
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	// 정적 멤버함수인 WndProc에서 사용하고 있으므로 static예약어를 적용
	HINSTANCE hInst;

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];


	// onUpdate를 수행하기위해 선언
	HWND mhWnd;
	HDC mhDC;


	CTexture* mpBackBuffer = nullptr;
};