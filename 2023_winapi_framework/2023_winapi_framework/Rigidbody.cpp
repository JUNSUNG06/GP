#include "pch.h"
#include "Rigidbody.h"
#include "TimeMgr.h"

Rigidbody::Rigidbody(Object* _pOwner)
	: m_pOwner(nullptr)
	, m_fGravityScale(650.f)
	, m_fBounciness(0)
	, m_bUseGravity(true)
	, m_bApplyGravity(true)
	, m_bReverseGravity(false)
	, m_vecVelocity({0, 0})
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{
	//중력 계산
	if (m_bUseGravity == true && m_bApplyGravity == true)
	{
		m_vecVelocity.y += m_fGravityScale * fDT;
	}
}

//중력 반전
void Rigidbody::ReverseGravity(bool _bReverseGravity)
{
	m_bReverseGravity = _bReverseGravity;

	m_fGravityScale = abs(m_fGravityScale);

	if (m_bReverseGravity == true)
		m_fGravityScale *= -1;
}

void Rigidbody::AddForce(Vec2 force)
{
	m_vecVelocity += force;
}
