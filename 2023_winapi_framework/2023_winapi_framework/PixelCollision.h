#pragma once
class Texture;

class PixelCollision
{
	SINGLE(PixelCollision);

public:
	void	Init();
	bool	CheckCollision(int startX, int startY, int endX, int endY);
	void	Release();

public:
	
	void	SetColorImage(Texture* _texColorImage) { m_texColorImgae = _texColorImage; }
	
private:
	Texture* m_texColorImgae;
};
