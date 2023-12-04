#pragma once
#include "Situation.h"
class RotateMapSituation
	: public Situation
{
public:
	RotateMapSituation(SITUATION_TYPE _eSitutationType);
	~RotateMapSituation();

public:
	virtual void StartSituation() override;
	virtual void UpdateSituation() override;
	virtual void EndSituation() override;

private:
	float m_fRotateSpeed;
};

