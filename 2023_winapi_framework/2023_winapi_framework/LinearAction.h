#pragma once
#include <functional>
class LinearAction
{
public:
	LinearAction(wstring _strName, std::function<void(float)> _pAction, float _fTime);
	~LinearAction();

public:
	bool DoAciton();

private:
	std::function<void(float)> m_pAction;
	float m_fTime;
	float m_fCurrentTime;
	wstring m_strName;
	friend class LinearActionMgr;
};