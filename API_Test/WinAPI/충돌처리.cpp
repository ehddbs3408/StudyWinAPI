// WinAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "WinAPI.h"
#include <math.h>

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
POINT g_ptObjPos1 = { 100,100 };
POINT g_ptObjPos2 = { WINSIZEX / 2,WINSIZEY / 2 };
RECT g_rtBox1;
RECT g_rtBox2;
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
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, NULL, NULL);
        break;

    case WM_KEYDOWN:
    {

    }
    break;
    case WM_LBUTTONDOWN:
    {

    }
    break;
    case WM_LBUTTONUP:
    {

    }
    break;

    case WM_TIMER:
    {
        g_rtBox1 = RECT_MAKE(g_ptObjPos1.x, g_ptObjPos1.y, 100);
        g_rtBox2 = RECT_MAKE(g_ptObjPos2.x, g_ptObjPos2.y, 100);
        RECT rt;
        if (IntersectRect(&rt, &g_rtBox1, &g_rtBox2))// �浹ó�� �Լ�;
        {
            switch (eMoveDir)
            {
            case MOVE_DIR::MOVE_LEFT:
                g_ptObjPos2.x -= fMoveSpeed;
                break;
            case MOVE_DIR::MOVE_RIGHT:
                g_ptObjPos2.x += fMoveSpeed;
                break;
            case MOVE_DIR::MOVE_UP:
                g_ptObjPos2.y -= fMoveSpeed;
                break;
            case MOVE_DIR::MOVE_DOWN:
                g_ptObjPos2.y += fMoveSpeed;
                break;
            default:
                break;
            }
        }
        InvalidateRect(hWnd, nullptr, true);

    }
    break;

    case WM_MOUSEMOVE:
    {
    }
    break;

    case WM_CHAR:
    {
        hdc = GetDC(hWnd);
        if (wParam == 'w')
        {
            g_ptObjPos1.y -= (g_ptObjPos1.y >= fMoveSpeed) ? fMoveSpeed : 0;
            eMoveDir = MOVE_DIR::MOVE_UP;
        }
        if (wParam == 's')
        {
            g_ptObjPos1.y += (g_ptObjPos1.y <= WINSIZEY - fMoveSpeed) ? fMoveSpeed : 0;
            eMoveDir = MOVE_DIR::MOVE_DOWN;
        }
        if (wParam == 'a')
        {
            g_ptObjPos1.x -= (g_ptObjPos1.x >= fMoveSpeed) ? fMoveSpeed : 0;
            eMoveDir = MOVE_DIR::MOVE_LEFT;
        }
        if (wParam == 'd')
        {
            g_ptObjPos1.x += (g_ptObjPos1.x <= WINSIZEX - fMoveSpeed) ? fMoveSpeed : 0;
            eMoveDir = MOVE_DIR::MOVE_RIGHT;
        }
        InvalidateRect(hWnd, nullptr, true);
        ReleaseDC(hWnd, hdc);
    }
    break;
    // Ŀ�� ������Ʈ (�����찡 ������ ������Ʈ):-> �ڵ�(�ڵ�� �� ������Ʈ�� �����Ѵ�.)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        RECT_DRAW(g_rtBox1);
        RECT_DRAW(g_rtBox2);
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
