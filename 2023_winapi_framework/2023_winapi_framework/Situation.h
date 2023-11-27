#pragma once
class Situation
{
public:
	Situation(SITUATION_TYPE _eSituationType);
	~Situation();

public:
	virtual void StartSituation() = 0;
	virtual void UpdateSituation() = 0;
	virtual void EndSituation() = 0;

public:
	SITUATION_TYPE GetSituationType() { return m_eSituationType; }

protected:
	SITUATION_TYPE m_eSituationType;
};

