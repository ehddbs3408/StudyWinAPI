// WinAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "WinAPI.h"
#include <math.h>
#include <vector>

#define MAX_LOADSTRING 100
// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.


#define RECT_MAKE(x,y,s) {x - s/2,y-s/2,x+s/2,y+s/2}
#define RECT_DRAW(rt) Rectangle(hdc,rt.left,rt.top,rt.right,rt.bottom)
// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
POINT g_ptObjPos1 = { WINSIZEX / 2,WINSIZEY - 30 };
RECT g_rtBox1;
vector<RECT> vecBox;
enum class MOVE_DIR
{
    MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN
};
MOVE_DIR eMoveDir;
int fMoveSpeed = 40;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI)); //����� ����

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // msg.message == WM_QUIT 
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //������ â ����� ����
    wcex.lpfnWndProc = WndProc; //�Լ� ������
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //���α׷� �ּҰ�
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI)); //������
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS); // Ŀ��
    wcex.hbrBackground = (HBRUSH)(BLACK_BRUSH); //��׶��� ��
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI); //�޴�â ���� �̸�
    wcex.lpszClassName = szWindowClass; //������ â�� �̸�
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
int Resolutionx = GetSystemMetrics(SM_CXSCREEN);
int Resolutiony = GetSystemMetrics(SM_CYSCREEN);

int WinposX = Resolutionx / 2 - WINSIZEX / 2;
int WinposY = Resolutiony / 2 - WINSIZEY / 2;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.



    HWND hWnd = CreateWindowW(szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        WinposX,            //������ ȭ�� ���� ��� ��ǥ x
        WinposY,                                     //������ ȭ�� ���� ��� ��ǥ y
        WINSIZEX,                        //������ ���� ������
        WINSIZEY,                                     //�޵��� ���� ������
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static bool isClick;
    static RECT schoolRect = { 100,100,150,150 };
    static RECT meRect;
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 10, NULL);
        isClick = false;
        srand((unsigned int)time(nullptr));
        break;

    case WM_TIMER:
    {
        if (isClick)
        {
            schoolRect.right = schoolRect.left + 50;
            schoolRect.bottom = schoolRect.top + 50;
            if (meRect.left>schoolRect.left)
                schoolRect.left += 1;
            else
                schoolRect.left -= 1;
            if (meRect.top > schoolRect.top)
                schoolRect.top += 1;
            else
                schoolRect.top -= 1;
            InvalidateRect(hWnd, nullptr, true);
       }
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (isClick)
        {
            meRect = { LOWORD(lParam),HIWORD(lParam),LOWORD(lParam) + 30,HIWORD(lParam) + 30 };
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        isClick = true;
        meRect = { LOWORD(lParam),HIWORD(lParam),LOWORD(lParam) + 30,HIWORD(lParam) + 30 };
    }
    break;
    case WM_LBUTTONUP:
    {
        isClick = false;
    }
    break;
    case WM_CHAR:
    {
        hdc = GetDC(hWnd);

        InvalidateRect(hWnd, nullptr, true);
        ReleaseDC(hWnd, hdc);
    }
    break;
    // Ŀ�� ������Ʈ (�����찡 ������ ������Ʈ):-> �ڵ�(�ڵ�� �� ������Ʈ�� �����Ѵ�.)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        DrawText(hdc, L"�׸���", wcslen(L"�׸���"), &schoolRect, DT_CENTER);
        if(isClick)
            DrawText(hdc, L"��", wcslen(L"��"), &meRect, DT_CENTER);
        EndPaint(hWnd, &ps);
    }


    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        KillTimer(hWnd, 1);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
