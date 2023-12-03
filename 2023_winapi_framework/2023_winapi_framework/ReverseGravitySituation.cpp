#include "pch.h"
#include "ReverseGravitySituation.h"
#include "GameMgr.h"
#include "Rigidbody.h"
ReverseGravitySituation::ReverseGravitySituation(SITUATION_TYPE _eSitutationType)
	: Situation(_eSitutationType)
{
	m_pPlayer1Rigidbody = nullptr;
	m_pPlayer2Rigidbody = nullptr;
}

ReverseGravitySituation::~ReverseGravitySituation()
{
	if(m_pPlayer1Rigidbody != nullptr)
		delete m_pPlayer1Rigidbody;
	if (m_pPlayer2Rigidbody != nullptr)
		delete m_pPlayer2Rigidbody;
}

void ReverseGravitySituation::StartSituation()
{
	m_pPlayer1Rigidbody = GameMgr::GetInst()->GetPlayer1()->GetRigidbody();
	m_pPlayer2Rigidbody = GameMgr::GetInst()->GetPlayer2()->GetRigidbody();

	m_pPlayer1Rigidbody->ReverseGravity(true);
	m_pPlayer2Rigidbody->ReverseGravity(true);
}

void ReverseGravitySituation::UpdateSituation()
{
}

void ReverseGravitySituation::EndSituation()
{
	m_pPlayer1Rigidbody->ReverseGravity(false);
	m_pPlayer2Rigidbody->ReverseGravity(false);
}
