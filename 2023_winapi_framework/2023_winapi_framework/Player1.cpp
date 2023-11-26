#include "pch.h"
#include "Player1.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

Player1::Player1()
	: m_pTex(nullptr)
	, int m_iHP(1)
	, float m_fPlayerSpeed(0f)
	, float m_fFireDelay(0f)
	, float m_fBulletSpeed(0f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
}

Player1::~Player1()
{
}

void Player1::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESS(KEY_TYPE::A))
	{
		vPos.x -= m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::D))
	{
		vPos.x += m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	SetPos(vPos);
}

void Player1::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player1::Attack()
{
}
