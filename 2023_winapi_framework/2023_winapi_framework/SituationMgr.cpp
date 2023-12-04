#include "pch.h"
#include "SituationMgr.h"
#include "Situation.h"
#include "ReverseGravitySituation.h"
#include "TimeMgr.h"

void SituationMgr::Init()
{
	m_pCurrentSituation = nullptr;

	SITUATION_TYPE situationType;

	situationType = SITUATION_TYPE::REVERSEGRAVITY;
	RegistSituation(situationType, new ReverseGravitySituation(situationType));
	m_fCurrentSituationTime = 0;
}

void SituationMgr::Udpate()
{
	if (m_pCurrentSituation != nullptr)
	{
		m_pCurrentSituation->UpdateSituation();
		m_fCurrentSituationTime += fDT;

		if (m_fCurrentSituationTime >= m_pCurrentSituation->GetDuration())
			EndSituation();
	}
}

void SituationMgr::Release()
{
	delete m_pCurrentSituation;
}

void SituationMgr::StartSituation()
{
	m_fCurrentSituationTime = 0;

	if (m_pCurrentSituation != nullptr)
		m_pCurrentSituation->StartSituation();
}

void SituationMgr::EndSituation()
{
	if (m_pCurrentSituation != nullptr)
		m_pCurrentSituation->EndSituation();

	m_pCurrentSituation = nullptr;
}

void SituationMgr::SetSituation(SITUATION_TYPE _situationType)
{
	if (m_umSituationMap.find(_situationType) == m_umSituationMap.end())
		return;

	m_pCurrentSituation = m_umSituationMap[_situationType];
}
