#pragma once
#include "Object.h"
class Texture;

class JumpPad
	: public Object
{
public:
	JumpPad();
	~JumpPad();

public:
	void Render(HDC _dc) override;
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther)  override;
	virtual void StayCollision(Collider* _pOther)  override;

private:
	Texture* m_pTex;
	float m_fJumpPower;
};

