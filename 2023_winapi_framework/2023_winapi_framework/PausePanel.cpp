#include "pch.h"
#include "PausePanel.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Button.h"
#include "Object.h"
#include "Core.h"
#include "Scene.h"

PausePanel::PausePanel()
{
	m_oContinueBtn = new Button([]() {TimeMgr::GetInst()->SetIsPause(false); }, L"Continue");
	m_oContinueBtn->SetPos(Vec2({ 0,0 }));
	m_oContinueBtn->SetScale(Vec2(190, 50));
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_oContinueBtn, OBJECT_GROUP::UI);

	m_oExitBtn = new Button([]() {SceneMgr::GetInst()->LoadScene(L"Intro_Scene"); }, L"Exit");
	m_oExitBtn->SetPos(Vec2({ 0,0 }));
	m_oExitBtn->SetScale(Vec2(190, 50));
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_oExitBtn, OBJECT_GROUP::UI);
}

PausePanel::~PausePanel()
{
	TimeMgr::GetInst()->SetIsPause(false);
}

void PausePanel::Update()
{
	if (TimeMgr::GetInst()->GetIsPause())
	{
		m_oContinueBtn->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 }));
		m_oExitBtn->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 100 }));
	}
	else {
		m_oContinueBtn->SetPos(Vec2({ -100,0 }));
		m_oExitBtn->SetPos(Vec2({ -100,0 }));
	}


	if (KEY_DOWN(KEY_TYPE::ESC)) {
		bool curb = TimeMgr::GetInst()->GetIsPause();
		TimeMgr::GetInst()->SetIsPause(!curb);
	}
}

void PausePanel::Render(HDC _dc)
{
	//wstring s = L"isPause in PausePanel: " + std::to_wstring(TimeMgr::GetInst()->GetIsPause());
	//TextOut(_dc, 100, 150, s.c_str(), s.length());

	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//RECT rt = { vPos.x - vScale.x / 2, vPos.y - vScale.y / 2
	//	, vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };
	//RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
}
