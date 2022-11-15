#pragma once
#include "Object.h"
class Player :
    public Object
{
private:
    void CreateBullet();
public:
    void Update() override;
//    void Render(HDC _dc) override;
};

