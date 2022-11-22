#pragma once
#include "BWindow.h"
// 싱글톤 2번째 방법
class Core :public BWindow
{
public:
	SINGLE(Core);
	//static Core* GetInst()
	//{
	//	static Core core;
	//	return &core;
	//}
private:
	Core();
	~Core();
private:
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw할 DC
	HDC		m_memDC;		// 사본용 DC
	HBITMAP	m_hBit;			// 사본용 비트맵
public:
	int		Init(HWND _hWnd, POINT _ptResolution);
	void    Progress();
private:
	void	Update();
	void	Render();
public:
	const HWND& GetWndHandle() { return m_hWnd; }
	const HINSTANCE& GetInstanceHandle() { return m_hInstance; }
	POINT& GetResolution() { return m_ptResolution; }
	const HDC& GetMainDC() { return m_hDC; }
};
// 싱글톤 1번 방법
//class Core
//{
//private:
//	static Core* g_pInst;
//public:
//	static Core* GetInst()
//	{
//		//최초 
//		//static Core* pCore = nullptr;
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new Core;
//		}
//		return g_pInst;
//	}
//	static void Release()
//	{
//		delete g_pInst;
//		g_pInst = nullptr;
//	}
//private:
//	Core();
//	~Core();
//};

