#include "pch.h"
#include "TagMgr.h"
#include "GameMgr.h"
#include "ResMgr.h"
#include "Object.h"
#include "Texture.h"
#include "CameraMgr.h"
#include <ctime>

void TagMgr::Init()
{
	m_pTagArrow = ResMgr::GetInst()->TexLoad(L"TagArrow", L"Texture\\TaggerArrow.bmp");
}

void TagMgr::Render(HDC _dc)
{
	if (m_ptTagger && m_pTagArrow)
	{
		Vec2 vPos = Vec2({ m_ptTagger->GetPos().x,
			m_ptTagger->GetPos().y - m_ptTagger->GetScale().y / 2.f - 6.5f - 5.5f});
		Vec2 vScale = Vec2({ 15, 15 });

		m_pTagArrow->Draw(_dc, vPos, vScale);
	}
}

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

void TagMgr::ChangeTaggerToPlayer1()
{
	m_ptTagger = GameMgr::GetInst()->GetPlayer1();
	CameraMgr::GetInst()->CameraShake(8, 0.5f);
}

void TagMgr::ChangeTaggerToPlayer2()
{
	m_ptTagger = GameMgr::GetInst()->GetPlayer2();
	CameraMgr::GetInst()->CameraShake(8, 0.5f);
}
