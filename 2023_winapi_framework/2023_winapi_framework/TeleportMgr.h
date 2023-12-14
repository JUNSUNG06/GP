#pragma once
#include "TeleportObject.h"
class TeleportMgr
{
	SINGLE(TeleportMgr);
public:
	void Init();
	void Update();
public:
	void StartSetup() { m_fCurTime = 0; m_bIsSpawned = false; }
	void SetMaxHoldingTime(float _time) { m_fMaxHoldingTime = _time; }
	void SetRegenTime(float _time) { m_fRegenTime = _time; }
	void RemovePortals();
	void SetPortals();
	void ResetCurrentTime() { m_fCurTime = 0; }

	float getcurtime() { return m_fCurTime; }
private:
	float m_fCurTime;
	float m_fMaxHoldingTime; // 포탈을 타지 않을 때 사라지는 시간
	float m_fRegenTime; // 포탈이 사라지고 다시 나올 시간
	bool m_bIsSpawned;
	TeleportObject* m_ptrTpPoint1;
	TeleportObject* m_ptrTpPoint2;
};

