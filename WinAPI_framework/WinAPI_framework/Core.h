#pragma once
#include "BWindow.h"
class Core : public BWindow
{
public:
	SINGLE(Core);
private:
	Core();
	~Core();
private:
	POINT m_ptResolutiion;
	HDC m_hDC; //메인 윈도우
public:
	int init(HWND _hWnd,POINT _ptResolution);
	void Progress();
};

//class Core
//{
//public:
//	static Core* GetInst()
//	{
//		if (nullptr == g_plnst)
//		{
//			g_plnst = new Core;
//		}
//		return g_plnst;
//	}
//
//	static void Release()
//	{
//		delete g_plnst;
//		g_plnst = nullptr;
//	}
//private:
//	static Core* g_plnst;
//	Core();
//	~Core();
//}; //1번 방법
// 
//class Core
//{
//public:
//	static Core* GetInst()
//	{
//		static Core core;
//		return &core;
//	}
//private:
//	Core();
//	~Core();
//};//두번째 방법