#include "pch.h"
#include "Explanation_Scene.h"
#include "Object.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Core.h"

#include "Player1.h"
#include "Player2.h"


void Explanation_Scene::Init()
{
	SetBackground(L"Background_Intro", L"Texture\\Background_Intro.bmp");

	ResMgr::GetInst()->TexLoad(L"Player1", L"Texture\\Player1.bmp");
	ResMgr::GetInst()->TexLoad(L"Player2", L"Texture\\Player2.bmp");
	ResMgr::GetInst()->TexLoad(L"Portal", L"Texture\\Portal.bmp");
	ResMgr::GetInst()->TexLoad(L"JumpPad", L"Texture\\JumpPad.bmp");

	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->LoadSound(L"Explanation_BGM", L"Sound\\Explanation_Scene_BGM.wav", true);
	ResMgr::GetInst()->Play(L"Explanation_BGM");

	Object* obj = new Object;
	obj->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 - 20}));
	obj->SetScale({ 1200,700 });
	AddObject(obj, OBJECT_GROUP::UI);


	obj = new Button([]() { SceneMgr::GetInst()->LoadScene(L"Intro_Scene"); }, L"���ư���");
	obj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 400 })));
	obj->SetScale(Vec2(190.f, 50.f));
	AddObject(obj, OBJECT_GROUP::UI);

}

void Explanation_Scene::Render(HDC _dc)
{


	Scene::Render(_dc);
	wstring explanation = L"Player 1";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 550, Core::GetInst()->GetResolution().y / 2 - 300, explanation.c_str(), explanation.length());
	explanation = L"���� ȭ��ǥ : ����";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 550, Core::GetInst()->GetResolution().y / 2 - 150, explanation.c_str(), explanation.length());
	explanation = L"���� ȭ��ǥ : ���� �̵�";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 550, Core::GetInst()->GetResolution().y / 2 - 100, explanation.c_str(), explanation.length());
	explanation = L"������ ȭ��ǥ : ������ �̵�";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 550, Core::GetInst()->GetResolution().y / 2 - 50, explanation.c_str(), explanation.length());

	Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2 - 550, 200 };
	Vec2 vScale = { 50,50 };

	TransparentBlt(_dc
		, (int)(vPos.x/* - vScale.x / 2*/)
		, (int)(vPos.y/* - vScale.y / 2*/)
		, ResMgr::GetInst()->TexFind(L"Player1")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player1")->GetHeight(), ResMgr::GetInst()->TexFind(L"Player1")->GetDC()
		, 0, 0, ResMgr::GetInst()->TexFind(L"Player1")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player1")->GetHeight(), RGB(255, 0, 255));

	explanation = L"Player 2";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 200, Core::GetInst()->GetResolution().y / 2 - 300, explanation.c_str(), explanation.length());
	explanation = L"W : ����";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 200, Core::GetInst()->GetResolution().y / 2 - 150, explanation.c_str(), explanation.length());
	explanation = L"A : ���� �̵�";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 200, Core::GetInst()->GetResolution().y / 2 - 100, explanation.c_str(), explanation.length());
	explanation = L"D : ������ �̵�";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - 200, Core::GetInst()->GetResolution().y / 2 - 50, explanation.c_str(), explanation.length());

	vPos = { (int)Core::GetInst()->GetResolution().x / 2 - 200, 200 };
	vScale = { 50,50 };

	TransparentBlt(_dc
		, (int)(vPos.x/* - vScale.x / 2*/)
		, (int)(vPos.y/* - vScale.y / 2*/)
		, ResMgr::GetInst()->TexFind(L"Player2")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player2")->GetHeight(), ResMgr::GetInst()->TexFind(L"Player2")->GetDC()
		, 0, 0, ResMgr::GetInst()->TexFind(L"Player2")->GetWidth(), ResMgr::GetInst()->TexFind(L"Player2")->GetHeight(), RGB(255, 0, 255));

	explanation = L"��Ż";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 100, Core::GetInst()->GetResolution().y / 2 - 300, explanation.c_str(), explanation.length());
	explanation = L"�ٸ� ��Ż��";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 100, Core::GetInst()->GetResolution().y / 2 - 150, explanation.c_str(), explanation.length());
	explanation = L"�����̵� �Ѵ�.";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 100, Core::GetInst()->GetResolution().y / 2 - 100, explanation.c_str(), explanation.length());

	vPos = { (int)Core::GetInst()->GetResolution().x / 2 + 100, 200 };
	vScale = { 50,50 };

	TransparentBlt(_dc
		, (int)(vPos.x/* - vScale.x / 2*/)
		, (int)(vPos.y/* - vScale.y / 2*/)
		, ResMgr::GetInst()->TexFind(L"Portal")->GetWidth(), ResMgr::GetInst()->TexFind(L"Portal")->GetHeight(), ResMgr::GetInst()->TexFind(L"Portal")->GetDC()
		, 0, 0, ResMgr::GetInst()->TexFind(L"Portal")->GetWidth(), ResMgr::GetInst()->TexFind(L"Portal")->GetHeight(), RGB(255, 0, 255));

	explanation = L"������";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 400, Core::GetInst()->GetResolution().y / 2 - 300, explanation.c_str(), explanation.length());
	explanation = L"���� ����";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 400, Core::GetInst()->GetResolution().y / 2 - 150, explanation.c_str(), explanation.length());
	explanation = L"���� �Ѵ�.";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 + 400, Core::GetInst()->GetResolution().y / 2 - 100, explanation.c_str(), explanation.length());

	vPos = { (int)Core::GetInst()->GetResolution().x / 2 + 400, 200 };
	vScale = { 50,50 };

	TransparentBlt(_dc
		, (int)(vPos.x/* - vScale.x / 2*/)
		, (int)(vPos.y/* - vScale.y / 2*/)
		, ResMgr::GetInst()->TexFind(L"JumpPad")->GetWidth() * 1.5, ResMgr::GetInst()->TexFind(L"JumpPad")->GetHeight(), ResMgr::GetInst()->TexFind(L"JumpPad")->GetDC()
		, 0, 0, ResMgr::GetInst()->TexFind(L"JumpPad")->GetWidth(), ResMgr::GetInst()->TexFind(L"JumpPad")->GetHeight(), RGB(255, 0, 255));

	explanation = L"�Ӹ� ���� ȭ��ǥ�� �ִ� �÷��̾ �����̰�,";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - (explanation.length()) * 7.4, Core::GetInst()->GetResolution().y / 2 + 150, explanation.c_str(), explanation.length());
	explanation = L"ȭ�� ���� ������ �ð��� 0�� �Ǿ��� �� ������ ����� �й��մϴ�.";
	TextOut(_dc, Core::GetInst()->GetResolution().x / 2 - (explanation.length()) * 7.4, Core::GetInst()->GetResolution().y / 2 + 200, explanation.c_str(), explanation.length());
}

void Explanation_Scene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}
