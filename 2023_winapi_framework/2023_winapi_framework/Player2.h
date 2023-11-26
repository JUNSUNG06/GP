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
    void Attack();
private:
    Texture* m_pTex;
    int m_iHP;
    float m_fPlayerSpeed;
    float m_fFireDelay;
    float m_fBulletSpeed;
};