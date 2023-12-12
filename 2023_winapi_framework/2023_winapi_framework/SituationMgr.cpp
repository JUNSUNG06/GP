#include "pch.h"
#include "SituationMgr.h"
#include "Situation.h"
#include "ReverseGravitySituation.h"
#include "ReverseInputSituation.h"
#include "IncreseMoveSpeedSituation.h"
#include "RotateMapSituation.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include <time.h>
#include "Core.h"

void SituationMgr::Init()
{
	m_pCurrentSituation = nullptr;
	srand((unsigned int)time(NULL));

	SITUATION_TYPE situationType;

	situationType = SITUATION_TYPE::REVERSE_GRAVITY;
	RegistSituation(situationType, new ReverseGravitySituation(situationType));
	situationType = SITUATION_TYPE::REVERSE_INPUT;
	RegistSituation(situationType, new ReverseInputSituation(situationType));
	situationType = SITUATION_TYPE::INCREASE_MOVE_SPEED;
	RegistSituation(situationType, new IncreseMoveSpeedSituation(situationType));
	situationType = SITUATION_TYPE::ROTATE_MAP;
	RegistSituation(situationType, new RotateMapSituation(situationType));
	
	m_fCurrentSituationTime = 0;
	m_fSituationChagneInterval = 5.f;
	m_fCurrentSitautionChangeTime = 0.f;
	m_bInSituation = false;
}

void SituationMgr::Udpate()
{
	if (SceneMgr::GetInst()->GetCurScene() !=
		SceneMgr::GetInst()->GetScene(L"Start_Scene"))
	{
		return;
	}

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
			int type = 4;
			SetSituation((SITUATION_TYPE)type);
			StartSituation();
		}
	}
}

void SituationMgr::Render(HDC _dc)
{
	if (m_pCurrentSituation != nullptr)
	{
		POINT pRes = Core::GetInst()->GetResolution();
		RECT rt = { 0, 30, pRes.x, 105};
		HFONT hFont = CreateFont(75, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));
		HFONT hOldFont = (HFONT)SelectObject(_dc, hFont);
		SetBkMode(_dc, TRANSPARENT);
		DrawText(_dc, m_pCurrentSituation->GetDescription().c_str(), -1, &rt
			, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_dc, hOldFont);
		DeleteObject(hFont);
	}
}

void SituationMgr::Release()
{
	delete m_pCurrentSituation;
}

void SituationMgr::StartSituation()
{
	if (SceneMgr::GetInst()->GetCurScene() !=
		SceneMgr::GetInst()->GetScene(L"Start_Scene"))
	{
		return;
	}

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
