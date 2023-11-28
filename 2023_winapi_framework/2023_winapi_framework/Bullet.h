#pragma once
#include "Object.h"
class Texture;
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();
public:
    void Update() override;
    void Render(HDC _dc) override;
    void SetDir(float _f) { m_fTheta = _f; }
    void SetDir(Vec2 _vDir = {1.f, 1.f})
    { 
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }
    void SetDamage(int _damage) { m_iDmg = _damage; }
    void SetSpeed(int _speed) { m_fSpeed = _speed; }
private:
//    float m_fDir; // �Ѿ� ����(-1 ��, 1 �Ʒ�);
    float m_fTheta; // �ﰢ�Լ� ����.
    Vec2 m_vDir;
    float m_fSpeed;
    int m_iDmg;
    Texture* m_pTex;
};

