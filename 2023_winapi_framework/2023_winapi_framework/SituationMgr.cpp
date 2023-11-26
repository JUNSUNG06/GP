#include "pch.h"
#include "SituationMgr.h"
#include "Situation.h"

void SituationMgr::Init()
{
	m_pCurrentSituation = nullptr;
}

void SituationMgr::Udpate()
{
	if (m_pCurrentSituation != nullptr)
		m_pCurrentSituation->UpdateSituation();
}

void SituationMgr::Release()
{
	delete m_pCurrentSituation;
}

void SituationMgr::ChangeSituation(SITUATION_TYPE _situationType)
{
	if (m_umSituationMap.find(_situationType) == m_umSituationMap.end())
		return;

	if (m_pCurrentSituation != nullptr)
		m_pCurrentSituation->EndSituation();
	m_pCurrentSituation = m_umSituationMap[_situationType];
	m_pCurrentSituation->StartSituation();
}
