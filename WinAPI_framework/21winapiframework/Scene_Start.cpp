#include "pch.h"
#include "Scene_Start.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	Object* pObj = new Player();
	pObj->SetPos(Vec2(640.f, 400.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//monster
	Monster* pMonsterObj = new Monster();
	pMonsterObj->SetPos(Vec2(640.f, 50.f));
	pMonsterObj->SetScale(Vec2(50.f, 50.f));
	//pMonsterObj->SetCenterpos(Vec2(640.f, 50.f));
}

void Scene_Start::Exit()
{
}
