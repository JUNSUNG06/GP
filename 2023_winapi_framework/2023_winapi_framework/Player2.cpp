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
#include "Rigidbody.h"
#include "PixelCollision.h"

Player2::Player2()
	: m_pTex(nullptr)
	, m_iHP(5)
	, m_bIsDie(false)
	, m_fPlayerSpeed(100.f)
	, m_fFireDelay(1.f)
	, m_fCurFireDelay(3.f)
	, m_fBulletSpeed(3.f)
	, m_pEnemy(nullptr)
	, m_fJumpPower(250.f)
	, m_bIsGround(false)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
	m_pRigidbody = new Rigidbody(this);
}

Player2::~Player2()
{
}

void Player2::Update()
{
	Vec2 vPos = GetPos();

	Move();
	Jump();

	vPos += m_pRigidbody->GetVelocity() * fDT;
	SetPos(vPos);


	//if (KEY_PRESS(KEY_TYPE::A))
	//{
	//	vPos.x -= m_fPlayerSpeed * fDT;
	//	//GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	//}
	//if (KEY_PRESS(KEY_TYPE::D))
	//{
	//	vPos.x += m_fPlayerSpeed * fDT;
	//	//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	//}
	////if (KEY_PRESS(KEY_TYPE::W))
	////{
	////	vPos.y -= m_fPlayerSpeed * fDT;
	////	//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	////}
	////if (KEY_PRESS(KEY_TYPE::S))
	////{
	////	vPos.y += m_fPlayerSpeed * fDT;
	////	//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	////}

	//vPos += m_pRigidbody->GetVelocity();

	//SetPos(vPos);


	m_fCurFireDelay += fDT;
	if (m_fCurFireDelay >= m_fFireDelay && m_fFireDelay && m_pEnemy != nullptr) {
		if (KEY_PRESS(KEY_TYPE::S))
		{
			Attack();
			m_fCurFireDelay = 0;
		}
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
			ResultMgr::GetInst()->PlayerDied(2);
			EventMgr::GetInst()->DeleteObject(this);
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
	if (Vec2({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y }).Length() != 0)
		pBullet->SetDir({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y });
	pBullet->SetName(L"Player2_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET2);
}

void Player2::Move()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (PixelCollision::GetInst()->CheckCollision(
		vPos.x - vScale.x / 2, vPos.y,
		vPos.x + vScale.x / 2, vPos.y + vScale.y / 2))
	{
		m_pRigidbody->SetApplyGravity(false);
		m_pRigidbody->SetVerticalVelocity(0.f);
		m_bIsGround = true;
	}
	else
	{
		m_pRigidbody->SetApplyGravity(true);
		m_bIsGround = false;
	}
	m_pRigidbody->Update();


	if (KEY_PRESS(KEY_TYPE::A))
	{
		//vPos.x -= m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
		m_pRigidbody->SetHorizontalVelocity(-m_fPlayerSpeed);
	}
	else if (KEY_UP(KEY_TYPE::A))
		m_pRigidbody->SetHorizontalVelocity(0);
	if (KEY_PRESS(KEY_TYPE::D))
	{
		//vPos.x += m_fPlayerSpeed * fDT;
		//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
		m_pRigidbody->SetHorizontalVelocity(m_fPlayerSpeed);
	}
	else if (KEY_UP(KEY_TYPE::D))
		m_pRigidbody->SetHorizontalVelocity(0);
	
	//if (KEY_PRESS(KEY_TYPE::DOWN))
	//{
	//	vPos.y += m_fPlayerSpeed * fDT;
	//	//GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	//}

	
}

void Player2::Jump()
{
	if (KEY_PRESS(KEY_TYPE::W) && m_bIsGround == true)
	{
		m_pRigidbody->SetVerticalVelocity(-m_fJumpPower);
	}
}
