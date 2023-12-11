#pragma once
#include "Object.h"
class PausePanel :
    public Object
{
public:
    PausePanel();
    ~PausePanel();

public:
    void Update() override;
    void Render(HDC _dc) override;

private:
    Object* m_oContinueBtn;
    Object* m_oExitBtn;
};

