#include "pch.h"
#include "ReverseInputSituation.h"
#include "Player1.h"
#include "Player2.h"
#include "GameMgr.h"

ReverseInputSituation::ReverseInputSituation(SITUATION_TYPE _eSitutationType)
	: Situation(_eSitutationType)
{
	m_fDuration = 3.f;
	m_pPlayer1 = nullptr;
	m_pPlayer2 = nullptr;
	m_sDescription = L"이동이 반전됩니다.";
}

ReverseInputSituation::~ReverseInputSituation()
{
	if (m_pPlayer1 != nullptr)
		delete m_pPlayer1;
	if (m_pPlayer2 != nullptr)
		delete m_pPlayer2;
}

void ReverseInputSituation::StartSituation()
{
	m_pPlayer1 = GameMgr::GetInst()->GetPlayer1();
	m_pPlayer2 = GameMgr::GetInst()->GetPlayer2();

	m_pPlayer1->SetMoveKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT);
	m_pPlayer2->SetMoveKey(KEY_TYPE::A, KEY_TYPE::D);
}

void ReverseInputSituation::UpdateSituation()
{
}

void ReverseInputSituation::EndSituation()
{
	m_pPlayer1->SetMoveKey(KEY_TYPE::RIGHT, KEY_TYPE::LEFT);
	m_pPlayer2->SetMoveKey(KEY_TYPE::D, KEY_TYPE::A);
}
