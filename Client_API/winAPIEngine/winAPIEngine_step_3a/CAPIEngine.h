#pragma once
#include <windows.h>
#define MAX_LOADSTRING 100

class CAPIEngine
{
public:
	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	// �������� ������ �������� �ش� ����Լ����� static���� ����
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	// ���� ����Լ��� WndProc���� ����ϰ� �����Ƿ� static���� ����
	static HINSTANCE hInst;

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
};

