#include "pch.h"
#include "BWindow.h"
#include "Resource.h"
#include "Core.h"

BWindow::BWindow() :m_hInstance(0), m_hWnd(0)
{
    
}

BWindow::~BWindow()
{

}

LRESULT BWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0); //WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int BWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    m_hInstance = hInstance;
    this->MyRegisterClass();
    this->WindowCreate();
    this->WindowShow(nCmdShow);
    this->WindowUpdate();

    if (FAILED(Core::GetInst()->init(m_hWnd, new POINT{ 860,120 })))
    {
        MessageBox(m_hWnd, L"Core 객체 초기화 실패",  L"ERROR", MB_OK);
        return FALSE;
    }

    return this->Messageloop();
}

ATOM BWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_WINAPIFRAMEWORK));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BWindow::WindowCreate()
{
    HWND hWnd = CreateWindowW(WINDOW_NAME, L"1반 gameframework", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
}

void BWindow::WindowShow(int nCmdShow)
{
    ShowWindow(m_hWnd, nCmdShow);
}

void BWindow::WindowUpdate()
{
    UpdateWindow(m_hWnd);
}

int BWindow::Messageloop()
{
    MSG msg;
    memset(&msg, 0, sizeof(msg));

    while (true)
    {
        //메세지가 있다면 여기
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
        else //게임루프가 돈다
        {
            Core::GetInst()->Progress();
        }

    }
    return (int)msg.wParam;
}
