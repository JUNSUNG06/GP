#pragma once
#include <functional>
class LinearAction;

class LinearActionMgr
{
	SINGLE(LinearActionMgr);

public:
	void Init();
	void Update();
	void Release();

public:
	void CreateLinearAction(wstring _strName, std::function<void(float)> _pAction, float _fTime);
	void RemoveLinerAction(wstring _strName);

private:
	map<wstring, LinearAction*> m_mLienrActions;
	vector<wstring> m_vecClearVec;
};

