#pragma once
#include "BWindow.h"
// �̱��� 2��° ���
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
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw�� DC
	HDC		m_memDC;		// �纻�� DC
	HBITMAP	m_hBit;			// �纻�� ��Ʈ��
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
// �̱��� 1�� ���
//class Core
//{
//private:
//	static Core* g_pInst;
//public:
//	static Core* GetInst()
//	{
//		//���� 
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

