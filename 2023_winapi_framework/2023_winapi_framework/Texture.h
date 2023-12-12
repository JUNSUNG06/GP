#pragma once
#include "Res.h"
class Texture :
    public Res
{
private:
    Texture();
    ~Texture();
    friend class ResMgr;
public:
    void Load(const wstring& _strFilePath);
    const LONG& GetWidth() const { return (m_bitInfo.bmWidth); }
    const LONG& GetHeight() const { return (m_bitInfo.bmHeight); }
    const HDC& GetDC() const { return m_hDC; }
    void Draw(HDC _dc, Vec2 _vPos, Vec2 _vScale);
    void DrawRotate(HDC _dc, Vec2 _vPos, Vec2 _vScale, float _fAngle);
    void SetAngle(float _fAngle) { m_fAngle = _fAngle; }
    float GetAngle() { return m_fAngle; }
private:
    HBITMAP m_hBit;
    HDC     m_hDC;
    BITMAP  m_bitInfo;
    float m_fAngle;
};

