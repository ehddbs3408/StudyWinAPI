#pragma once
#include "Res.h"
class Image :
    public Res
{
private:
    HBITMAP m_hBit;
    HDC     m_hDC;
    BITMAP  m_bitInfo;
private:
    Image();
    ~Image();
    friend class ResMgr;
public:
    void Load(const wstring& _strFilePath);
    UINT GetWidth() { return m_bitInfo.bmWidth; }
    UINT GetHeight() { return m_bitInfo.bmHeight; }
    HDC GetDC() { return m_hDC; }
};

