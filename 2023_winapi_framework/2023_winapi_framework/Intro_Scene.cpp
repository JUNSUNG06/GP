#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Core.h"
void Intro_Scene::Init()
{
	Object* obj = new Button([](){ SceneMgr::GetInst()->LoadScene(L"Start_Scene");}, L"게임 시작");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	obj->SetScale(Vec2(100.f, 100.f));
	AddObject(obj, OBJECT_GROUP::UI);
}
