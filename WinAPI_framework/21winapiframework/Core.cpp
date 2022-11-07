#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
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

Object g_obj;
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

	//g_obj.m_ptPos={ m_ptResolution.x / 2,m_ptResolution.y / 2 };
	//g_obj.m_ptScale={ 100,100 };
	g_obj.SetPos(Vec2(m_ptResolution.x / 2, m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100,100));
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
	//static int iCallcount = 0;
	//++iCallcount;
	//static int iPrevcount = GetTickCount64();
	//int iCurcount = GetTickCount64();
	//if (iCurcount - iPrevcount > 1000)
	//{
	//	iPrevcount = iCurcount;
	//	iCallcount = 0;
	//}
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	Update();
	Render();
}

void Core::Update()
{
	Vec2 vPos = g_obj.GetPos();
	if(KeyMgr::GetInst()->GetKey(KEY::LEFT)==KEY_STATE::AWAY)
	{
		//g_obj.m_ptPos.x -= 1;
		vPos.x -= 100.f;//* fDT;//TimeMgr::GetInst()->GetfDT();
	}

	if (KeyMgr::GetInst()->GetKey(KEY::RIGHT) == KEY_STATE::TAP)
	{
		//g_obj.m_ptPos.x += 1;
		vPos.x += 100.f;// *fDT; //TimeMgr::GetInst()->GetfDT();
	}
	g_obj.SetPos(vPos);
}

void Core::Render()
{
	// 화면 clear(하얀색으로 칠해줘야해)
	//Rectangle(m_memDC, -1, -1
	//	, m_ptResolution.x + 1, m_ptResolution.y + 1);
	PatBlt(m_memDC, 0,0, m_ptResolution.x, m_ptResolution.y, WHITENESS);
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
//	InvalidateRect()
	Rectangle(m_memDC
		,(int)(vPos.x - vScale.x/2.f)
		,(int)(vPos.y - vScale.y/2.f)
		,(int)(vPos.x + vScale.x/2.f)
		,(int)(vPos.y + vScale.y/2.f));
	BitBlt(m_hDC, 0,0, m_ptResolution.x, m_ptResolution.y
	,m_memDC, 0,0,SRCCOPY);
	//Rectangle(m_hDC
	//		,g_obj.m_ptPos.x - g_obj.m_ptScale.x/2
	//		,g_obj.m_ptPos.y - g_obj.m_ptScale.y/2
	//		,g_obj.m_ptPos.x + g_obj.m_ptScale.x/2
	//		,g_obj.m_ptPos.y + g_obj.m_ptScale.y/2);
}
