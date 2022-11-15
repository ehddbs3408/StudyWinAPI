#include "pch.h"
#include "Object.h"

Object::Object()
	: m_vPos{}
	, m_vScale{}
{
}

Object::~Object()
{
}


void Object::Render(HDC _dc)
{
	Rectangle(_dc
		, (int)(m_vPos.x - m_vScale.x / 2.f)
		, (int)(m_vPos.y - m_vScale.y / 2.f)
		, (int)(m_vPos.x + m_vScale.x / 2.f)
		, (int)(m_vPos.y + m_vScale.y / 2.f));
}
