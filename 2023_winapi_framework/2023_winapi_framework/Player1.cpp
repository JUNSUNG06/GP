#include "pch.h"
#include "Player1.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "EventMgr.h"
#include "ResultMgr.h"
#include "Rigidbody.h"
#include "PixelCollision.h"

Player1::Player1()
	: m_pTex(nullptr)
	, m_iHP(5)
	, m_bIsDie(false)
	, m_fPlayerSpeed(100.f)
	, m_fFireDelay(1.f)
	, m_fCurFireDelay(3.f)
	, m_fBulletSpeed(3.f)
	, m_pEnemy(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
	m_pRigidbody = new Rigidbody(this);
}

Player1::~Player1()
{
}

void Player1::Update()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

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
	//if (KEY_PRESS(KEY_TYPE::UP))
	//{
	//	vPos.y -= m_fPlayerSpeed * fDT;
	//	//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	//}
	//if (KEY_PRESS(KEY_TYPE::DOWN))
	//{
	//	vPos.y += m_fPlayerSpeed * fDT;
	//	//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	//}

	if (PixelCollision::GetInst()->CheckCollision(
		vPos.x - vScale.x / 2, vPos.y,
		vPos.x + vScale.x / 2, vPos.y + vScale.y / 2))
	{
		m_pRigidbody->SetApplyGravity(false);
		m_pRigidbody->SetVelocity({ 
			(float)m_pRigidbody->GetVelocity().x, 0.f });
	}
	else
	{
		m_pRigidbody->SetApplyGravity(true);
	}
	m_pRigidbody->Update();


	vPos += m_pRigidbody->GetVelocity();

	SetPos(vPos);


	m_fCurFireDelay += fDT;
	if (m_fCurFireDelay >= m_fFireDelay && m_pEnemy != nullptr) {
		Attack();
		m_fCurFireDelay = 0;
	}
}

void Player1::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Component_Render(_dc);

	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);\
}

void Player1::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player2_Bullet")
	{
		m_iHP--;
		if (m_iHP <= 0) {
			m_bIsDie = true;
			ResultMgr::GetInst()->PlayerDied(1);
			EventMgr::GetInst()->DeleteObject(this);
		}
	}
}

void Player1::ExitCollision(Collider* _pOther)
{
}

void Player1::StayCollision(Collider* _pOther)
{
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
	if (Vec2({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y }).Length() != 0)
		pBullet->SetDir({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y });
	pBullet->SetName(L"Player1_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}
