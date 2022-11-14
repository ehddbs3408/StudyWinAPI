#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"

Monster::Monster() : m_fSpeed(100.f), m_fmaxDis(50.f), m_vContorPos(Vec2(0.1f,0.1f)), m_fDir(1.f)
{
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vCurPos = GetPos();
	vCurPos.x += m_fSpeed * fDT * m_fDir;

	float fDist = (m_vContorPos.x - vCurPos.x) - m_fmaxDis;
	if (fDist > 0.1f)
	{
		m_fDir *= -1;
		vCurPos.x += fDist * m_fDir;
	}
	SetPos(vCurPos);
}
