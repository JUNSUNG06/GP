#pragma once
#include "Object.h"
class TeleportObject :
    public Object
{
public:
    TeleportObject();
    ~TeleportObject();
public:
    void Render(HDC _dc) override;
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther)  override;
    virtual void StayCollision(Collider* _pOther)  override;
public:
    void SetOtherTelpo(TeleportObject* _otherObj) { m_ptrOtherTelpo = _otherObj; }
    bool GetIsEntry() { return m_bIsEntryPoint; }
    bool CheckIsOnWall();
private:
    void Teleporting(Object* _obj);
private:
    TeleportObject* m_ptrOtherTelpo;
    bool m_bIsEntryPoint;
};

