#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"

Bullet::Bullet()
	: m_fDir(1.f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos.x += 600.f * fDT;
	vPos.y += 600.f * fDT * m_fDir;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_dc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));

}
