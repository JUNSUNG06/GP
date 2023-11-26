#pragma once
#include <unordered_map>
class Situation;

class SituationMgr
{
	SINGLE(SituationMgr)

public:
	void Init();
	void Udpate();
	void Release();
	void ChangeSituation(SITUATION_TYPE _situationType);

public:
	Situation* GetCurrentSituation() { return m_pCurrentSituation; }
	void RegistSituation(SITUATION_TYPE _type, Situation* _situation) 
	{ m_umSituationMap.insert({ _type, _situation }); }

private: 
	std::unordered_map<SITUATION_TYPE, Situation*> m_umSituationMap;
	Situation* m_pCurrentSituation;	
};

