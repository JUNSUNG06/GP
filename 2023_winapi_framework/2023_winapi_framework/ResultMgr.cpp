#include "pch.h"
#include "ResultMgr.h"
#include "SceneMgr.h"
#include "Object.h"

void ResultMgr::ResetPoint()
{
	m_iPlayer1Win = 0;
	m_iPlayer2Win = 0;
}

void ResultMgr::PlayerDied(const Object* _pObj)
{
	if (_pObj->GetName() == L"Player1") {
		m_iPlayer2Win++;
	}
	else if (_pObj->GetName() == L"Player2") {
		m_iPlayer1Win++;
	}
	SceneMgr::GetInst()->LoadScene(L"Result_Scene");


	if (m_iPlayer1Win >= m_iMaxPoint) {
		
		//ResetPoint();
	}
}
