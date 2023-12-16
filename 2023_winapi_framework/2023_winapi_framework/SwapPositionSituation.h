#pragma once
#include "Situation.h"
class Player1;
class Player2;
class SwapPositionSituation
	: public Situation
{
public:
	SwapPositionSituation(SITUATION_TYPE _eSitutationType);
	~SwapPositionSituation();
public:
	virtual void StartSituation() override;
	virtual void UpdateSituation() override;
	virtual void EndSituation() override;

	void SwapPos();

private:
	Player1* m_pPlayer1;
	Player2* m_pPlayer2;
	float m_fCurrentTime;
	bool m_bSwapped;
};

