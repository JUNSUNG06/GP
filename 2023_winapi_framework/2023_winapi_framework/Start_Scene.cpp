#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Player1.h"
#include "Player2.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "ResultMgr.h"
#include "PixelCollision.h"
#include "GameMgr.h"
#include "SituationMgr.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "PausePanel.h"
#include "TagMgr.h"
#include "JumpPad.h"
#include "GameMgr.h"

#include "TeleportMgr.h"

void Start_Scene::Init()
{
	SetBackground(L"Level_1", L"Texture\\Level_1.bmp");

	PausePanel* pspn = new PausePanel;
	pspn->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 }));
	pspn->SetScale(Vec2(300, 300));
	AddObject(pspn, OBJECT_GROUP::UI);

	m_pCollisionTexture = ResMgr::GetInst()->TexLoad(L"LevelCollision", L"Texture\\LevelCollision.bmp");
	PixelCollision::GetInst()->SetColorImage(m_pCollisionTexture);

	Player1* pObj = new Player1;
	pObj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 4 * 3, (Core::GetInst()->GetResolution().y / 2) })));
	pObj->SetScale(Vec2(25.f, 25.f));
	pObj->SetPlayerSpeed(250.f);
	//pObj->SetFireDelay(3.f);
	pObj->SetName(L"Player1");
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	GameMgr::GetInst()->SetPlayer1(pObj);


	Player2* pObj1 = new Player2;
	pObj1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 4 * 1, (Core::GetInst()->GetResolution().y / 2) })));
	pObj1->SetScale(Vec2(25.f, 25.f));
	pObj1->SetPlayerSpeed(250.f);
	//pObj1->SetFireDelay(3.f);
	pObj1->SetName(L"Player2");
	AddObject(pObj1, OBJECT_GROUP::PLAYER2);
	GameMgr::GetInst()->SetPlayer2(pObj1);

	JumpPad* pad = new JumpPad;
	pad->SetPos(Vec2({16 + 25, 836}));
	pad->SetScale(Vec2({50, 24}));
	pad->SetName(L"JumpPad1");
	AddObject(pad, OBJECT_GROUP::JUMPPAD);
	JumpPad* pad2 = new JumpPad;
	pad2->SetPos(Vec2({ Core::GetInst()->GetResolution().x - 16 - 25, 836}));
	pad2->SetScale(Vec2({ 50, 24 }));
	pad2->SetName(L"JumpPad2");
	AddObject(pad2, OBJECT_GROUP::JUMPPAD);

	pObj->SetEnemy(pObj1);
	pObj1->SetEnemy(pObj);

	TagMgr::GetInst()->ChooseRandomTagger();

	TeleportMgr::GetInst()->StartSetup();

	// 몬스터 세팅 마구마구 배치를 해봅시다.

	//Vec2 vResolution = Core::GetInst()->GetResolution();
	//Monster* pMonster = nullptr;
	//int iMonster = 10;		// 몬스터 수 
	//float fMoveDist = 30.f; // 움직일 거리
	//float fMonsterScale = 50.f; // 몬스터 크기
	//// 해상도x - ( 움직일 거리 + 오브젝트 크기 /2) * 2 / 몬스터수 -1 
	//float fTerm = (vResolution.x - (fMoveDist + fMonsterScale / 2.f) * 2) 
	//				/ (float)(iMonster -1);
	//for (int i = 0; i < iMonster; ++i)
	//{
	//	pMonster = new Monster;
	//	pMonster->SetPos(Vec2(
	//		(fMoveDist + fMonsterScale / 2.f) + i* fTerm
	//		,300.f));
	//	pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
	//	pMonster->SetCenterPos(pMonster->GetPos());
	//	pMonster->SetMoveDis(fMoveDist);
	//	AddObject(pMonster, OBJECT_GROUP::MONSTER);
	//}
	// 사운드 세팅
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->LoadSound(L"Game_Scene_BGM", L"Sound\\Game_Scene_BGM.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResMgr::GetInst()->Play(L"Game_Scene_BGM");

	// 충돌체크해야되는것들을 설정하자.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::BULLET2);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER2, OBJECT_GROUP::BULLET);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::PLAYER2);
	//CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER2, OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::JUMPPAD, OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::JUMPPAD, OBJECT_GROUP::PLAYER2);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::TELEPORT, OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::TELEPORT, OBJECT_GROUP::PLAYER2);

	//ui
	ResMgr::GetInst()->TexLoad(L"Heart", L"Texture\\Heart.bmp");
	ResMgr::GetInst()->LoadSound(L"Attack", L"Sound\\Attack.wav", false);
	ResMgr::GetInst()->LoadSound(L"Hit", L"Sound\\Hit.wav", false);

	GameMgr::GetInst()->StartGame();
}

void Start_Scene::Update()
{
	Scene::Update();
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	//wstring s = L"isPause: " + std::to_wstring(TimeMgr::GetInst()->GetIsPause()) + L" dt: " + std::to_wstring(TimeMgr::GetInst()->GetDT());
	//TextOut(_dc, 100, 100, s.c_str(), s.length());
	//wstring s = L"Tagger: " + TagMgr::GetInst()->GetTagger()->GetName();
	//TextOut(_dc, 100, 100, s.c_str(), s.length());
	//wstring ss = L"timer: " + std::to_wstring(TeleportMgr::GetInst()->getcurtime());
	//TextOut(_dc, 100, 200, ss.c_str(), ss.length());

	//heart ui
	/*long long player1hp = GameMgr::GetInst()->GetPlayer1()->GetPlayerHP();
	int Width = ResMgr::GetInst()->TexFind(L"Heart")->GetWidth();
	int Height = ResMgr::GetInst()->TexFind(L"Heart")->GetHeight();
	Vec2 vPos = { 10, 10 };
	Vec2 vScale = { 30, 30 };
	if ((player1hp) < 0 || (player1hp) > 50)
		player1hp = 0;
	for (size_t i = 0; i < (player1hp); i++)
	{
		TransparentBlt(_dc
			, (int)(vPos.x - vScale.x / 2)
			, (int)(vPos.y - vScale.y / 2)
			, Width, Height, ResMgr::GetInst()->TexFind(L"Heart")->GetDC()
			, 0, 0, Width, Height, RGB(255, 0, 255));
		vPos.x += Width + 10;
	}


	int player2hp = GameMgr::GetInst()->GetPlayer2()->GetPlayerHP();
	vPos = { 1490,  10 };
	vScale = { 30, 30 };
	if ((player2hp) < 0 || (player2hp) > 50)
		player2hp = 0;
	for (size_t i = 0; i < player2hp; i++)
	{
		TransparentBlt(_dc
			, (int)(vPos.x - vScale.x / 2)
			, (int)(vPos.y - vScale.y / 2)
			, Width, Height, ResMgr::GetInst()->TexFind(L"Heart")->GetDC()
			, 0, 0, Width, Height, RGB(255, 0, 255));
		vPos.x -= Width + 10;
	}*/
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
