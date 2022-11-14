#pragma once
#include "Object.h"
class Monster :
    public Object
{
private:
    float m_fSpeed;
    float m_fmaxDis;
    float m_fDir;
    Vec2 m_vContorPos;
public:
    Monster();
    ~Monster();
public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float f) { m_fSpeed = f; }
public:
    void Update() override;
};

