#pragma once

class Object;
//#include "Object.h"
class Scene
{
public:
	Scene();
	virtual ~Scene();
private:
	//Object m_obj;
	vector<Object*>		m_vecOb[(UINT)GROUP_TYPE::END];
	wstring						m_strName;
protected:
	void AddObject(Object* _pObj, GROUP_TYPE _eType)
	{
		m_vecOb[(UINT)_eType].push_back(_pObj);
	}
public:
	virtual void Enter() abstract;
	virtual void Exit() abstract;
public:
	void		SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}
	const wstring& GetName() { return m_strName; }
	void Update();
	void Render(HDC _dc);
};

