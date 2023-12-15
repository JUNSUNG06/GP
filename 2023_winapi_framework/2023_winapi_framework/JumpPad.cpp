#include "pch.h"
#include "JumpPad.h"
#include "Collider.h"
#include "Player1.h"
#include "Player2.h"
#include "GameMgr.h"
#include "Rigidbody.h"
#include "ResMgr.h"
#include "Texture.h"
JumpPad::JumpPad()
	: m_pTex(nullptr)
	, m_fJumpPower(-800.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50, 24));
	m_pTex = ResMgr::GetInst()->TexLoad(L"JumpPad", L"Texture\\JumpPad.bmp");
	ResMgr::GetInst()->LoadSound(L"JumpPad", L"Sound\\JumpPad.wav", false);
}

JumpPad::~JumpPad()
{
	
}

void JumpPad::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	//RECT_RENDER(vPos.x, vPos.y, vSclae.x, vSclae.y, _dc);
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, m_pTex->GetWidth() * 2 + 6, m_pTex->GetHeight(), m_pTex->GetDC()
		, 0, 0, m_pTex->GetWidth() , m_pTex->GetHeight(), RGB(255, 0, 255));
}

void JumpPad::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player1")
	{
		ResMgr::GetInst()->Play(L"JumpPad");
		GameMgr::GetInst()->GetPlayer1()->GetRigidbody()->SetVerticalVelocity(m_fJumpPower);
	}
	else if (pOtherObj->GetName() == L"Player2")
	{
		ResMgr::GetInst()->Play(L"JumpPad");
		GameMgr::GetInst()->GetPlayer2()->GetRigidbody()->SetVerticalVelocity(m_fJumpPower);
	}
}

void JumpPad::ExitCollision(Collider* _pOther)
{
}

void JumpPad::StayCollision(Collider* _pOther)
{
}
