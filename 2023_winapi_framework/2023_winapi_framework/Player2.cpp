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
#include "Texture.h"
#include "Core.h"
#include "CameraMgr.h"

Player2::Player2()
	: m_pTex(nullptr)
	, m_iHP(5)
	, m_fPlayerSpeed(500.f)
	, m_bIsDie(false)
	, m_fFireDelay(1.f)
	, m_fCurFireDelay(3.f)
	, m_fBulletSpeed(3.f)
	, m_pEnemy(nullptr)
	, m_fJumpPower(400.f)
	, m_bIsGround(false)
	, m_bCanMoveLeft(true)
	, m_bCanMoveRight(true)
	, m_iJumpCount(2)
	, m_iCurrentJumpCount(0)
{
	m_pHandTex = ResMgr::GetInst()->TexLoad(L"Player2_Hand", L"Texture\\Player2_Hand.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
	m_pRigidbody = new Rigidbody(this);
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player2", L"Texture\\Player2.bmp");
	SetMoveKey(KEY_TYPE::D, KEY_TYPE::A);
	m_fHandDis = 45.f;
}

Player2::~Player2()
{
	if (m_pRigidbody != nullptr)
		delete m_pRigidbody;
}

void Player2::Update()
{
	Vec2 vPos = GetPos();

	Move();
	Jump();

	vPos += m_pRigidbody->GetVelocity() * fDT;
	SetPos(vPos);


	m_fCurFireDelay += fDT;
	if (m_fCurFireDelay >= m_fFireDelay && m_fFireDelay && m_pEnemy != nullptr && !TimeMgr::GetInst()->GetIsPause()) {
		if (KEY_PRESS(KEY_TYPE::S))
		{
			Attack();
			m_fCurFireDelay = 0;
		}
	}

	POINT pRes = Core::GetInst()->GetResolution();

	if (vPos.x < 0 || vPos.y < 0 || vPos.x > pRes.x || vPos.y > pRes.y)
	{
		m_iHP = 0;
		m_bIsDie = true;
		ResultMgr::GetInst()->PlayerDied(1);
		EventMgr::GetInst()->DeleteObject(this);
	}

	if (m_pEnemy != nullptr)
	{
		Vec2 vDir = { m_pEnemy->GetPos().x - GetPos().x,
		m_pEnemy->GetPos().y - GetPos().y };
		vDir = vDir.Normalize();

		m_vecHandPos = vDir * m_fHandDis;
	}
}

void Player2::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vDir = { m_pEnemy->GetPos().x - GetPos().x,
		m_pEnemy->GetPos().y - GetPos().y };
	vDir = vDir.Normalize();

	Component_Render(_dc);

	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, m_pTex->GetWidth(), m_pTex->GetHeight(), m_pTex->GetDC()
		, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), RGB(255, 0, 255));

#pragma region hand
	HBITMAP hMemBtiamp = CreateCompatibleBitmap(m_pHandTex->GetDC(), m_pHandTex->GetWidth(), m_pHandTex->GetHeight());
	HDC hMemDc = CreateCompatibleDC(m_pHandTex->GetDC());
	SelectObject(hMemDc, hMemBtiamp);

	if (vDir.x > 0)
	{
		StretchBlt(hMemDc
			, 0
			, 0
			, m_pHandTex->GetWidth(), m_pHandTex->GetHeight(), m_pHandTex->GetDC()
			, 0, 0, m_pHandTex->GetWidth(), m_pHandTex->GetHeight(), SRCCOPY);
	}
	else
	{
		StretchBlt(hMemDc
			, m_pHandTex->GetWidth() - 1
			, 0
			, -m_pHandTex->GetWidth(), m_pHandTex->GetHeight(), m_pHandTex->GetDC()
			, 0, 0, m_pHandTex->GetWidth(), m_pHandTex->GetHeight(), SRCCOPY);
	}

	TransparentBlt(_dc, (int)(vPos.x - m_pHandTex->GetWidth() / 2) + vDir.x * m_fHandDis
		, (int)(vPos.y - m_pHandTex->GetHeight() / 2) + vDir.y * m_fHandDis
		, m_pHandTex->GetWidth()
		, m_pHandTex->GetHeight()
		, hMemDc
		, 0, 0
		, m_pHandTex->GetWidth()
		, m_pHandTex->GetHeight()
		, RGB(255, 0, 255));
#pragma endregion
}

void Player2::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player1_Bullet")
	{
		const Object* cBullet = _pOther->GetObj();
		Object* ncBullet = const_cast<Object*>(cBullet);
		EventMgr::GetInst()->DeleteObject(ncBullet);
		ResMgr::GetInst()->Play(L"Hit");
		m_iHP--;
		CameraMgr::GetInst()->CameraShake(10, 0.5f);
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
	vBulletPos += m_vecHandPos;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	//	pBullet->SetDir(M_PI / 4 * 7);
	//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(-10.f, -15.f));
	if (Vec2({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y }).Length() != 0)
		pBullet->SetDir({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y });
	pBullet->SetName(L"Player2_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET2);
	ResMgr::GetInst()->Play(L"Attack");
}

void Player2::Move()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	POINT checkedPoint = {};

#pragma region move
	if (KEY_PRESS(m_eLeftMoveKey) && m_bCanMoveLeft)
	{
		m_pRigidbody->SetHorizontalVelocity(-m_fPlayerSpeed);
	}
	else if (KEY_UP(m_eLeftMoveKey))
	{
		m_pRigidbody->SetHorizontalVelocity(0);
	}
	else if (KEY_PRESS(m_eRightMoveKey) && m_bCanMoveRight)
	{
		m_pRigidbody->SetHorizontalVelocity(m_fPlayerSpeed);
	}
	else if (KEY_UP(m_eRightMoveKey))
	{
		m_pRigidbody->SetHorizontalVelocity(0);
	}
#pragma endregion

#pragma region check ground, ceiling
	RECT groundCheckRect;
	RECT ceilingCheckRect;

	if (!m_pRigidbody->GetReverseGravity())
	{
		groundCheckRect = { (LONG)(vPos.x - vScale.x / 2 + 5), (LONG)(vPos.y),
							(LONG)(vPos.x + vScale.x / 2 - 5), (LONG)(vPos.y + vScale.y / 2) };
		ceilingCheckRect = { (LONG)(vPos.x - vScale.x / 2 + 5), (LONG)(vPos.y - vScale.y / 2),
							(LONG)(vPos.x + vScale.x / 2 - 5), (LONG)(vPos.y) };
	}
	else
	{
		groundCheckRect = { (LONG)(vPos.x - vScale.x / 2 + 5), (LONG)(vPos.y - vScale.y / 2),
							(LONG)(vPos.x + vScale.x / 2 - 5), (LONG)(vPos.y) };
		ceilingCheckRect = { (LONG)(vPos.x - vScale.x / 2 + 5), (LONG)(vPos.y),
							(LONG)(vPos.x + vScale.x / 2 - 5), (LONG)(vPos.y + vScale.y / 2) };
	}

	if (PixelCollision::GetInst()->CheckCollision(groundCheckRect.left, groundCheckRect.top,
		groundCheckRect.right, groundCheckRect.bottom, &checkedPoint))
	{
		m_pRigidbody->SetApplyGravity(false);
		m_pRigidbody->SetVerticalVelocity(0.f);
		m_iCurrentJumpCount = 0;
		m_bIsGround = true;
	}
	else
	{
		m_pRigidbody->SetApplyGravity(true);
		m_bIsGround = false;
	}

	if (PixelCollision::GetInst()->CheckCollision(ceilingCheckRect.left, ceilingCheckRect.top,
		ceilingCheckRect.right, ceilingCheckRect.bottom, &checkedPoint))
	{
		m_pRigidbody->SetVerticalVelocity(0.f);
	}

	m_pRigidbody->Update();
#pragma endregion

#pragma region check left move
	if (PixelCollision::GetInst()->CheckCollision(
		vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f + 5,
		vPos.x - vScale.x / 3.f, vPos.y + vScale.y / 2.f - 5, &checkedPoint))
	{
		m_bCanMoveLeft = false;
		m_pRigidbody->SetHorizontalVelocity(0);
	}
	else
	{
		m_bCanMoveLeft = true;
	}
#pragma endregion

#pragma region check right move
	if (PixelCollision::GetInst()->CheckCollision(
		vPos.x + vScale.x / 3.f, vPos.y - vScale.y / 2.f + 5,
		vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f - 5, &checkedPoint))
	{
		m_bCanMoveRight = false;
		m_pRigidbody->SetHorizontalVelocity(0);
	}
	else
	{
		m_bCanMoveRight = true;
	}
#pragma endregion
}

void Player2::Jump()
{
	float jumpPower = m_pRigidbody->GetReverseGravity() ?
		m_fJumpPower : -m_fJumpPower;

	if (KEY_DOWN(KEY_TYPE::W) && m_iCurrentJumpCount < m_iJumpCount && !TimeMgr::GetInst()->GetIsPause())
	{
		if (!m_bIsGround && m_iCurrentJumpCount == 0)
			m_iCurrentJumpCount++;
		m_iCurrentJumpCount++;

		m_pRigidbody->SetVerticalVelocity(jumpPower);
	}
}
