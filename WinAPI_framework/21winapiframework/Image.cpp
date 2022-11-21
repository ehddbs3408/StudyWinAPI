#include "pch.h"
#include "Image.h"

Image::Image() : m_hBit(0),m_hDC(0)
{
}

Image::~Image()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}d

void Image::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)
	LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);
}
