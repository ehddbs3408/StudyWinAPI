#pragma once
#include "Object.h"
class Object;
class Collider
{
private:
	Object* m_pOwner; //
	Vec2 m_vOffsetPos;
	Vec2 m_vFinalPos;
	Vec2 m_vScale;
	friend class Object;
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
public:
	void FinalUpdate();
	void Render(HDC _dc);
	
};

