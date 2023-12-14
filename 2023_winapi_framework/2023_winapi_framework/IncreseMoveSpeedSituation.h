#pragma once
#include "Situation.h"
class Player1;
class Player2;

class IncreseMoveSpeedSituation
	: public Situation
{
public:
	IncreseMoveSpeedSituation(SITUATION_TYPE _eSitutationType);
	~IncreseMoveSpeedSituation();
public:
	virtual void StartSituation() override;
	virtual void UpdateSituation() override;
	virtual void EndSituation() override;
private:
	Player1* m_pPlayer1;
	Player2* m_pPlayer2;
	float m_fBeforePlayer1;
	float m_fBeforePlayer2;
};