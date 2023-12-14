#include "pch.h"
#include "TeleportMgr.h"
#include "Object.h"
#include "TeleportObject.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Core.h"
#include "PixelCollision.h"


void TeleportMgr::Init()
{
	m_fCurTime = 0;
	m_fMaxHoldingTime = 10.f;
	m_fRegenTime = 10.f;
	m_bIsSpawned = false;
}

void TeleportMgr::Update()
{
	m_fCurTime += fDT;
	if (!m_bIsSpawned) {
		if (m_fCurTime >= m_fRegenTime) {
			SetPortals();
			m_fCurTime = 0;
			m_bIsSpawned = true;
		}
	}
	else {
		if (m_fCurTime >= m_fMaxHoldingTime) {
			m_fCurTime = 0;
			RemovePortals();
		}
	}
}

void TeleportMgr::SetPortals()
{
	TeleportObject* tpObj1 = new TeleportObject;
	tpObj1->SetPos(Vec2(rand() % ((int)Core::GetInst()->GetResolution().x - 200) + 100, rand() % ((int)Core::GetInst()->GetResolution().y - 200) + 100));
	tpObj1->SetScale(Vec2(20, 20));
	tpObj1->SetName(L"tpObj1");
	SceneMgr::GetInst()->GetCurScene()->AddObject(tpObj1, OBJECT_GROUP::TELEPORT);

	TeleportObject* tpObj2 = new TeleportObject;
	tpObj2->SetPos(Vec2(rand() % ((int)Core::GetInst()->GetResolution().x - 200) + 100, rand() % ((int)Core::GetInst()->GetResolution().y - 200) + 100));
	tpObj2->SetScale(Vec2(20, 20));
	tpObj2->SetName(L"tpObj2");
	SceneMgr::GetInst()->GetCurScene()->AddObject(tpObj2, OBJECT_GROUP::TELEPORT);

	tpObj1->SetOtherTelpo(tpObj2);
	tpObj2->SetOtherTelpo(tpObj1);

	if (tpObj1->CheckIsOnWall() || tpObj2->CheckIsOnWall()) {
		RemovePortals();
		m_fCurTime = m_fRegenTime;
		return;
	}

	m_ptrTpPoint1 = tpObj1;
	m_ptrTpPoint2 = tpObj2;
}

void TeleportMgr::RemovePortals() {
	EventMgr::GetInst()->DeleteObject(m_ptrTpPoint1);
	EventMgr::GetInst()->DeleteObject(m_ptrTpPoint2);
	m_ptrTpPoint1 = nullptr;
	m_ptrTpPoint2 = nullptr;

	m_fCurTime = 0;
	m_bIsSpawned = false;
}