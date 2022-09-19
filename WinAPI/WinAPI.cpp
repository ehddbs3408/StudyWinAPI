// WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
POINT g_ptObjPos = {500,300};
POINT g_ptObjScale = {100,100};


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
    if (!InitInstance (hInstance, nCmdShow))
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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW; //사이즈 창 변경시 유지
    wcex.lpfnWndProc    = WndProc; //함수 포인터
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance; //프로그램 주소값
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI)); //아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS); // 커서
    wcex.hbrBackground  = (HBRUSH)(BLACK_BRUSH); //백그라운드 색
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI); //메뉴창 설명 이름
    wcex.lpszClassName  = szWindowClass; //윈도우 창의 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    static wchar_t str[200];
    static int i, yPos;
    static SIZE size;
    RECT rt = { 0,0,1000,1000 };
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            MessageBox(hWnd, L"대희야 ㅋㅋㅋ 그것도 못깨니?",L"ㅋㅋㅋㅋㅋㅋ", MB_OK);
            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd,nullptr,true);
            break;
        }
    }
        break;
    case WM_LBUTTONDOWN:
    {

    }
    break;
    case WM_KEYUP:
    {

    }
    break;
    case WM_CREATE:
        i = 0;
        yPos = 0;
        CreateCaret(hWnd, NULL, 2, 15); //(핸들,비트맵,두께, 높이)
        ShowCaret(hWnd);
        //GetClientRect(hWnd, &rtview);
        break;
    case WM_CHAR:
    {
        hdc = GetDC(hWnd);
        if (wParam == VK_BACK&& i > 0)
            i--;
        else if (wParam == VK_RETURN)
        {
            i = 0;
            yPos += 20;
        }
        else
            str[i++] = wParam;
        str[i] = '\0';
        InvalidateRect(hWnd, nullptr,true);
        ReleaseDC(hWnd, hdc);
    }
        break;
        // 커널 오브젝트 (윈도우가 제어라는 오브젝트):-> 핸들(핸들로 이 오브젝트를 제어한다.)
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        GetTextExtentPoint(hdc, str, wcslen(str), &size);
        SetCaretPos(size.cx, 0);
        DrawText(hdc, str, wcslen(str), &rt, DT_TOP | DT_LEFT );
        //TextOut(hdc, 0, yPos, str, wcslen(str));
        EndPaint(hWnd, &ps);


            /*
            PAINTSTRUCT ps;
            //Dc : device Context = 그리기위한 데이터 핸들
            //dc의  기본펜은(black), 기본 브러쉬(하얀색)
            HDC hdc = BeginPaint(hWnd, &ps);

            Rectangle(hdc, 
                g_ptObjPos.x - g_ptObjScale.x / 2,
                g_ptObjPos.y - g_ptObjScale.y / 2,
                g_ptObjPos.x + g_ptObjScale.x/2,
                g_ptObjPos.y + g_ptObjScale.y/2);
                */


            /*

            HPEN hRedpen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
            HPEN hDefultpen = (HPEN)SelectObject(hdc, hRedpen);

            HBRUSH hBluebrush = CreateSolidBrush(RGB(100, 100, 255));
            HBRUSH hDefultbrush = (HBRUSH)SelectObject(hdc, hBluebrush);

            Rectangle(hdc, 10, 10, 500, 500);

            DeleteObject(hRedpen);
            DeleteObject(hBluebrush);
            */

            //wstring wstr = L"게임 프로그래밍 ";
            //RECT rt = {};
            //rt.left = 300;
            //rt.top = 300;
            //rt.right = 400;
            //rt.bottom = 400;
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            //Rectangle(hdc, 10, 10, 110, 110);
            //Ellipse(hdc, 50, 50, 150, 150);
            //TextOut(hdc, 200, 200, wstr.c_str(), wstr.length());
            //DrawText(hdc, L"helloWorld", 10, &rt, DT_SINGLELINE | DT_RIGHT);
            //MoveToEx(hdc, 0, 0, nullptr);
            //LineTo(hdc, 800, 400);

            //연습 문제 1번
            /*
            RECT rt{
                WinposX,
                WinposY,
                WinposX + WINSIZEX,
                WinposY + WINSIZEY
            };
            AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
            MoveWindow(hWnd, WinposX, WinposY, rt.right - rt.left, rt.bottom - rt.top,true);

             for (int i = 0; i < WINSIZEX; i += 80)
            {
                MoveToEx(hdc, i, 0, nullptr);
                LineTo(hdc, i, 720);
            }
            for (int i = 0; i < WINSIZEY; i += 80)
            {
                MoveToEx(hdc, 0, i, nullptr);
                LineTo(hdc, 1280, i);
            }
            */

            //문제 2번
            /*
            bool isCircle = false;
            int line = 100;
            int num = 100;
            for (int i = 1; i < 26; i++)
            {
                if (isCircle==false)
                {
                    int sizeX = num;
                    int sizeY = line;
                    Rectangle(hdc, sizeX, sizeY, sizeX+ 50, sizeY + 50);
                    num += 70;
                }
                else
                {
                    int sizeX = num;
                    int sizeY = line;
                    Ellipse(hdc, sizeX, sizeY, sizeX + 50, sizeY + 50);
                    num += 70;
                }
                if (i % 5 == 0&&i!=0)
                {
                    isCircle = !isCircle;
                    num = 100;
                    line += 70;
                }
            }
            */

            
        }
            
           
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        HideCaret(hWnd);
        DestroyCaret();
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
