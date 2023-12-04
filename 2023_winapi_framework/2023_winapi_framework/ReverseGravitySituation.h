#pragma once
#include "Situation.h"
class Rigidbody;
class ReverseGravitySituation
	: public Situation
{
public:
	ReverseGravitySituation(SITUATION_TYPE _eSitutationType);
	~ReverseGravitySituation();
public:
	virtual void StartSituation() override;
	virtual void UpdateSituation() override;
	virtual void EndSituation() override;

private:
	Rigidbody* m_pPlayer1Rigidbody;
	Rigidbody* m_pPlayer2Rigidbody;
};