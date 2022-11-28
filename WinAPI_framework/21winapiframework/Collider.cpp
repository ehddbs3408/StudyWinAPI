#include "pch.h"
#include "Collider.h"
#include "SelectGDI.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void Collider::Render(HDC _dc)
{
	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc,BRUSH_TYPE::HOLLOW);
}