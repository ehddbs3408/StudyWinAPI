#pragma once
class BWindow
{
public:
	BWindow();
	~BWindow();
public:
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	int					Run(_In_ HINSTANCE hInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow);
	ATOM               MyRegisterClass();
	void					WindowCreate();
	void					WindowShow(int nCmdShow);
	void					WindowUpdate();
	int					Messageloop();
protected:
	HWND				m_hWnd;
	HINSTANCE		m_hInstance;
public:
	const HWND& GetWndHandle() { return m_hWnd; }
	const HINSTANCE& GetWndInstance() { return m_hInstance; }

};

