#pragma once
class LinearAction;

class LinearActionMgr
{
	SINGLE(LinearActionMgr);

public:
	void Init();
	void Update();
	void Release();

public:
	void CreateLinearAction(wstring _strName, void (*_pAction)(float _fTime), float _fTime);
	void RemoveLinerAction(wstring _strName);

private:
	map<wstring, LinearAction*> m_mLienrActions;
	vector<wstring> m_vecClearVec;
};

