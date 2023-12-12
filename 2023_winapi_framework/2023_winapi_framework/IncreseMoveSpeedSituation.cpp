#include "pch.h"
#include "IncreseMoveSpeedSituation.h"
#include "GameMgr.h"
#include "Player1.h"
#include "Player2.h"

IncreseMoveSpeedSituation::IncreseMoveSpeedSituation(SITUATION_TYPE _eSitutationType)
	: Situation(_eSitutationType)
{
	m_pPlayer1 = nullptr;
	m_pPlayer2 = nullptr;
	m_fDuration = 5.f;
	m_sDescription = L"이동속도가 증가합니다.";
}

IncreseMoveSpeedSituation::~IncreseMoveSpeedSituation()
{
	if (m_pPlayer1 != nullptr)
		delete m_pPlayer1;
	if (m_pPlayer2 != nullptr)
		delete m_pPlayer2;
}

void IncreseMoveSpeedSituation::StartSituation()
{
	m_pPlayer1 = GameMgr::GetInst()->GetPlayer1();
	m_pPlayer2 = GameMgr::GetInst()->GetPlayer2();

	if (m_pPlayer1 != nullptr)
		m_pPlayer1->SetPlayerSpeed(m_pPlayer1->GetPlayerSPeed() * 2);
	if (m_pPlayer2 != nullptr)
		m_pPlayer2->SetPlayerSpeed(m_pPlayer1->GetPlayerSPeed() * 2);
}

void IncreseMoveSpeedSituation::UpdateSituation()
{
}

void IncreseMoveSpeedSituation::EndSituation()
{
	if (m_pPlayer1 != nullptr)
		m_pPlayer1->SetPlayerSpeed(m_pPlayer1->GetPlayerSPeed() * 0.5f);
	if (m_pPlayer2 != nullptr)
		m_pPlayer2->SetPlayerSpeed(m_pPlayer1->GetPlayerSPeed() * 0.5f);
}
