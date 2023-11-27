#include "pch.h"
#include "Player2.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "EventMgr.h"
#include "ResultMgr.h"

Player2::Player2()
	: m_pTex(nullptr)
	, m_iHP(5)
	, m_bIsDie(false)
	, m_fPlayerSpeed(100.f)
	, m_fFireDelay(0.f)
	, m_fCurFireDelay(3.f)
	, m_fBulletSpeed(3.f)
	, m_pEnemy(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
}

Player2::~Player2()
{
}

void Player2::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESS(KEY_TYPE::A))
	{
		vPos.x -= m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::D))
	{
		vPos.x += m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	if (KEY_PRESS(KEY_TYPE::W))
	{
		vPos.y -= m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	if (KEY_PRESS(KEY_TYPE::S))
	{
		vPos.y += m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	SetPos(vPos);


	m_fCurFireDelay += fDT;
	if (m_fCurFireDelay >= m_fFireDelay) {
		Attack();
		m_fCurFireDelay = 0;
	}
}

void Player2::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player2::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player1_Bullet")
	{
		m_iHP--;
		if (m_iHP <= 0) {
			m_bIsDie = true;
			EventMgr::GetInst()->DeleteObject(this);
			ResultMgr::GetInst()->PlayerDied(2);
		}
	}
}

void Player2::ExitCollision(Collider* _pOther)
{
}

void Player2::StayCollision(Collider* _pOther)
{
}

void Player2::Attack()
{
	Bullet* pBullet = new Bullet;
	Vec2 vBulletPos = GetPos();
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	//	pBullet->SetDir(M_PI / 4 * 7);
	//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(-10.f, -15.f));
	pBullet->SetDir({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y });
	pBullet->SetName(L"Player2_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET2);
}
