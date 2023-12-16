#include "pch.h"
#include "ReverseMoveSituation.h"
#include "Player1.h"
#include "Player2.h"
#include "GameMgr.h"

ReverseMoveSituation::ReverseMoveSituation(SITUATION_TYPE _eSitutationType)
	: Situation(_eSitutationType)
{
	m_fDuration = 5.f;
	m_pPlayer1 = nullptr;
	m_pPlayer2 = nullptr;
	m_sDescription = L"서로를 움직입니다.";
}

ReverseMoveSituation::~ReverseMoveSituation()
{
}

void ReverseMoveSituation::StartSituation()
{
	m_pPlayer1 = GameMgr::GetInst()->GetPlayer1();
	m_pPlayer2 = GameMgr::GetInst()->GetPlayer2();

	if (m_pPlayer1 != nullptr)
	{
		m_pPlayer1->SetMoveKey(KEY_TYPE::D, KEY_TYPE::A);
		m_pPlayer1->SetJumpKey(KEY_TYPE::W);
	}
	if (m_pPlayer2 != nullptr)
	{
		m_pPlayer2->SetMoveKey(KEY_TYPE::RIGHT, KEY_TYPE::LEFT);
		m_pPlayer2->SetJumpKey(KEY_TYPE::UP);
	}
}

void ReverseMoveSituation::UpdateSituation()
{
}

void ReverseMoveSituation::EndSituation()
{
	if (m_pPlayer1 != nullptr)
	{
		m_pPlayer1->SetMoveKey(KEY_TYPE::RIGHT, KEY_TYPE::LEFT);
		m_pPlayer1->SetJumpKey(KEY_TYPE::UP);
	}
	if (m_pPlayer2 != nullptr)
	{
		m_pPlayer2->SetMoveKey(KEY_TYPE::D, KEY_TYPE::A);
		m_pPlayer2->SetJumpKey(KEY_TYPE::W);
	}
}
