#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
Core::Core()
	: m_hDC(0)
	, m_ptResolution{}
	, m_memDC(0)
	, m_hBit(0)
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int Core::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	m_hDC = GetDC(m_hWnd);
	m_memDC = CreateCompatibleDC(m_hDC);
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	SelectObject(m_memDC, m_hBit);

	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();

	// 해상도 맞게 조절
	RECT rt = { 0,0,m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd,nullptr, 100,100
		,rt.right-rt.left
	    ,rt.bottom-rt.top,0);
	return S_OK;
}

void Core::Progress()
{
	Update();
	Render();
}

void Core::Update()
{
	// =====Mgr Update====
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();

	//Vec2 vPos = g_obj.GetPos();
	//
	//g_obj.SetPos(vPos);
}

void Core::Render()
{

	PatBlt(m_memDC, 0,0, m_ptResolution.x, m_ptResolution.y, WHITENESS);

	SceneMgr::GetInst()->Render(m_memDC);

	//Vec2 vPos = g_obj.GetPos();
	//Vec2 vScale = g_obj.GetScale();
//	InvalidateRect()
	
	BitBlt(m_hDC, 0,0, m_ptResolution.x, m_ptResolution.y
	,m_memDC, 0,0,SRCCOPY);
}
