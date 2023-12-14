#pragma once
#include "TeleportObject.h"
class TeleportMgr
{
	SINGLE(TeleportMgr);
public:
	void Init();
	void Update();
public:
	void SetMaxHoldingTime(float _time) { m_fMaxHoldingTime = _time; }
	void SetRegenTime(float _time) { m_fRegenTime = _time; }
	void RemovePortals();
	void SetPortals();
private:
	float m_fCurTime;
	float m_fMaxHoldingTime; // ��Ż�� Ÿ�� ���� �� ������� �ð�
	float m_fRegenTime; // ��Ż�� ������� �ٽ� ���� �ð�
	bool m_bIsSpawned;
	TeleportObject* m_ptrTpPoint1;
	TeleportObject* m_ptrTpPoint2;
};
