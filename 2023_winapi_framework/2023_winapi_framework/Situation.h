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
	float GetDuration() { return m_fDuration; }

public:
	SITUATION_TYPE GetSituationType() { return m_eSituationType; }
	wstring GetDescription() { return m_sDescription; }

protected:
	SITUATION_TYPE m_eSituationType;
	float m_fDuration;
	wstring m_sDescription;
};

