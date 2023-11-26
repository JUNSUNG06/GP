#include "pch.h"
#include "Player2.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

Player2::Player2()
	: m_pTex(nullptr)
	, int m_iHP(1)
	, float m_fPlayerSpeed(0f)
	, float m_fFireDelay(0f)
	, float m_fBulletSpeed(0f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
}

Player2::~Player2()
{
}

void Player2::Update()
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

void Player2::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player2::Attack()
{
}
