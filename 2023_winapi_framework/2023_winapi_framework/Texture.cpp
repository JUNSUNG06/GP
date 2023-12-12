#include "pch.h"
#include "Texture.h"
#include "Core.h"
#include<assert.h>
Texture::Texture()
	: m_hBit(0)
	, m_hDC(0)
	, m_bitInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void Texture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	assert(m_hBit);
	m_hDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hDC, m_hBit);
	GetObject(m_hBit, sizeof(BITMAP),&m_bitInfo);
}

void Texture::Draw(HDC _dc, Vec2 _vPos, Vec2 _vScale)
{
	if (m_fAngle <= 0.1f)
	{
		TransparentBlt(_dc
			, (int)(_vPos.x - _vScale.x / 2)
			, (int)(_vPos.y - _vScale.y / 2)
			, GetWidth(), GetHeight(), m_hDC
			, 0, 0, GetWidth(), GetHeight(), RGB(255, 0, 255));
	}
	else
	{
		DrawRotate(_dc, _vPos, _vScale, m_fAngle);
	}
}

void Texture::DrawRotate(HDC _dc, Vec2 _vPos, Vec2 _vScale, float _fAngle)
{
	POINT tPoint[3] = { 0 };
	float fx, fy, fxDest, fyDest;
	float fRadian = 30.f * M_PI / 180.f;
	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);
	float width = GetWidth();
	float height = GetHeight();
	POINT resolution = Core::GetInst()->GetResolution();
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) {
			fx = -width * 0.5f;
			fy = -height * 0.5f;
		}
		else if (i == 1) {
			fx = width * 0.5f;
			fy = -height * 0.5f;
		}
		else if (i == 2) {
			fx = -width * 0.5f;
			fy = height * 0.5f;
		}

		fxDest = fx * cosTheta - fy * sinTheta;
		fyDest = fx * sinTheta + fy * cosTheta;
		tPoint[i].x = (fxDest + _vPos.x);
		tPoint[i].y = (fyDest + _vPos.y);
	}

	HDC _hDC = CreateCompatibleDC(_dc);
	HBITMAP _hWnd = CreateCompatibleBitmap(_dc,
		resolution.x, resolution.y);
	HBITMAP _hOldBit = (HBITMAP)SelectObject(_hDC, _hWnd);

	float left = _vPos.x - (width * 0.25f);
	float top = _vPos.y - (height * 0.25f);

	PatBlt(_hDC, 0, 0, resolution.x, resolution.y, WHITENESS);

	TransparentBlt(_hDC, left, top,
		width * 0.5f, height * 0.5f,
		GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));

	PlgBlt(_dc, tPoint, _hDC,
		left, top, width * 0.5f, height * 0.5f, nullptr, 0, 0);

	SelectObject(_hDC, _hOldBit);
	DeleteObject(_hWnd);
	DeleteDC(_hDC);
}
