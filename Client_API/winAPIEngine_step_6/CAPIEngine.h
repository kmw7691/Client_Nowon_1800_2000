#pragma once
#include <windows.h>

#define MAX_LOADSTRING 100


class CTexture;

//Ŭ���� ���漱��, Ŭ������ �̸��� �˷��ش�.
//�����ͺ����� ũ��� �����Ϸ��� �̹� �˰��ֱ� ������
//������ ǥ���̴�
class CAPIEngine
{
public:

	CAPIEngine();
	virtual ~CAPIEngine(); // ����Ҹ���

	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	virtual void onCreate();
	virtual void onDestroy();
	virtual void onUpdate();


	//���׸��� ����� �������� ����
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	//ȭ���� Ŭ�����ϴ� �Լ�
	void Clear();
	void Present();


	// ��������� ��������� �����ϱ� ���� private�� ��������
private:
	CAPIEngine(const CAPIEngine& tEngnine) {};
	CAPIEngine& operator = (const CAPIEngine& tEngnine) {};

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	// �������� ������ �������� �ش� ����Լ����� static���� ����
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	// ���� ����Լ��� WndProc���� ����ϰ� �����Ƿ� static���� ����
	HINSTANCE hInst;

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];


	// onUpdate�� �����ϱ����� ����
	HWND mhWnd;
	HDC mhDC;


	CTexture* mpBackBuffer = nullptr;
};