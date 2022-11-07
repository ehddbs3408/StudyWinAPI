#include "pch.h"
#include "BWindow.h"
#include "Core.h"
//#include "Resource.h"
BWindow::BWindow()
    : m_hInstance(0)
    , m_hWnd(0)
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
        PostQuitMessage(0); // WM_QUIT
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
    // Core ����ó��, �ػ� ����
    if (FAILED(Core::GetInst()->Init(m_hWnd, POINT{1280,800})))
    {
        MessageBox(m_hWnd, L"Core ��ü �ʱ�ȭ ����", L"ERROR", MB_OK);
        return FALSE;
    }

    return this->Messageloop();
}

ATOM BWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

void BWindow::WindowCreate()
{
    m_hWnd = CreateWindowW(WINDOW_NAME, L"1��'s gameframework", WS_OVERLAPPEDWINDOW,
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
    // PeekMessage
    while (true)
    {
        // �޽����� ������ ����
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // �츮�� ���� ������ ���ž�.
        else
        {
            // "������ ��������."
            Core::GetInst()->Progress();
        }

    }

    return (int)msg.wParam;
}