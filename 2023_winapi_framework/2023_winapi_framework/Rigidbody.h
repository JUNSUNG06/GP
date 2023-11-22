#pragma once
class Object;

class Rigidbody
{
public:
	Rigidbody(Object* _pOwner);
	~Rigidbody();

public:
	void FinalUpdate();
public:
	Object* GetOwner() { return m_pOwner; }
	float GetGravityScale() { return m_fGravityScale; }
	void SetGravityScale(float _fGravity) { m_fGravityScale = _fGravity; }
	bool GetUseGravity() { return m_bUseGravity; }
	void SetUseGravity(bool _bValue) { m_bUseGravity = _bValue; }
	float GetBounciness() { return m_fBounciness; }
	void SetBounciness(float _fBounciness) { m_fBounciness = _fBounciness; }
	Vec2 GetVelocity() { return m_vecVelocity; }
	void SetVelocity(Vec2 _vecVelocity) { m_vecVelocity = _vecVelocity; }
	bool GetReverseGravity() { return m_bReverseGravity; }
	void SetReverseGravity(bool _bReverseGravity);
private:
	Object* m_pOwner;
	float m_fGravityScale;
	float m_fBounciness;
	bool m_bUseGravity;
	bool m_bReverseGravity;
	Vec2 m_vecVelocity;
};