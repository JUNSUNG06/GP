#pragma once
#include "Object.h"
class Texture;
class Rigidbody;
class Collider;
class Player1 :
    public Object
{
public:
    Player1();
    ~Player1();
public:
    void Update() override;
    void Render(HDC _dc) override;
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther)  override;
    virtual void StayCollision(Collider* _pOther)  override;
    void CheckCanMove();
public:
    void SetPlayerHP(int _hp) { m_iHP = _hp; }
    int GetPlayerHP() { return m_iHP; } // �߰��Ѱ�
    void SetPlayerSpeed(float _speed) { m_fPlayerSpeed = _speed; }
    void SetFireDelay(float _delay) { m_fFireDelay = _delay; }
    void SetJumpPower(float _fValue) { m_fJumpPower = _fValue; }
    void SetMoveKey(KEY_TYPE rightKey, KEY_TYPE leftKey)
    {
        m_eRightMoveKey = rightKey;
        m_eLeftMoveKey = leftKey;
    }
    void Attack();
    void Move();
    void Jump();
    Rigidbody* GetRigidbody() { return m_pRigidbody; }
    //
    void SetEnemy(Object* _obj) { m_pEnemy = _obj; }
    //
private:
    Texture* m_pTex;
    Texture* m_pHandTex;
    int m_iHP;
    bool m_bIsDie;
    float m_fPlayerSpeed;
    float m_fFireDelay;
    float m_fCurFireDelay;
    float m_fBulletSpeed;
    float m_fJumpPower;
    int m_iJumpCount;
    int m_iCurrentJumpCount;
    float m_fHandDis;
    bool m_bIsGround;
    bool m_bBeforeGround;
    bool m_bIsCeiling;
    bool m_bBeforeCeiling;
    bool m_bCanMoveRight;
    bool m_bCanMoveLeft;
    Vec2 m_vecHandPos;
    //
    Object* m_pEnemy;
    //
    Rigidbody* m_pRigidbody;

    KEY_TYPE m_eRightMoveKey;
    KEY_TYPE m_eLeftMoveKey;
};