#include "pch.h"
#include "Scene_Start.h"
#include "Object.h"

Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	Object* pObj = new Object();
	pObj->SetPos(Vec2(640.f, 400.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
}

void Scene_Start::Exit()
{
}
