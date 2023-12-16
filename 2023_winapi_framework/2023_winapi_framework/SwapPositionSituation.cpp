#include "pch.h"
#include "SwapPositionSituation.h"
#include "GameMgr.h"
#include "Player1.h"
#include "Player2.h"
#include "TimeMgr.h"
#include "ResMgr.h"

SwapPositionSituation::SwapPositionSituation(SITUATION_TYPE _eSitutationType)
	: Situation(_eSitutationType)
{
	m_fDuration = 10.f;
	m_fCurrentTime = 0.f;
	m_pPlayer1 = nullptr;
	m_pPlayer2 = nullptr;
	m_sDescription = L"위치가 교환됩니다.";
}

SwapPositionSituation::~SwapPositionSituation()
{
}

void SwapPositionSituation::StartSituation()
{
	SwapPos();
}

void SwapPositionSituation::UpdateSituation()
{
	m_fCurrentTime += fDT;

	if (m_fCurrentTime > m_fDuration / 2.f && !m_bSwapped)
	{
		SwapPos();
		m_bSwapped = true;
	}
}

void SwapPositionSituation::EndSituation()
{
	SwapPos();
	m_fCurrentTime = 0.f;
	m_bSwapped = false;
}

void SwapPositionSituation::SwapPos()
{
	m_pPlayer1 = GameMgr::GetInst()->GetPlayer1();
	m_pPlayer2 = GameMgr::GetInst()->GetPlayer2();

	if (m_pPlayer1 == nullptr || m_pPlayer2 == nullptr)
		return;

	Vec2 p1Pos = m_pPlayer1->GetPos();
	Vec2 p2Pos = m_pPlayer2->GetPos();

	m_pPlayer1->SetPos(p2Pos);
	m_pPlayer2->SetPos(p1Pos);

	ResMgr::GetInst()->Play(L"Sparkle");
}
