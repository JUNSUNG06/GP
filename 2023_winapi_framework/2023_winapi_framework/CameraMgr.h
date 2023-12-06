#pragma once
class CameraMgr
{
	SINGLE(CameraMgr);
public:
	void Init();
	void Update();
public:
	void CameraShake(float power, float time);
	bool GetIsCameraShaking() { return m_bIsShaking; }
	float GetShakePower() { return m_fCurPower; }

public: // private
	float m_fCurTime;
	float m_fTime;
	float m_fCurPower;
	float m_fPower;
	bool m_bIsShaking;
};

