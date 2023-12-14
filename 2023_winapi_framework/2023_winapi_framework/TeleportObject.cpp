#include "pch.h"
#include "TeleportObject.h"
#include "Collider.h"
#include "TeleportMgr.h"
#include "PixelCollision.h"

TeleportObject::TeleportObject()
	: m_ptrOtherTelpo(nullptr)
	, m_bIsEntryPoint(false)
{
	CreateCollider();
}

TeleportObject::~TeleportObject()
{
}

void TeleportObject::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSclae = GetScale();
	RECT_RENDER(vPos.x, vPos.y, vSclae.x, vSclae.y, _dc);
	Object::Component_Render(_dc);
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

void TeleportObject::Teleporting(Object* _obj)
{
	_obj->SetPos(m_ptrOtherTelpo->GetPos());
	m_bIsEntryPoint = true;
	TeleportMgr::GetInst()->RemovePortals();
}
