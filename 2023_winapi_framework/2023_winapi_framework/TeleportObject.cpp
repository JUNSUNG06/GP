#include "pch.h"
#include "TeleportObject.h"
#include "Collider.h"
#include "TeleportMgr.h"
#include "PixelCollision.h"
#include "ResMgr.h"
#include "Texture.h"

TeleportObject::TeleportObject()
	: m_ptrOtherTelpo(nullptr)
	, m_bIsEntryPoint(false)
	, m_pTex(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Portal", L"Texture\\Portal.bmp");
	ResMgr::GetInst()->LoadSound(L"Sparkle", L"Sound\\Sparkle.wav", false);
	CreateCollider();
}

TeleportObject::~TeleportObject()
{
}

void TeleportObject::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, m_pTex->GetWidth(), m_pTex->GetHeight(), m_pTex->GetDC()
		, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), RGB(255, 0, 255));
}

void TeleportObject::EnterCollision(Collider* _pOther)
{
	if (!m_ptrOtherTelpo->GetIsEntry()) {
		Object* obj = const_cast<Object*>(_pOther->GetObj());
		Teleporting(obj);
	}
}

void TeleportObject::ExitCollision(Collider* _pOther)
{
}

void TeleportObject::StayCollision(Collider* _pOther)
{
}

bool TeleportObject::CheckIsOnWall()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	RECT rt = { (LONG)(vPos.x - vScale.x / 2), (LONG)(vPos.y),
							(LONG)(vPos.x + vScale.x / 2), (LONG)(vPos.y + vScale.y / 2) };
	POINT checkedPoint = {};
	return PixelCollision::GetInst()->CheckCollision(rt.left, rt.top, rt.right, rt.bottom, &checkedPoint);
}

void TeleportObject::RemoveThis()
{
	EventMgr::GetInst()->DeleteObject(this);
}

void TeleportObject::Teleporting(Object* _obj)
{
	ResMgr::GetInst()->Play(L"Sparkle");
	_obj->SetPos(m_ptrOtherTelpo->GetPos());
	m_bIsEntryPoint = true;
	TeleportMgr::GetInst()->ResetCurrentTime();
	TeleportMgr::GetInst()->RemovePortals();
}
