#pragma once
class Res
{
private:
	wstring m_strKey;
	wstring m_strRelativePath;
public:
	Res();
	~Res();
public:
	void Setkey(const wstring& _strkey) { m_strKey = _strkey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }
}; 

