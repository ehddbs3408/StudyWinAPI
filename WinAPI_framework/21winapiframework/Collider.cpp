#include "pch.h"
#include "Collider.h"

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
