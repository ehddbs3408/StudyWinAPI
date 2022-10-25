#include "pch.h"
#include "Core.h"

Core::Core():m_hDC(0)
{
	
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int Core::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolutiion = _ptResolution;

	m_hDC = GetDC(m_hWnd);

	RECT rt = { 0,0,m_ptResolutiion.x,m_ptResolutiion.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	return S_OK;
}

void Core::Progress()
{
	Rectangle(m_hDC, 0, 0, 0,0);
}
