#pragma once
class Object
{
private:
	//POINT		m_ptPos;
	//POINT		m_ptScale;
	Vec2		m_vPos;
	Vec2		m_vScale;
public:
	Object();
	virtual ~Object();
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() { return m_vPos; }
	const Vec2& GetScale() { return m_vScale; }
public:
//	virtual void	Update() = 0;
	virtual void	Update() abstract;
	virtual void	Render(HDC _dc);
};

