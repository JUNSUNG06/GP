#include "pch.h"
#include "GameMgr.h"
#include "TimeMgr.h"
#include "Core.h"
#include "TagMgr.h"
#include "ResultMgr.h"
#include <iostream>

void GameMgr::Init()
{
	m_bIsPlay = false;
	m_fCurrentPlayTime = 121.f;
}


void GameMgr::Update()
{
	if (m_bIsPlay)
	{
		m_fCurrentPlayTime -= fDT;

		if (m_fCurrentPlayTime <= 0)
			EndGame();
	}
}

void GameMgr::Render(HDC _dc)
{
	if (m_bIsPlay)
	{
		HFONT hFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));
		HFONT hOldFont = (HFONT)SelectObject(_dc, hFont);
		SetBkMode(_dc, TRANSPARENT);

		RECT rt = RECT_MAKE(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 15, 200, 45);

		DrawText(_dc, std::to_wstring((int)m_fCurrentPlayTime).c_str(), -1, &rt
			, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_dc, hOldFont);
		DeleteObject(hFont);
	}
}

void GameMgr::StartGame()
{
	m_bIsPlay = true;
}

void GameMgr::EndGame()
{
	Object* tagger = TagMgr::GetInst()->GetTagger();

	if (tagger->GetName() == L"Player1")
	{
		SetPlayer1Died(true);
		ResultMgr::GetInst()->PlayerDied(1);
	}
	else if(tagger->GetName() == L"Player2")
	{
		SetPlayer2Died(true);
		ResultMgr::GetInst()->PlayerDied(2);
	}

	m_bIsPlay = false;
	m_fCurrentPlayTime = 11.f;
}
