#pragma once
class Object;
class Texture;

class TagMgr
{
	SINGLE(TagMgr);

public:
	void Init();
	void Render(HDC _dc);
	void ChooseRandomTagger();
	void ChangeTaggerToPlayer1();
	void ChangeTaggerToPlayer2();
	Object* GetTagger() { return m_ptTagger; }

private:
	Object* m_ptTagger;
	Texture* m_pTagArrow;
};

