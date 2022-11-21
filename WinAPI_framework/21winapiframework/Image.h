#pragma once
#include "Res.h"
class Image :
	public Res
{
private:
	HBITMAP m_hBit;
	HDC			m_hDC;
public:
	Image();
	~Image();
public:
	void Load(const wstring& _strFilePath);
};

