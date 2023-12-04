#pragma once
#include <unordered_map>
class Situation;

class SituationMgr
{
private:						
	SituationMgr() = default;
	~SituationMgr() = default;
public:							
	static SituationMgr* GetInst()
	{							
		static SituationMgr m_pInst;
		return &m_pInst;		
	}

public:
	void Init();
	void Udpate();
	void Release();
	void SetSituation(SITUATION_TYPE _situationType);
	void StartSituation();
	void EndSituation();

public:
	Situation* GetCurrentSituation() { return m_pCurrentSituation; }
	void RegistSituation(SITUATION_TYPE _type, Situation* _situation) 
	{ m_umSituationMap.insert({ _type, _situation }); }

private: 
	std::unordered_map<SITUATION_TYPE, Situation*> m_umSituationMap;
	Situation* m_pCurrentSituation;	
	float m_fCurrentSituationTime;
};

