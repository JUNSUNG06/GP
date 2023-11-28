#include "pch.h"
#include "Result_Scene.h"
#include "ResultMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"

void Result_Scene::Init()
{
	m_fCurTime = 0;
}

void Result_Scene::Update()
{
	m_fCurTime += fDT;
	if (ResultMgr::GetInst()->GetMatchEnd()) {
		if (KEY_PRESS(KEY_TYPE::SPACE)) {
			SceneMgr::GetInst()->LoadScene(L"Start_Scene");
			ResultMgr::GetInst()->ResetPoint();
		}
	}
	else {
		if (m_fCurTime >= 3)
			SceneMgr::GetInst()->LoadScene(L"Start_Scene");
	}
	Scene::Update();
}

void Result_Scene::Render(HDC _dc)
{
	wstring score = std::to_wstring(ResultMgr::GetInst()->GetPlayer1Wins()) + L" : " + std::to_wstring(ResultMgr::GetInst()->GetPlayer2Wins());
	TextOut(_dc, 100, 100, score.c_str(), score.length());

	if (ResultMgr::GetInst()->GetMatchEnd()) {
		wstring result;
		if (ResultMgr::GetInst()->GetPlayer1Wins() > ResultMgr::GetInst()->GetPlayer2Wins()) {
			result = L"Player 1 Win";
		}
		else {
			result = L"Player 2 Win";
		}
		wstring space = L"press spacebar";
		TextOut(_dc, 100, 200, result.c_str(), result.length());
		TextOut(_dc, 100, 250, space.c_str(), space.length());
	}
	Scene::Render(_dc);
}

void Result_Scene::Release()
{
	Scene::Release();
}
