#pragma once
class Scene;
class SceneMgr
{
private:
	SceneMgr();
	~SceneMgr();
public:
	SINGLE(SceneMgr);
private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];
	Scene* m_pCurScene;
	
public:
	void Init();
	void Update();
	void Render(HDC _dc);
};

