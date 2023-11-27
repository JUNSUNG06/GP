#include "pch.h"
#include "Result_Scene.h"
#include "ResultMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

void Result_Scene::Init()
{
	m_fCurTime = 0;
	Scene::Init();
}

void Result_Scene::Update()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= 3) {
		SceneMgr::GetInst()->LoadScene(L"Start_Scene");
	}
	Scene::Update();
}

void Result_Scene::Render(HDC _dc)
{
	wstring score = std::to_wstring(ResultMgr::GetInst()->GetPlayer1Wins()) + L" : " + std::to_wstring(ResultMgr::GetInst()->GetPlayer2Wins());
	TextOut(_dc, 100, 100, score.c_str(), score.length());
	Scene::Render(_dc);
}

void Result_Scene::Release()
{
	Scene::Release();
}
