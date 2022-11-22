#pragma once
class Image;
class ResMgra
{
private:
	map<wstring, Image*> m_mapImg;

public:
	SINGLE(ResMgr);
private:
	ResMgr();
	~ResMgr();
public:
	Image* imgLoad(const wstring& _strKey, const wstring& _strrRe);
};

