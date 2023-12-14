#pragma once
#include "define.h"
#include "Player1.h"
#include "Player2.h"

class GameMgr
{
	SINGLE(GameMgr);

public:
	void SetPlayer1(Player1* _pPlayer) { m_pPlayer1 = _pPlayer; }
	void SetPlayer2(Player2* _pPlayer) { m_pPlayer2 = _pPlayer; }
	Player1* GetPlayer1() { return m_pPlayer1; }
	Player2* GetPlayer2() { return m_pPlayer2; }
	void SetPlayer1Died(bool _bValue) { m_bPlayer1Died = _bValue; }
	void SetPlayer2Died(bool _bValue) { m_bPlayer2Died = _bValue; }
	bool GetPlayer1Died() { return m_bPlayer1Died; }
	bool GetPlayer2Died() { return m_bPlayer2Died; }
	void Init();
	void Update();
	void Render(HDC _dc);
	void StartGame();
	void EndGame();

private: 
	Player1* m_pPlayer1;
	Player2* m_pPlayer2;
	bool m_bPlayer1Died;
	bool m_bPlayer2Died;
	bool m_bIsPlay;
	float m_fCurrentPlayTime;
};

