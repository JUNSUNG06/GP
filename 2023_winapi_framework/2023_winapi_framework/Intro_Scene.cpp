#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Core.h"
#include "SelectGDI.h"
#include "ResMgr.h"
#include "Explanation_Scene.h"
#include "ResultMgr.h"
#include "LinearActionMgr.h"
void Intro_Scene::Init()
{
	SetBackground(L"Background_Intro", L"Texture\\Background_Intro.bmp");

	//����
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->LoadSound(L"Main_Menu_BGM", L"Sound\\Main_Menu_BGM.wav", true);
	ResMgr::GetInst()->LoadSound(L"Button_Click", L"Sound\\Button_Click.wav", false);

	ResMgr::GetInst()->Play(L"Main_Menu_BGM");

	Object* obj = new Button([]()
		{
			SceneMgr::GetInst()->LoadScene(L"Start_Scene");
		}
	, L"���� ����");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	obj->SetScale(Vec2(190.f, 50.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new Button([]() 
		{ SceneMgr::GetInst()->LoadScene(L"Explanation_Scene"); }, L"���� ����"); 
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 80 })));
	obj->SetScale(Vec2(190.f, 50.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new Button([]() { SendMessage(Core::GetInst()->GetHwnd(), WM_CLOSE, 0, 0); }, L"���� ����");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 160 })));
	obj->SetScale(Vec2(190.f, 50.f));
	AddObject(obj, OBJECT_GROUP::UI);

	/*LinearActionMgr::GetInst()->CreateLinearAction(L"Tset", 
		[](float _fTime) { if (_fTime >= 1.5f) SceneMgr::GetInst()->LoadScene(L"Start_Scene"); }, 3.f);*/
}

void Intro_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	POINT pRes = Core::GetInst()->GetResolution();
	RECT rt = { 0, 180, pRes.x, 300 };
	HFONT hFont = CreateFont(120, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, L"�ѱ���迬����_bold");

	HFONT hOldFont = (HFONT)SelectObject(_dc, hFont);
	SetBkMode(_dc, TRANSPARENT);
	DrawText(_dc, L"�����������", -1, &rt
		, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(_dc, hOldFont);
	DeleteObject(hFont);
}

void Intro_Scene::Release()
{
	Scene::Release();
}
