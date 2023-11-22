#include "pch.h"
#include "Rigidbody.h"
#include "TimeMgr.h"

Rigidbody::Rigidbody(Object* _pOwner)
	: m_pOwner(nullptr)
	, m_fGravityScale(-9.81f)
	, m_fBounciness(0)
	, m_bUseGravity(true)
	, m_bReverseGravity(false)
	, m_vecVelocity({0, 0})
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::FinalUpdate()
{
	if (m_bUseGravity == true)
	{
		m_vecVelocity.y += m_fGravityScale * fDT;
	}
}

void Rigidbody::SetReverseGravity(bool _bReverseGravity)
{
	m_bReverseGravity = _bReverseGravity;

	m_fGravityScale = abs(m_fGravityScale);

	if (m_bReverseGravity == false)
		m_fGravityScale *= -1;
}
