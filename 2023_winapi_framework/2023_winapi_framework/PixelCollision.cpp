#include "pch.h"
#include "PixelCollision.h"
#include "Core.h"
#include "Texture.h"

void PixelCollision::Init()
{
	m_texColorImgae = nullptr;
}

bool PixelCollision::CheckCollision(int startX, int startY, int endX, int endY)
{
	if (m_texColorImgae == nullptr)
		return false;

	for (int y = startY; y < endY; y++)
	{
		for (int x = startX; x < endX; x++)
		{
			COLORREF color = GetPixel(m_texColorImgae->GetDC(), x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
				return true;
		}
	}

	return false;
}