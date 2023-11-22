#pragma once
#include "Object.h"
class Enemy :
    public Object
{
public:
    Enemy();
    ~Enemy();
private:
    void Update() override;
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther)  override;
    virtual void StayCollision(Collider* _pOther)  override;
private:
    bool m_bIsJumper;
    float m_fSpeed;
    float m_fDir;
};

