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
#include "Texture.h"
#include "Core.h"
#include "CameraMgr.h"

Player1::Player1()
	: m_pTex(nullptr)
	, m_iHP(5)
	, m_bIsDie(false)
	, m_fPlayerSpeed(500.f)
	, m_fFireDelay(1.f)
	, m_fCurFireDelay(3.f)
	, m_fBulletSpeed(3.f)
	, m_pEnemy(nullptr)
	, m_fJumpPower(250.f)
	, m_bIsGround(false)
	, m_bCanMoveLeft(true)
	, m_bCanMoveRight(true)
	, m_iJumpCount(2)
	, m_iCurrentJumpCount(0)
{
	m_pHandTex = ResMgr::GetInst()->TexLoad(L"Player1_Hand", L"Texture\\Player1_Hand.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
	m_pRigidbody = new Rigidbody(this);
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player1", L"Texture\\Player1.bmp");
	SetMoveKey(KEY_TYPE::RIGHT, KEY_TYPE::LEFT);
	m_fHandDis = 45.f;
}

Player1::~Player1()
{
	if (m_pRigidbody != nullptr)
		delete m_pRigidbody;
}

void Player1::Update()
{
	Vec2 vPos = GetPos();

	CheckCanMove();
	Move();
	Jump();

	vPos += m_pRigidbody->GetVelocity() * fDT;
	SetPos(vPos);

	m_fCurFireDelay += fDT;
	if (m_fCurFireDelay >= m_fFireDelay && m_pEnemy != nullptr) {
		if (KEY_PRESS(KEY_TYPE::DOWN))
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

void Player1::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vDir = { m_pEnemy->GetPos().x - GetPos().x,
		m_pEnemy->GetPos().y - GetPos().y };
	vDir = vDir.Normalize();

	//Component_Render(_dc);

	m_pTex->Draw(_dc, GetPos(), GetScale());
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

	TransparentBlt(_dc
		, (int)(vPos.x - m_pHandTex->GetWidth() / 2) + m_vecHandPos.x
		, (int)(vPos.y - m_pHandTex->GetHeight() / 2) + m_vecHandPos.y
		, m_pHandTex->GetWidth()
		, m_pHandTex->GetHeight()
		, hMemDc
		, 0, 0
		, m_pHandTex->GetWidth()
		, m_pHandTex->GetHeight()
		, RGB(255, 0, 255));

	DeleteObject(hMemBtiamp);
	DeleteDC(hMemDc);
#pragma endregion
}

void Player1::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player2_Bullet")
	{
		ResMgr::GetInst()->Play(L"Hit");
		m_iHP--;
		CameraMgr::GetInst()->CameraShake(10, 0.5f);
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
	vBulletPos += m_vecHandPos;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	//	pBullet->SetDir(M_PI / 4 * 7);
	//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(-10.f, -15.f));
	if (Vec2({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y }).Length() != 0)
		pBullet->SetDir({ m_pEnemy->GetPos().x - GetPos().x, m_pEnemy->GetPos().y - GetPos().y });
	pBullet->SetName(L"Player1_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
	ResMgr::GetInst()->Play(L"Attack");
}

void Player1::CheckCanMove()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	POINT checkedPoint = {};

#pragma region check ground
	RECT groundCheckRect;
	RECT ceilingCheckRect;

	m_bBeforeGround = m_bIsGround;
	m_bBeforeCeiling = m_bIsCeiling;

	//set check rect
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

	//check ceiling 
	if (PixelCollision::GetInst()->CheckCollision(ceilingCheckRect.left, ceilingCheckRect.top,
		ceilingCheckRect.right, ceilingCheckRect.bottom, &checkedPoint))
	{
		m_bIsCeiling = true;
	}
	else
	{
		m_bIsCeiling = false;
	}

	//check ground
	if (PixelCollision::GetInst()->CheckCollision(groundCheckRect.left, groundCheckRect.top,
		groundCheckRect.right, groundCheckRect.bottom, &checkedPoint))
	{
		m_pRigidbody->SetApplyGravity(false);
		m_iCurrentJumpCount = 0;
		m_bIsGround = true;
	}
	else
	{
		m_pRigidbody->SetApplyGravity(true);
		m_bIsGround = false;
	}

	//set vertical velocity
	if ((m_bIsGround && !m_bBeforeGround) || (m_bIsCeiling && !m_bBeforeCeiling))
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
		//block move
		m_bCanMoveLeft = false;
		m_pRigidbody->SetHorizontalVelocity(0);
	}
	else
	{
		//enable move
		m_bCanMoveLeft = true;
	}
#pragma endregion

#pragma region check right move
	if (PixelCollision::GetInst()->CheckCollision(
		vPos.x + vScale.x / 3.f, vPos.y - vScale.y / 2.f + 5,
		vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f - 5, &checkedPoint))
	{
		//block move
		m_bCanMoveRight = false;
		m_pRigidbody->SetHorizontalVelocity(0);
	}
	else
	{
		//enable move
		m_bCanMoveRight = true;
	}
#pragma endregion
}

void Player1::Move()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	POINT checkedPoint = {};

	//set velocity
	if (KEY_PRESS(m_eLeftMoveKey) && m_bCanMoveLeft)
	{
		m_pRigidbody->SetHorizontalVelocity(-m_fPlayerSpeed);
	}
	else if (KEY_UP(m_eLeftMoveKey))
	{
		m_pRigidbody->SetHorizontalVelocity(0);
	}

	if (KEY_PRESS(m_eRightMoveKey) && m_bCanMoveRight)
	{
		m_pRigidbody->SetHorizontalVelocity(m_fPlayerSpeed);
	}
	else if (KEY_UP(m_eRightMoveKey))
	{
		m_pRigidbody->SetHorizontalVelocity(0);
	}
}

void Player1::Jump()
{
	//set jump power
	float jumpPower = m_pRigidbody->GetReverseGravity() ?
		m_fJumpPower : -m_fJumpPower;

	//jump
	if (KEY_DOWN(KEY_TYPE::UP) && m_iCurrentJumpCount < m_iJumpCount)
	{
		m_iCurrentJumpCount++;
		if (!m_bIsGround && !m_bIsCeiling && m_iCurrentJumpCount == 0)
			m_iCurrentJumpCount++;

		m_pRigidbody->SetVerticalVelocity(jumpPower);
	}
}