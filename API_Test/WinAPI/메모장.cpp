// WinAPI.cpp : 蕉巴軒追戚芝拭 企廃 遭脊繊聖 舛税杯艦陥.
//

#include "framework.h"
#include "WinAPI.h"

#define MAX_LOADSTRING 100

// 穿蝕 痕呪:
HINSTANCE hInst;                                // 薄仙 昔什渡什脊艦陥.
WCHAR szTitle[MAX_LOADSTRING];                  // 薦鯉 妊獣匝 努什闘脊艦陥.
WCHAR szWindowClass[MAX_LOADSTRING];            // 奄沙 但 適掘什 戚硯脊艦陥.

// 戚 坪球 乞汲拭 匂敗吉 敗呪税 識情聖 穿含杯艦陥:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
POINT g_ptObjPos = { 500,300 };
POINT g_ptObjScale = { 100,100 };


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 食奄拭 坪球研 脊径杯艦陥.

    // 穿蝕 庚切伸聖 段奄鉢杯艦陥.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 蕉巴軒追戚芝 段奄鉢研 呪楳杯艦陥:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI)); //舘逐奄 走舛

    MSG msg;

    // 奄沙 五獣走 欠覗脊艦陥:
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
//  敗呪: MyRegisterClass()
//
//  遂亀: 但 適掘什研 去系杯艦陥.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //紫戚綜 但 痕井獣 政走
    wcex.lpfnWndProc = WndProc; //敗呪 匂昔斗
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //覗稽益轡 爽社葵
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI)); //焼戚嬬
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS); // 朕辞
    wcex.hbrBackground = (HBRUSH)(BLACK_BRUSH); //拷益虞錘球 事
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI); //五敢但 竺誤 戚硯
    wcex.lpszClassName = szWindowClass; //制亀酔 但税 戚硯
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   敗呪: InitInstance(HINSTANCE, int)
//
//   遂亀: 昔什渡什 輩級聖 煽舌馬壱 爽 但聖 幻旧艦陥.
//
//   爽汐:
//
//        戚 敗呪研 搭背 昔什渡什 輩級聖 穿蝕 痕呪拭 煽舌馬壱
//        爽 覗稽益轡 但聖 幻窮 陥製 妊獣杯艦陥.
//
int Resolutionx = GetSystemMetrics(SM_CXSCREEN);
int Resolutiony = GetSystemMetrics(SM_CYSCREEN);

int WinposX = Resolutionx / 2 - WINSIZEX / 2;
int WinposY = Resolutiony / 2 - WINSIZEY / 2;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 昔什渡什 輩級聖 穿蝕 痕呪拭 煽舌杯艦陥.



    HWND hWnd = CreateWindowW(szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        WinposX,            //制亀酔 鉢檎 疎著 雌舘 阻妊 x
        WinposY,                                     //制亀酔 鉢檎 疎著 雌舘 阻妊 y
        WINSIZEX,                        //制亀酔 亜稽 紫戚綜
        WINSIZEY,                                     //図亀酔 室稽 紫戚綜
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
//  敗呪: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  遂亀: 爽 但税 五獣走研 坦軒杯艦陥.
//
//  WM_COMMAND  - 蕉巴軒追戚芝 五敢研 坦軒杯艦陥.
//  WM_PAINT    - 爽 但聖 益験艦陥.
//  WM_DESTROY  - 曽戟 五獣走研 惟獣馬壱 鋼発杯艦陥.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static wchar_t str[10][200];
    static int i, line;
    static SIZE size;
    RECT rt = { 0,0,1000,1000 };
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 五敢 識澱聖 姥庚 歳汐杯艦陥:
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
            MessageBox(hWnd, L"企費醤 せせせ 益依亀 公凹艦?", L"せせせせせせ", MB_OK);
            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
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
        line = 0;
        CreateCaret(hWnd, NULL, 2, 15); //(輩級,搾闘己,砧臆, 株戚)
        ShowCaret(hWnd);
        //GetClientRect(hWnd, &rtview);
        break;
    case WM_CHAR:
    {
        hdc = GetDC(hWnd);
        if (wParam == VK_BACK && i > 0)
            i--;
        else if (wParam == VK_RETURN)
        {
            if (line < 9)
            {
                i = 0;
                line++;
            }
        }
        else
            if (i < 198)
            {
                str[line][i++] = wParam;
            }

        str[line][i] = '\0';
        InvalidateRect(hWnd, nullptr, true);
        ReleaseDC(hWnd, hdc);
    }
    break;
    // 朕確 神崎詮闘 (制亀酔亜 薦嬢虞澗 神崎詮闘):-> 輩級(輩級稽 戚 神崎詮闘研 薦嬢廃陥.)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        for (int j = 0; j < line + 1; j++)
        {
            GetTextExtentPoint(hdc, str[j], wcslen(str[j]), &size);
            TextOut(hdc, 0, j * 20, str[j], wcslen(str[j]));
            SetCaretPos(size.cx, j * 20);
        }
        EndPaint(hWnd, &ps);
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

// 舛左 企鉢 雌切税 五獣走 坦軒奄脊艦陥.
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
