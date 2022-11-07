#pragma once

class Object;
//#include "Object.h"
class Scene
{
public:
	Scene();
	~Scene();
private:
	//Object m_obj;
	vector<Object*>		m_vecOb[(UINT)GROUP_TYPE::END];
	wstring						m_strName;
public:
	void		SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}
	const wstring& GetName() { return m_strName; }

};

