#include "pch.h"
#include "Explanation_Scene.h"
#include "Object.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Core.h"

void Explanation_Scene::Init()
{
	SetBackground(L"Background_Intro", L"Texture\\Background_Intro.bmp");

	Object* obj = new Button([]() { SceneMgr::GetInst()->LoadScene(L"Intro_Scene"); }, L"돌아가기");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 60 })));
	obj->SetScale(Vec2(100.f, 30.f));
	AddObject(obj, OBJECT_GROUP::UI);
}

void Explanation_Scene::Render(HDC _dc)
{
	RECT_RENDER(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2, 1000, 1000, _dc);
	Scene::Render(_dc);
}
