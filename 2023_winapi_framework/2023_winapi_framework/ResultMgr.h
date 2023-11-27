#pragma once
class Object;
class ResultMgr
{
	SINGLE(ResultMgr);
public:
	void ResetPoint();
	void PlayerDied(const Object* _pObj);
	int GetPlayer1Wins() { return m_iPlayer1Win; }
	int GetPlayer2Wins() { return m_iPlayer2Win; }
private:
	int m_iPlayer1Win;
	int m_iPlayer2Win;
	int m_iMaxPoint;
};