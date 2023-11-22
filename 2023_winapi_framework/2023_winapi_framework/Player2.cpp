#include "pch.h"
#include "Player2.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

Player2::Player2()
	: m_pTex(nullptr)
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
		vPos.x -= 100.f * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::D))
	{
		vPos.x += 100.f * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	SetPos(vPos);
}

void Player2::Render(HDC _dc)
{
	Component_Render(_dc);
}
