#include "pch.h"
#include "RotateMapSituation.h"
#include "Texture.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "LinearActionMgr.h"
#include <string>
#include <iostream>

RotateMapSituation::RotateMapSituation(SITUATION_TYPE _eSitutationType)
	: Situation(_eSitutationType)
{
	m_fDuration = 15.f;
	m_sDescription = L"땅이 회전합니다.";
}

RotateMapSituation::~RotateMapSituation()
{
}

void RotateMapSituation::StartSituation()
{
	LinearActionMgr::GetInst()->CreateLinearAction(
		L"RotateBackground",
		[&](float _fPercent)
		{
			Texture* m_pBack = SceneMgr::GetInst()
				->GetCurScene()->GetBackground();

			if (m_pBack)
			{
				float _fAngle = 360.f * _fPercent;
				m_sDescription = std::to_wstring(_fAngle);
				m_pBack->SetAngle(_fAngle);
			}
		}, 
		m_fDuration - 0.1f);
}

void RotateMapSituation::UpdateSituation()
{
}

void RotateMapSituation::EndSituation()
{
	Texture* m_pBack = SceneMgr::GetInst()
		->GetCurScene()->GetBackground();

	if (m_pBack)
		m_pBack->SetAngle(0.f);
}
