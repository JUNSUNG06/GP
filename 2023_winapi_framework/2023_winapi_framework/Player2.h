#pragma once
#include "Object.h"
class Texture;
class Player2 :
    public Object
{
public:
    Player2();
    ~Player2();
public:
    void Update() override;
    void Render(HDC _dc) override;
    void SetPlayerSpeed(float _speed) { m_fPlayerSpeed = _speed; }
    void SetFireDelay(float _delay) { m_fFireDelay = _delay; }
    void Attack();
    //
    void SetEnemy(Object* _obj) { m_pEnemy = _obj; }
    //
private:
    Texture* m_pTex;
    int m_iHP;
    float m_fPlayerSpeed;
    float m_fFireDelay;
    float m_fCurFireDelay;
    float m_fBulletSpeed;
    //
    Object* m_pEnemy;
    //
};