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
private:
    Texture* m_pTex;
};

