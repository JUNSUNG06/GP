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

private: 
	Player1* m_pPlayer1;
	Player2* m_pPlayer2;
};

