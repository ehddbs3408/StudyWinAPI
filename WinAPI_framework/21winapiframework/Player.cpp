#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
void Player::Update()
{
	Vec2 vPos = GetPos();
	//if (KeyMgr::GetInst()->GetKey(KEY::LEFT) == KEY_STATE::HOLD)
	if(KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 300.f * fDT;//TimeMgr::GetInst()->GetfDT();
	}
//	if (KeyMgr::GetInst()->GetKey(KEY::RIGHT) == KEY_STATE::HOLD)
	if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 300.f * fDT; //TimeMgr::GetInst()->GetfDT();
	}

//	if (KeyMgr::GetInst()->GetKey(KEY::UP) == KEY_STATE::HOLD)
	if (KEY_HOLD(KEY::UP))
	{
		vPos.y -= 300.f * fDT; //TimeMgr::GetInst()->GetfDT();
	}
	if (KEY_HOLD(KEY::DOWN))
//	if (KeyMgr::GetInst()->GetKey(KEY::DOWN) == KEY_STATE::HOLD)
	{
		vPos.y += 300.f * fDT; //TimeMgr::GetInst()->GetfDT();
	}
//	if (KeyMgr::GetInst()->GetKey(KEY::SPACE) == KEY_STATE::TAP)
	if(KEY_TAP(KEY::SPACE))
	{
		CreateBullet();
	}
	SetPos(vPos);
}
void Player::CreateBullet()
{
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;
	Bullet* pBullet = new Bullet;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
//	pBullet->SetDir(true);
	pBullet->SetDir(Vec2(-1.f, -7.f));
	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pBullet, GROUP_TYPE::BULLET);
}
//void Player::Render(HDC _dc)
//{
//}
