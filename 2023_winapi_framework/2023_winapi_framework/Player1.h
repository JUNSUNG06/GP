#pragma once
#include "Object.h"
class Texture;
class Player1 :
    public Object
{
public:
    Player1();
    ~Player1();
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