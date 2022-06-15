#include "CAPIEngine.h"
#include "Resource.h"


HINSTANCE CAPIEngine::hInst = nullptr;




CAPIEngine::CAPIEngine()
{
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));

    memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
}

CAPIEngine::~CAPIEngine()
{
}

BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow)
{
    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

   // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIENGINESTEP0, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    return TRUE;
}

void CAPIEngine::onCreate()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::Create\n");
    OutputDebugString(szTemp);
}

void CAPIEngine::onDestroy()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::Destroy\n");
    OutputDebugString(szTemp);
}

void CAPIEngine::onUpdate()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPIEngine::OnUpdate\n");
    OutputDebugString(szTemp);
}



MSG CAPIEngine::Run()
{
    MSG msg = { 0 };




    mhDC = GetDC(mhWnd);

    onCreate();

    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));


    //    MSG msg;

        //// �⺻ �޽��� �����Դϴ�:
        //while (GetMessage(&msg, nullptr, 0, 0))
        //{
        //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        //    {
        //        TranslateMessage(&msg);
        //        DispatchMessage(&msg);
        //    }
        //}

    // �� ������ �������α׷��� ���� ó���� if������ 
    // �� �ܿ� idle time�� ���Ӽ����� ����ó���� ���ڴ� ��� ����
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //���ӷ��������� �⺻������ �ۼ��Ͽ���
            //OutputDebugString(L"game loop\n");
            onUpdate();
        }
    }

    onDestroy();


    ReleaseDC(mhWnd, mhDC);


    // return (int)msg.wParam;

    return msg;
}



ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;     // lpfnWndProc�� �����Լ��� �Լ�������
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIENGINESTEP0));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIENGINESTEP0);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);

    return ATOM();
}

BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }

    // Ŭ���̾�Ʈ ������ ũ�⸦ �̰����� �����̴�
    RECT tRect = { 0,0,800,600 };
    // Ÿ��Ʋ��, �޴� ���� ����Ͽ� ��ü ������ ������ �ٽ� ������ش�
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);





    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;

    return 0;
}

LRESULT CALLBACK  CAPIEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // DC (Device Context)�� handle :DC�� �׸��⿡ ����ϴ� ��ġ (��ġ, ��ġ�� ���õ� ������, ��ġ�� ���� ��)�� �߻�ȭ �س��� ���̴�
        HDC hdc = BeginPaint(hWnd, &ps); // �׸����� ����
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...


        //TextOut(hdc, 0, 0, L"test text output.", 17);
        //TextOut(hdc, 0, 25, L"�ȳ��ϼ���. ���ο��Դϴ�.", 13);
        //TextOut(hdc, 0, 50, L"I am a good boy.", 16);

        //LPCWSTR tString = TEXT("WCHAR Test");
        //TextOut(hdc, 0, 100, tString, 10);


        ////�簢�� �׸���
        //Rectangle(hdc, 200, 200, 200 + 100, 200 + 50);


        //// ���� �׸���
        //MoveToEx(hdc, 350, 200, NULL); // ������
        //LineTo(hdc, 450, 300); // ����

        //MoveToEx(hdc, 200, 50, NULL); // ������
        //LineTo(hdc, 400, 100); // ����
        //LineTo(hdc, 200, 150); // ����


        //// ���׸���
        //Ellipse(hdc, 400, 100, 400 + 100, 100 + 100);




        // WM_PAINT������ �޽����� �÷��׼� �޽�����
        // WM_PAINT�� �߻��ϸ� �÷��׺����� 1�� �����ȴ�
        // ����, �� �÷��� ������ ���� ��� 1�̸�, ��� WM_PAINT �޽����� �߻���Ų��
        // (�׸��⸦ �ؾ��ϴµ� ó������ �ʾұ� ����)
        // �׷��� CPU������ ��Ƹ԰Եȴ�
        // ENDPAINT�� ȣ��Ǹ� �̷��� �÷��� ������ ���� 0���� �����Ѵ�

        EndPaint(hWnd, &ps); //  �׸��� ��尡 �����ٴ� �ǹ�
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK  CAPIEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



void CAPIEngine::DrawCircle(float tX, float tY, float tRadius)
{
    Ellipse(mhDC, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
}