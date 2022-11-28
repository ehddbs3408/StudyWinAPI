#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"


SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hColorPen = Core::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hColorPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hColorPen = Core::GetInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hColorPen);
	
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultBrush);
	SelectObject(m_hDC, m_hDefaultPen);
}
