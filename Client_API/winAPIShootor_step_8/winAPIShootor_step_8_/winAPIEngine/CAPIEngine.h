#pragma once

#include <windows.h>

#include "SVector2D.h"
#include "CUnit.h"

#include "CCollisionMgr.h"

#define MAX_LOADSTRING 100

//Ŭ���� ���漱��, Ŭ������ �̸��� �˷��ش�.
//������ ������ ũ��� �����Ϸ��� �̹� �˰� �ֱ� ������ 
//������ ǥ���̴�.
class CTexture;

class CAPIEngine
{
public:

	CAPIEngine();
	virtual ~CAPIEngine();	//����Ҹ��� 

	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	//ryu	
	virtual void OnCreate();
	virtual void OnDestroy();

	virtual void OnUpdate(float tDeltaTime);

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




	//������ ������ �������� ref ������ �������� �ʰڴ�.
	template<typename T>
	T* CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
	{
		T* tpPrefab = new T();

		//tpPrefab->SetEngine(this);
		tpPrefab->Create(this);
		tpPrefab->SetTexture(tpTex);
		tpPrefab->SetAnchors(tAnchorX, tAnchorY);
		tpPrefab->SetPosition(tPosition);
		
		//����
		tpPrefab->SetColliderPosition();

		tpPrefab->SetIsActive(true);	//Ȱ���� �⺻������ �ϰڴ�.

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




	//��������� ��������� �����ϱ� ���ؼ� private�� ���������Ͽ���.
private:
	CAPIEngine(const CAPIEngine& tEngine) {};
	CAPIEngine& operator=(const CAPIEngine& tEngine) {};

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	//�������� ������ �������� �ش� ����Լ����� static ���� �����ߴ�.
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	//static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


public:
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.

	//��������Լ��� WndProc���� ����ϰ� �����Ƿ� static���� �����ߴ�.
	//static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
	HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.


	//OnUpdate���� �׸��⸦ �����ϱ� ���� ����
	HWND mhWnd;
	HDC mhDC;


	CTexture* mpBackBuffer = nullptr;



	//�ð���������� ���� �����Ӵ� �ð�

	//�ð���� ������ ���� 
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime = 0.0f;
};

