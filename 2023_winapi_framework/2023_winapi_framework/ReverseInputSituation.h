#pragma once
#include "Situation.h"
class Player1;
class Player2;
class ReverseInputSituation
	: public Situation
{
public:
	ReverseInputSituation(SITUATION_TYPE _eSitutationType);
	~ReverseInputSituation();
public:
	virtual void StartSituation() override;
	virtual void UpdateSituation() override;
	virtual void EndSituation() override;

private:
	Player1* m_pPlayer1;
	Player2* m_pPlayer2;
};

