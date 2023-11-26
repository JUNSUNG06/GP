#include "pch.h"
#include "Player1.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"

Player1::Player1()
	: m_pTex(nullptr)
	, m_iHP(1)
	, m_fPlayerSpeed(100.f)
	, m_fFireDelay(0.f)
	, m_fCurFireDelay(3.f)
	, m_fBulletSpeed(3.f)
	, m_pEnemy(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
}

Player1::~Player1()
{
}

void Player1::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		vPos.x -= m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		vPos.x += m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	SetPos(vPos);


	m_fCurFireDelay += fDT;
	if (m_fCurFireDelay >= m_fFireDelay) {
		Attack();
		m_fCurFireDelay = 0;
	}
}

void Player1::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player1::Attack()
{
	Bullet* pBullet = new Bullet;
	Vec2 vBulletPos = GetPos();
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	//	pBullet->SetDir(M_PI / 4 * 7);
	//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(-10.f, -15.f));
	pBullet->SetDir({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y });
	pBullet->SetName(L"Player_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}
