#include "pch.h"
#include "Enemy.h"
#include "TimeMgr.h"
#include "Collider.h"

Enemy::Enemy()
	: m_bIsJumper(false)
	, m_fSpeed(100.f)
	, m_fDir(1.f)
{
	CreateCollider();
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Vec2 vCurPos = GetPos();
	vCurPos.x += m_fSpeed * fDT * m_fDir;

	SetPos(vCurPos);
}

void Enemy::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Wall") // 벽 만나면 방향 바꾸기
	{
		m_fDir *= -1;
	}
}

void Enemy::ExitCollision(Collider* _pOther)
{
}

void Enemy::StayCollision(Collider* _pOther)
{
}
