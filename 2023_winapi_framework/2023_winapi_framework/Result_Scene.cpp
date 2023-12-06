#include "pch.h"
#include "Result_Scene.h"
#include "ResultMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "Button.h"
#include "SituationMgr.h"

void Result_Scene::Init()
{
	m_fCurTime = 0;
	SituationMgr::GetInst()->EndSituation();
	SetBackground(L"Background_Intro", L"Texture\\Background_Intro.bmp");
	if (ResultMgr::GetInst()->GetMatchEnd()) {
		Object* btn = new Button([]() {
			SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
			ResultMgr::GetInst()->ResetPoint();
			},
			L"돌아가기");
		btn->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 300 })));
		btn->SetScale(Vec2(100.f, 30.f));
		AddObject(btn, OBJECT_GROUP::UI);
	}
}

void Result_Scene::Update()
{
	m_fCurTime += fDT;
	if (ResultMgr::GetInst()->GetMatchEnd()) {
		if (KEY_PRESS(KEY_TYPE::SPACE)) {
			SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
		}
	}
	else {
		if (m_fCurTime >= 2)
			SceneMgr::GetInst()->LoadScene(L"Start_Scene"); // it was Start_Scene
	}
	Scene::Update();
}

void Result_Scene::Render(HDC _dc)
{

	Scene::Render(_dc);

	SetBkMode(_dc, TRANSPARENT);

	if (!ResultMgr::GetInst()->GetMatchEnd()) {
		RECT_RENDER(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 , 100, 50, _dc);

		wstring score = std::to_wstring(ResultMgr::GetInst()->GetPlayer1Wins()) + L" : " + std::to_wstring(ResultMgr::GetInst()->GetPlayer2Wins());
		TextOut(_dc, (Core::GetInst()->GetResolution().x / 2) - score.length() * 4,
			(Core::GetInst()->GetResolution().y / 2) - 10, score.c_str(), score.length());

		ResMgr::GetInst()->TexLoad(L"Player1", L"Texture\\Player1.bmp");
		Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2 - 400, (int)Core::GetInst()->GetResolution().y / 2 };
		Vec2 vScale = { 50,50 };

		TransparentBlt(_dc
			, (int)(vPos.x - ResMgr::GetInst()->TexFind(L"Player1")->GetWidth() * 3 / 2)
			, (int)(vPos.y - ResMgr::GetInst()->TexFind(L"Player1")->GetHeight() * 3 / 2)
			, ResMgr::GetInst()->TexFind(L"Player1")->GetWidth() * 3, ResMgr::GetInst()->TexFind(L"Player1")->GetHeight() * 3
			, ResMgr::GetInst()->TexFind(L"Player1")->GetDC()
			, 0, 0, ResMgr::GetInst()->TexFind(L"Player1")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player1")->GetHeight(), RGB(255, 0, 255));

		ResMgr::GetInst()->TexLoad(L"Player2", L"Texture\\Player2.bmp");
		vPos = { (int)Core::GetInst()->GetResolution().x / 2 + 400, (int)Core::GetInst()->GetResolution().y / 2 };
		vScale = { 50,50 };

		TransparentBlt(_dc
			, (int)(vPos.x - ResMgr::GetInst()->TexFind(L"Player2")->GetWidth() * 3 / 2)
			, (int)(vPos.y - ResMgr::GetInst()->TexFind(L"Player2")->GetHeight() * 3 / 2)
			, ResMgr::GetInst()->TexFind(L"Player2")->GetWidth() * 3, ResMgr::GetInst()->TexFind(L"Player2")->GetHeight() * 3
			, ResMgr::GetInst()->TexFind(L"Player2")->GetDC()
			, 0, 0, ResMgr::GetInst()->TexFind(L"Player2")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player2")->GetHeight(), RGB(255, 0, 255));
	}
	else
	{
		wstring result;
		if (ResultMgr::GetInst()->GetPlayer1Wins() > ResultMgr::GetInst()->GetPlayer2Wins()) {
			result = L"Player 1 Win";

			ResMgr::GetInst()->TexLoad(L"Player1", L"Texture\\Player1.bmp");
			Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2 };
			Vec2 vScale = { 50,50 };

			TransparentBlt(_dc
				, (int)(vPos.x - ResMgr::GetInst()->TexFind(L"Player1")->GetWidth() * 3 / 2)
				, (int)(vPos.y - ResMgr::GetInst()->TexFind(L"Player1")->GetHeight() * 3 / 2)
				, ResMgr::GetInst()->TexFind(L"Player1")->GetWidth() * 3, ResMgr::GetInst()->TexFind(L"Player1")->GetHeight() * 3
				, ResMgr::GetInst()->TexFind(L"Player1")->GetDC()
				, 0, 0, ResMgr::GetInst()->TexFind(L"Player1")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player1")->GetHeight(), RGB(255, 0, 255));
		}
		else {
			result = L"Player 2 Win";

			ResMgr::GetInst()->TexLoad(L"Player2", L"Texture\\Player2.bmp");
			Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2 };
			Vec2 vScale = { 50,50 };

			TransparentBlt(_dc
				, (int)(vPos.x - ResMgr::GetInst()->TexFind(L"Player2")->GetWidth() * 3 / 2)
				, (int)(vPos.y - ResMgr::GetInst()->TexFind(L"Player2")->GetHeight() * 3 / 2)
				, ResMgr::GetInst()->TexFind(L"Player2")->GetWidth() * 3, ResMgr::GetInst()->TexFind(L"Player2")->GetHeight() * 3
				, ResMgr::GetInst()->TexFind(L"Player2")->GetDC()
				, 0, 0, ResMgr::GetInst()->TexFind(L"Player2")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player2")->GetHeight(), RGB(255, 0, 255));
		}

		TextOut(_dc, (Core::GetInst()->GetResolution().x / 2) - result.length() * 5.2,
			(Core::GetInst()->GetResolution().y / 2) + 100, result.c_str(), result.length());
	}
}

void Result_Scene::Release()
{
	Scene::Release();
}
