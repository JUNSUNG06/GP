#include "pch.h"
#include "LinearActionMgr.h"
#include "LinearAction.h"

void LinearActionMgr::Init()
{
	m_mLienrActions.clear();
}

void LinearActionMgr::Update()
{
	/*for (auto iter = m_mLienrActions.begin(); iter != m_mLienrActions.end(); iter++)
	{
		if (!iter->second->DoAciton())
		{
			wstring _strName = iter->second->m_strName;

			delete m_mLienrActions[_strName];
			m_mLienrActions.erase(m_mLienrActions.find(_strName));
			iter--;
		}
	}*/

	for (auto pair : m_mLienrActions)
	{
		if (!pair.second->DoAciton())
		{
			wstring _strName = pair.second->m_strName;

			//m_mLienrActions.erase(m_mLienrActions.find(_strName));
			m_vecClearVec.push_back(_strName);
		}
	}

	for (auto name : m_vecClearVec)
	{
		if (m_mLienrActions.find(name) != m_mLienrActions.end())
		{
			m_mLienrActions.erase(name);
		}
	}
}

void LinearActionMgr::Release()
{
	for (auto action : m_mLienrActions)
	{
		wstring _strName = action.second->m_strName;

		delete m_mLienrActions[_strName];
		m_mLienrActions.erase(m_mLienrActions.find(_strName));
	}
}

void LinearActionMgr::CreateLinearAction(wstring _strName, void(*_pAction)(float _fTime), float _fTime)
{
	if (m_mLienrActions.find(_strName) != m_mLienrActions.end())
		return;

	LinearAction* action = new LinearAction(_strName, _pAction, _fTime);
	m_mLienrActions.insert({ _strName, action });
}

void LinearActionMgr::RemoveLinerAction(wstring _strName)
{
	if (m_mLienrActions.find(_strName) != m_mLienrActions.end())
	{
		delete m_mLienrActions[_strName];
		m_mLienrActions.erase(m_mLienrActions.find(_strName));
	}
}
