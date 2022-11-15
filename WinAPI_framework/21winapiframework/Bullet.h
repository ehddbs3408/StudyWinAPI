#pragma once
#include "Object.h"
class Bullet :
    public Object
{
private:
    float m_fDir; // �Ѿ� ����(��, �Ʒ�)
public:
    Bullet();
    ~Bullet();
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
public:
    void SetDir(bool _b)
    {
        if (_b) // ��
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }
};

