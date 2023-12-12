#pragma once
#include "Object.h"
class TagMgr
{
	SINGLE(TagMgr);

public:
	void ChooseRandomTagger();
	void ChangeTagger(Object* _caughtPlayer);
	Object* GetTagger() { return m_ptTagger; }
private:
	Object* m_ptTagger;
};

