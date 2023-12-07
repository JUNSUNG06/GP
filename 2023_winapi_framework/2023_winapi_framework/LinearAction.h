#pragma once
class LinearAction
{
public:
	LinearAction(wstring _strName, void(*_pAction)(float _fTime), float _fTime);
	~LinearAction();

public:
	bool DoAciton();

private:
	void (*m_pAction)(float _fTime);
	float m_fTime;
	float m_fCurrentTime;
	wstring m_strName;
	friend class LinearActionMgr;
};