#pragma once
#include "Scene.h"
class Explanation_Scene :
    public Scene
{
public:
    void Init() override;
    void Render(HDC _dc) override;
    void Release() override;
};

