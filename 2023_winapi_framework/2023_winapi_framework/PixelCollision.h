#pragma once
class Texture;

class PixelCollision
{
	SINGLE(PixelCollision);

public:
	void	Init();
	bool	CheckCollision(int startX, int startY, int endX, int endY, POINT* checkedPoint, bool _bReverse = false);
	void	Render(HDC _dc);
	void	Release();

public:
	
	void	SetColorImage(Texture* _texColorImage) { m_texColorImgae = _texColorImage; }
	
private:
	Texture* m_texColorImgae;
	float m_fTextureRotation;
};

