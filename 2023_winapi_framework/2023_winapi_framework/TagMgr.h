#pragma once
#include "Object.h"
class TagMgr
{
	SINGLE(TagMgr);

public:
	void ChooseRandomTagger();
	void ChangeTaggerToPlayer1();
	void ChangeTaggerToPlayer2();
	Object* GetTagger() { return m_ptTagger; }

private:
	Object* m_ptTagger;
};

