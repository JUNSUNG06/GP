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
	TransparentBlt(_dc
		, (int)(_vPos.x - _vScale.x / 2)
		, (int)(_vPos.y - _vScale.y / 2)
		, GetWidth(), GetHeight(), m_hDC
		, 0, 0, GetWidth(), GetHeight(), RGB(255, 0, 255));
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
			fx = -width * (_vScale.x / 100.f);
			fy = -height * (_vScale.y / 100.f);
		}
		else if (i == 1) {
			fx = width * (_vScale.x / 100.f);
			fy = -height * (_vScale.y / 100.f);
		}
		else if (i == 2) {
			fx = -width * (_vScale.x / 100.f);
			fy = height * (_vScale.y / 100.f);
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

	float left = _vPos.x - (width * (_vScale.x / 200.f));
	float top = _vPos.y - (height * (_vScale.y / 200.f));

	PatBlt(_hDC, 0, 0, resolution.x, resolution.y, WHITENESS);

	TransparentBlt(_hDC, left, top,
		width * (_vScale.x / 100.f), height * (_vScale.y / 100.f),
		GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));

	PlgBlt(_dc, tPoint, _hDC,
		left, top, width * (_vScale.x / 100.f), height * (_vScale.y / 100.f), nullptr, 0, 0);

	SelectObject(_hDC, _hOldBit);
	DeleteObject(_hWnd);
	DeleteDC(_hDC);
}
