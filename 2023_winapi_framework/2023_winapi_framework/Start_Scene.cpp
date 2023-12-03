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

void Start_Scene::Init()
{
	SetBackground(L"Level_1", L"Texture\\Level_1.bmp");
	m_pCollisionTexture = ResMgr::GetInst()->TexLoad(L"LevelCollision", L"Texture\\LevelCollision.bmp");
	//m_pLevelTexture = ResMgr::GetInst()->TexLoad(L"Level", L"Texture\\Level.bmp");
	PixelCollision::GetInst()->SetColorImage(m_pCollisionTexture);

	Player1* pObj = new Player1;
	pObj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, (Core::GetInst()->GetResolution().y / 2) + 100 })));
	pObj->SetScale(Vec2(50.f, 50.f));
	pObj->SetPlayerSpeed(100.f);
	//pObj->SetFireDelay(3.f);
	pObj->SetName(L"Player1");
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	GameMgr::GetInst()->SetPlayer1(pObj);


	Player2* pObj1 = new Player2;
	pObj1->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, (Core::GetInst()->GetResolution().y / 2) - 100 })));
	pObj1->SetScale(Vec2(50.f, 50.f));
	pObj1->SetPlayerSpeed(100.f);
	//pObj1->SetFireDelay(3.f);
	pObj->SetName(L"Player2");
	AddObject(pObj1, OBJECT_GROUP::PLAYER2);
	GameMgr::GetInst()->SetPlayer2(pObj1);


	pObj->SetEnemy(pObj1);
	pObj1->SetEnemy(pObj);

	// ���� ���� �������� ��ġ�� �غ��ô�.

	//Vec2 vResolution = Core::GetInst()->GetResolution();
	//Monster* pMonster = nullptr;
	//int iMonster = 10;		// ���� �� 
	//float fMoveDist = 30.f; // ������ �Ÿ�
	//float fMonsterScale = 50.f; // ���� ũ��
	//// �ػ�x - ( ������ �Ÿ� + ������Ʈ ũ�� /2) * 2 / ���ͼ� -1 
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
	// ���� ����
	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM");

	// �浹üũ�ؾߵǴ°͵��� ��������.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::BULLET2);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER2, OBJECT_GROUP::BULLET);

	SituationMgr::GetInst()->SetSituation(SITUATION_TYPE::REVERSEGRAVITY);
	SituationMgr::GetInst()->StartSituation();
}

void Start_Scene::Update()
{
	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// �� ����
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	/*TransparentBlt(_dc, 0, 0, 
		m_pLevelTexture->GetWidth(), 
		m_pLevelTexture->GetHeight(), 
		m_pLevelTexture->GetDC(), 
		0, 0, 
		m_pLevelTexture->GetWidth(),
		m_pLevelTexture->GetHeight(),
		RGB(255, 0, 255));*/
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
