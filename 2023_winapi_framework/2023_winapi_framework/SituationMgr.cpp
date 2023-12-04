#include "pch.h"
#include "SituationMgr.h"
#include "Situation.h"
#include "ReverseGravitySituation.h"
#include "TimeMgr.h"
#include <time.h>

void SituationMgr::Init()
{
	m_pCurrentSituation = nullptr;

	SITUATION_TYPE situationType;

	situationType = SITUATION_TYPE::REVERSEGRAVITY;
	RegistSituation(situationType, new ReverseGravitySituation(situationType));
	m_fCurrentSituationTime = 0;
	m_fSituationChagneInterval = 5.f;
	m_fCurrentSitautionChangeTime = 0.f;
	m_bInSituation = false;
	srand((unsigned int)time(NULL));
}

void SituationMgr::Udpate()
{
	if (m_bInSituation)
	{
		if (m_pCurrentSituation != nullptr)
		{
			m_pCurrentSituation->UpdateSituation();
			m_fCurrentSituationTime += fDT;

			if (m_fCurrentSituationTime >= m_pCurrentSituation->GetDuration())
				EndSituation();
		}
	}
	else
	{
		m_fCurrentSitautionChangeTime += fDT;

		if (m_fCurrentSitautionChangeTime >= m_fSituationChagneInterval)
		{
			m_fCurrentSitautionChangeTime = 0.f;
			int type = rand() % (int)SITUATION_TYPE::END;
			SetSituation((SITUATION_TYPE)type);
			StartSituation();
		}
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
	m_bInSituation = false;
}

void SituationMgr::SetSituation(SITUATION_TYPE _situationType)
{
	if (m_umSituationMap.find(_situationType) == m_umSituationMap.end())
		return;

	m_pCurrentSituation = m_umSituationMap[_situationType];
	m_bInSituation = true;
}
