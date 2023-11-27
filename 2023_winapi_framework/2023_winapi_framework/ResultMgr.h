#pragma once
class Object;
class ResultMgr
{
	SINGLE(ResultMgr)
public:
	void Init();
	void Update();
public:
	void ResetPoint();
	void PlayerDied(int _iPlayeridx);
	int GetPlayer1Wins() { return m_iPlayer1Win; }
	int GetPlayer2Wins() { return m_iPlayer2Win; }
private:
	int m_iPlayer1Win;
	int m_iPlayer2Win;
	int m_iMaxPoint;
	float m_fCurTime;
	bool m_bIsGameEnded;
};