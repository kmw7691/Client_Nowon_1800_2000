#pragma once
#include <windows.h>
#include "SVector2D.h"
#include "CUnit.h"

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
	virtual void onUpdate(float tDeltaTime);


	//���׸��� ����� �������� ����
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	//ȭ���� Ŭ�����ϴ� �Լ�
	void Clear(float tR = 1.0f, float tG = 1.0f, float tB = 1.0f);


	void Present();


	float GetDeltaTime() const
	{
		return mDeltaTime;
	}



	template<typename T>
	T* CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
	{
		T* tpPrefab = new T();

		//tpPrefab->SetEngine(this);
		tpPrefab->Create(this);
		tpPrefab->SetTexture(tpTex);
		tpPrefab->SetAnchors(tAnchorX, tAnchorY);
		tpPrefab->SetPosition(tPosition);

		return tpPrefab;
	}

	void DestroyPrefab(CUnit*& tPrefab)
	{
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

		return tpUnit;
	}

	template<typename T>
	void DestroyObject(T*& tUnit)
	{
		if (nullptr != tUnit)
		{
			tUnit->Release();
			tUnit = nullptr;
		}
	}



	// ��������� ��������� �����ϱ� ���� private�� ��������
private:
	CAPIEngine(const CAPIEngine& tEngnine) {};
	CAPIEngine& operator = (const CAPIEngine& tEngnine) {};

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	// �������� ������ �������� �ش� ����Լ����� static���� ����
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	//static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	// ���� ����Լ��� WndProc���� ����ϰ� �����Ƿ� static���� ����
	HINSTANCE hInst;

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];


	// onUpdate�� �����ϱ����� ����
	HWND mhWnd;
	HDC mhDC;


	CTexture* mpBackBuffer = nullptr;

	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;



	//�ð���������� ���� �����Ӵ� �ð�
	float mDeltaTime = 0.0f;
};