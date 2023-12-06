#include "pch.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "Core.h"

void CameraMgr::Init()
{
	m_fCurTime = 0;
	m_fTime = 0;
	m_fCurPower = 0;
	m_fPower = 0;
	m_bIsShaking = false;
}

void CameraMgr::Update()
{
	if (m_bIsShaking)
		if (m_fCurTime < m_fTime) { // 타임동안 줄어드는 파워로 되는거
			m_fCurTime += fDT;
			m_fCurPower = (m_fTime - m_fCurTime) / m_fTime * m_fPower;
		}
		else {
			m_bIsShaking = false;
		}
}

void CameraMgr::CameraShake(float power, float time)
{
	m_bIsShaking = true;
	m_fPower = power;
	m_fCurPower = power;
	m_fTime = time;
	m_fCurTime = 0;
}