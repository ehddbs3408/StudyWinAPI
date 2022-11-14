#include "pch.h"
#include "Player.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

void Player::Update()
{
	Vec2 vPos = GetPos();
	if (KeyMgr::GetInst()->GetKey(KEY::LEFT) == KEY_STATE::HOLD)
	{
		//g_obj.m_ptPos.x -= 1;
		vPos.x -= 100.f * fDT;//TimeMgr::GetInst()->GetfDT();
	}

	if (KeyMgr::GetInst()->GetKey(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		//g_obj.m_ptPos.x += 1;
		vPos.x += 100.f * fDT; //TimeMgr::GetInst()->GetfDT();
	}

	if (KeyMgr::GetInst()->GetKey(KEY::UP) == KEY_STATE::HOLD)
	{
		//g_obj.m_ptPos.x -= 1;
		vPos.y -= 100.f * fDT;//TimeMgr::GetInst()->GetfDT();
	}

	if (KeyMgr::GetInst()->GetKey(KEY::DOWN) == KEY_STATE::HOLD)
	{
		//g_obj.m_ptPos.x += 1;
		vPos.y += 100.f * fDT; //TimeMgr::GetInst()->GetfDT();
	}
}
