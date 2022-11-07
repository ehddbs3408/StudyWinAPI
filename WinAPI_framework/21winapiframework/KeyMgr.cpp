#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	VK_MENU, VK_LSHIFT, VK_CONTROL, VK_SPACE,
	VK_RETURN, VK_ESCAPE,
};

KeyMgr::KeyMgr()
{
}

KeyMgr::~KeyMgr()
{
}

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE,false });
	}
}

void KeyMgr::Update()
{
	//HWND hMainWnd = Core::GetInst()->GetInstanceHandle();
	HWND hWnd = GetFocus();
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]))
			{
				if (m_vecKey[i].bPrevCheck)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevCheck = true;
			}
			else
			{
				if (m_vecKey[i].bPrevCheck)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevCheck = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevCheck = false;
			if (m_vecKey[i].eState == KEY_STATE::HOLD
				|| m_vecKey[i].eState == KEY_STATE::TAP)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
	
}


