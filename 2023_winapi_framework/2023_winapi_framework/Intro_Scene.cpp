#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Core.h"
void Intro_Scene::Init()
{
	SetBackground(L"Background_Intro", L"Texture\\Background_Intro.bmp");

	Object* obj = new Button([](){ SceneMgr::GetInst()->LoadScene(L"Start_Scene");}, L"���� ����");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	obj->SetScale(Vec2(100.f, 30.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new Button([]() { SceneMgr::GetInst()->LoadScene(L"Start_Scene"); }, L"���� ����");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 60 })));
	obj->SetScale(Vec2(100.f, 30.f));
	AddObject(obj, OBJECT_GROUP::UI);

	obj = new Button([]() { SendMessage(Core::GetInst()->GetHwnd(), WM_CLOSE, 0, 0); }, L"���� ����");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 120 })));
	obj->SetScale(Vec2(100.f, 30.f));
	AddObject(obj, OBJECT_GROUP::UI);
}