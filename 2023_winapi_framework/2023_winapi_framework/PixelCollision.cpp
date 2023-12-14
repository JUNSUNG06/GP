#include "pch.h"
#include "PixelCollision.h"
#include "Core.h"
#include "Texture.h"

void PixelCollision::Init()
{
	m_texColorImgae = nullptr;
}

bool PixelCollision::CheckCollision(int startX, int startY, int endX, int endY, POINT* checkedPoint, bool _bReverse)
{
	if (m_texColorImgae == nullptr)
		return false;

	if (_bReverse == false)
	{
		for (int y = startY; y <= endY; y++)
		{
			for (int x = startX; x <= endX; x++)
			{
				COLORREF color = GetPixel(m_texColorImgae->GetDC(), x, y);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 255)
				{
					*checkedPoint = { x, y };
					return true;
				}
			}
		}
	}
	else
	{
		for (int y = endY; y >= startY; y--)
		{
			for (int x = endX; x >= startX; x--)
			{
				COLORREF color = GetPixel(m_texColorImgae->GetDC(), x, y);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 255)
				{
					*checkedPoint = { x, y };
					return true;
				}
			}
		}
	}
	
	return false;
}

void PixelCollision::Render(HDC _dc)
{
	if (m_texColorImgae != nullptr)
		BitBlt(_dc, 0, 0, m_texColorImgae->GetWidth(), m_texColorImgae->GetHeight(),
			m_texColorImgae->GetDC(), 0, 0, SRCCOPY);
		
}

void PixelCollision::Release()
{
	m_texColorImgae = nullptr;
}
