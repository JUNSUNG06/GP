#include "pch.h"
#include "ResultMgr.h"
#include "SceneMgr.h"
#include "Object.h"
#include "TimeMgr.h"
#include "GameMgr.h"


void ResultMgr::Init()
{
	m_iPlayer1Win = 0;
	m_iPlayer2Win = 0;
	m_iMaxPoint = 1;
	m_fCurTime = 0;
	m_bIsGameEnded = false;
}

void ResultMgr::Update()
{
	if (m_bIsGameEnded)
		m_fCurTime += fDT;
	if (m_fCurTime >= 1) {
		SceneMgr::GetInst()->LoadScene(L"Result_Scene");
		GameMgr::GetInst()->SetPlayer1Died(false);
		GameMgr::GetInst()->SetPlayer2Died(false);
		m_bIsGameEnded = false;
		m_fCurTime = 0;
	}
}

void ResultMgr::ResetPoint()
{
	m_iPlayer1Win = 0;
	m_iPlayer2Win = 0;
}

void ResultMgr::PlayerDied(int _iPlayeridx)
{
	if (_iPlayeridx == 1 && !GameMgr::GetInst()->GetPlayer2Died()) {
		GameMgr::GetInst()->SetPlayer1Died(true);
		m_iPlayer2Win++;
	}
	else if (_iPlayeridx == 2 && !GameMgr::GetInst()->GetPlayer1Died()) {
		GameMgr::GetInst()->SetPlayer2Died(true);
		m_iPlayer1Win++;
	}

	m_bIsGameEnded = true;
}
