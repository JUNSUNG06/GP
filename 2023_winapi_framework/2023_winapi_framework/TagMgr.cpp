#include "pch.h"
#include "TagMgr.h"
#include "GameMgr.h"
#include <ctime>

void TagMgr::ChooseRandomTagger()
{
	srand((unsigned int)time(NULL));
	if (rand() % 2 == 0) {
		m_ptTagger = GameMgr::GetInst()->GetPlayer1();
	}
	else {
		m_ptTagger = GameMgr::GetInst()->GetPlayer2();
	}
}

void TagMgr::ChangeTagger(Object* _caughtPlayer)
{
	m_ptTagger = _caughtPlayer;
}
