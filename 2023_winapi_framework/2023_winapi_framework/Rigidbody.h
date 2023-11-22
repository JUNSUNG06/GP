#pragma once
class Object;

class Rigidbody
{
public:
	Rigidbody(Object* _pOwner);
	~Rigidbody();

public:
	Object* GetOwner() { return m_pOwner; }
	float GetGravity() { return m_fGravity; }
	void SetGravity(float _fGravity) { m_fGravity = _fGravity; }
	void SetUserGravity(bool _bValue) { m_bUseGravity = _bValue; }
	float GetBounciness() { return m_fBounciness; }
	void SetBounciness(float _fBounciness) { m_fBounciness = _fBounciness; }
	Vec2 GetVelocity() { return m_vecVelocity; }
	Vec2 GetVelocity() { return m_vecVelocity; }
private:
	Object* m_pOwner;
	float m_fGravity;
	bool m_bUseGravity;
	float m_fBounciness;
	Vec2 m_vecVelocity;
};

