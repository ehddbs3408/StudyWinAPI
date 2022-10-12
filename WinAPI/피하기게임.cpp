// WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI.h"
#include <math.h>
#include <vector>

#define MAX_LOADSTRING 100
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


#define RECT_MAKE(x,y,s) {x - s/2,y-s/2,x+s/2,y+s/2}
#define RECT_DRAW(rt) Rectangle(hdc,rt.left,rt.top,rt.right,rt.bottom)

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

POINT g_ptObjPos1 = { WINSIZEX / 2,WINSIZEY - 85 };
POINT g_ptMousePos;
RECT g_rtBox1;
int iLevel = 0;
struct tagBox
{
    RECT rt;
    float fSpeed;
};
vector<tagBox> vecBox;
int  iDelay = 100;

int iScore = 0;
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI)); //단축기 지정

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //사이즈 창 변경시 유지
    wcex.lpfnWndProc = WndProc; //함수 포인터
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //프로그램 주소값
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI)); //아이콘
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS); // 커서
    wcex.hbrBackground = (HBRUSH)(BLACK_BRUSH); //백그라운드 색
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI); //메뉴창 설명 이름
    wcex.lpszClassName = szWindowClass; //윈도우 창의 이름
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
int Resolutionx = GetSystemMetrics(SM_CXSCREEN);
int Resolutiony = GetSystemMetrics(SM_CYSCREEN);

int WinposX = Resolutionx / 2 - WINSIZEX / 2;
int WinposY = Resolutiony / 2 - WINSIZEY / 2;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.



    HWND hWnd = CreateWindowW(szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        WinposX,            //윈도우 화면 좌측 상단 죄표 x
        WinposY,                                     //윈도우 화면 좌측 상단 죄표 y
        WINSIZEX,                        //윈도우 가로 사이즈
        WINSIZEY,                                     //왼도우 세로 사이즈
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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 10, NULL);
        srand((unsigned int)time(nullptr));
        break;
    case WM_MOUSEMOVE:

        break;
    case WM_TIMER:
    {
        InvalidateRect(hWnd, nullptr, true);
        iLevel = iScore / 100 + 1;
        g_rtBox1 = RECT_MAKE(g_ptObjPos1.x, g_ptObjPos1.y, 50);
        if (iDelay > 50)
        {
            tagBox box;
            box.rt.left = rand() % (WINSIZEX - 30);
            box.rt.right = box.rt.left + 30;
            box.rt.top = -30;
            box.rt.bottom = 0;
            box.fSpeed = rand() % 11 + 5;
            vecBox.push_back(box); //비가 내리듯  내릴거임
            iDelay = rand() % 50;
        }
        else
            iDelay++;

        vector<tagBox>::iterator iter;
        for (iter = vecBox.begin(); iter != vecBox.end(); iter++)
        {
            iter->rt.top += iter->fSpeed;
            iter->rt.bottom += iter->fSpeed;
            RECT rt;
            RECT rtIter = iter->rt;
            if (iter->rt.top > WINSIZEY)
            {
                iScore += 50;
                vecBox.erase(iter);
                break;
            }
            else if (IntersectRect(&rt, &g_rtBox1, &rtIter))
            {
                iScore -= 100;
                if (iScore < 0)
                    iScore = 0;
                vecBox.erase(iter);
                break;
            }
        }

    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            g_ptObjPos1.x -= (g_rtBox1.left >= 10) ? fMoveSpeed : 0;
            break;
        case VK_RIGHT:
            g_ptObjPos1.x += (g_rtBox1.right < WINSIZEX - fMoveSpeed) ? fMoveSpeed : 0;
            break;
        }
    }
    break;
    case WM_CHAR:
    {
        hdc = GetDC(hWnd);

        InvalidateRect(hWnd, nullptr, true);
        ReleaseDC(hWnd, hdc);
    }
    break;
    // 커널 오브젝트 (윈도우가 제어라는 오브젝트):-> 핸들(핸들로 이 오브젝트를 제어한다.)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);

        RECT_DRAW(g_rtBox1);

        for (int i = 0; i < vecBox.size(); i++)
        {
            RECT_DRAW(vecBox[i].rt);
        }

        char BufScore[32];
        wchar_t Buflevel[32];

        _itoa_s(iScore, BufScore, 10);
        string str = string(BufScore);
        TextOutA(hdc, 10, 30, str.c_str(), str.length());

        swprintf_s(Buflevel, L"레벨: %d", iLevel);
        TextOut(hdc, 10, 10, Buflevel, wcslen(Buflevel));

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

// 정보 대화 상자의 메시지 처리기입니다.
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
