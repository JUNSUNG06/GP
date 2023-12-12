#include "pch.h"
#include "LinearAction.h"
#include "TimeMgr.h"

LinearAction::LinearAction(wstring _strName, std::function<void(float)> _pAction, float _fTime)
	: m_pAction(_pAction)
	, m_fTime(_fTime)
	, m_fCurrentTime(0.f)
	, m_strName(_strName)
{
}

LinearAction::~LinearAction()
{
}

bool LinearAction::DoAciton()
{
	m_pAction(m_fCurrentTime / m_fTime);

	m_fCurrentTime += fDT;

	return m_fCurrentTime <= m_fTime;
}
