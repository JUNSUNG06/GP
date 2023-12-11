#include "pch.h"
#include "SceneMgr.h"
#include "Intro_Scene.h"
#include "Start_Scene.h"
#include "Game_Scene.h"
#include "Result_Scene.h"
#include "Explanation_Scene.h"
#include "SelectGDI.h"

void SceneMgr::Init()
{
	m_pCurScene = nullptr;
	// 씬 등록
	RegisterScene(L"Intro_Scene",std::make_shared<Intro_Scene>());
	RegisterScene(L"Start_Scene",std::make_shared<Start_Scene>());
	RegisterScene(L"Game_Scene", std::make_shared<Game_Scene>());
	RegisterScene(L"Result_Scene", std::make_shared<Result_Scene>());
	RegisterScene(L"Explanation_Scene", std::make_shared<Explanation_Scene>());

	// 첫 씬 지정
	LoadScene(L"Intro_Scene");
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{
	//폰트 바꿔보기!
	//AddFontResource(L"Texture\\한국기계연구원_bold.ttf"); // 한번만 하면 되는건가
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"한국기계연구원_bold");
	//SelectObject(_dc, hFont);
	SelectGDI selectFont(_dc, hFont);

	m_pCurScene->Render(_dc);
}

void SceneMgr::LoadScene(const wstring& _scenename)
{
	// 씬이 있으면
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release();
		m_pCurScene = nullptr;
	}

	auto iter = m_mapScenes.find(_scenename);
	if (iter != m_mapScenes.end())
	{
		m_pCurScene = iter->second;
		m_pCurScene->Init();
	}
}

void SceneMgr::RegisterScene(const wstring& _scenename, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), {_scenename, _scene});
}
