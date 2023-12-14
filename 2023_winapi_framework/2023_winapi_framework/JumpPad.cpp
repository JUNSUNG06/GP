#include "pch.h"
#include "JumpPad.h"
#include "Collider.h"
#include "Player1.h"
#include "Player2.h"
#include "GameMgr.h"
#include "Rigidbody.h"
JumpPad::JumpPad()
	: m_pTex(nullptr)
	, m_fJumpPower(-800.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50, 24));
}

JumpPad::~JumpPad()
{
	
}

void JumpPad::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSclae = GetScale();
	RECT_RENDER(vPos.x, vPos.y, vSclae.x, vSclae.y, _dc);
}

void JumpPad::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player1")
	{
		GameMgr::GetInst()->GetPlayer1()->GetRigidbody()->SetVerticalVelocity(m_fJumpPower);
	}
	else if (pOtherObj->GetName() == L"Player2")
	{
		GameMgr::GetInst()->GetPlayer2()->GetRigidbody()->SetVerticalVelocity(m_fJumpPower);
	}
}

void JumpPad::ExitCollision(Collider* _pOther)
{
}

void JumpPad::StayCollision(Collider* _pOther)
{
}
