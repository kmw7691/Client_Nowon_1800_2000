#pragma once
#include <windows.h>
#define MAX_LOADSTRING 100

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
	static HINSTANCE hInst;

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
};