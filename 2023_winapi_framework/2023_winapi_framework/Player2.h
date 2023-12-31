#pragma once
#include "Object.h"
class Texture;
class Rigidbody;
class Collider;
class Player2 :
    public Object
{
public:
    Player2();
    ~Player2();
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther)  override;
    virtual void StayCollision(Collider* _pOther)  override;
    void CheckCanMove();
public:
    void SetPlayerHP(int _hp) { m_iHP = _hp; }
    int GetPlayerHP() { return m_iHP; } // �߰��Ѱ�
    void SetPlayerSpeed(float _speed) { m_fMaxPlayerSpeed = _speed; }
    float GetPlayerSPeed() { return m_fMaxPlayerSpeed; }
    void SetFireDelay(float _delay) { m_fFireDelay = _delay; }
    void SetJumpPower(float _fValue) { m_fJumpPower = _fValue; }
    void SetMoveKey(KEY_TYPE rightKey, KEY_TYPE leftKey)
    {
        m_eRightMoveKey = rightKey;
        m_eLeftMoveKey = leftKey;
    }
    void SetJumpKey(KEY_TYPE key) { m_eJumpKey = key; }
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
    float m_fMaxPlayerSpeed;
    float m_fCurrentPlayerSpeed;
    float m_fAcceleration;
    float m_fDeceleration;
    int m_iMoveDir;
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
    KEY_TYPE m_eJumpKey;
};