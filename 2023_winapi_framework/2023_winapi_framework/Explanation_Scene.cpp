#include "pch.h"
#include "Explanation_Scene.h"
#include "Object.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Core.h"

void Explanation_Scene::Init()
{
	SetBackground(L"Background_Intro", L"Texture\\Background_Intro.bmp");

	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->LoadSound(L"Explanation_BGM", L"Sound\\Explanation_Scene_BGM.wav", true);
	ResMgr::GetInst()->Play(L"Explanation_BGM");

	Object* obj = new Object;
	obj->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 }));
	obj->SetScale({ 900,600 });
	AddObject(obj, OBJECT_GROUP::UI);


	obj = new Button([]() { SceneMgr::GetInst()->LoadScene(L"Intro_Scene"); }, L"돌아가기");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 400 })));
	obj->SetScale(Vec2(100.f, 30.f));
	AddObject(obj, OBJECT_GROUP::UI);
}

void Explanation_Scene::Render(HDC _dc)
{


	Scene::Render(_dc);
	wstring explanation = L"Player 1";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 400, Core::GetInst()->GetResolution().y / 2 - 200, explanation.c_str(), explanation.length());
	explanation = L"위쪽 화살표 : 점프";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 400, Core::GetInst()->GetResolution().y / 2 - 50, explanation.c_str(), explanation.length());
	explanation = L"왼쪽 화살표 : 왼쪽 이동";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 400, Core::GetInst()->GetResolution().y / 2 + 50, explanation.c_str(), explanation.length());
	explanation = L"오른쪽 화살표 : 오른쪽 이동";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 400, Core::GetInst()->GetResolution().y / 2 + 150, explanation.c_str(), explanation.length());

	explanation = L"Player 2";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 50, Core::GetInst()->GetResolution().y / 2 - 200, explanation.c_str(), explanation.length());
	explanation = L"W : 점프";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 50, Core::GetInst()->GetResolution().y / 2 - 50, explanation.c_str(), explanation.length());
	explanation = L"A : 왼쪽 이동";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 50, Core::GetInst()->GetResolution().y / 2 + 50, explanation.c_str(), explanation.length());
	explanation = L"D : 오른쪽 이동";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 50, Core::GetInst()->GetResolution().y / 2 + 150, explanation.c_str(), explanation.length());
}

void Explanation_Scene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}
