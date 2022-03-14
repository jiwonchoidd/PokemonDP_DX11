#pragma once
#include "KScene.h"
#include "KSoundManager.h"
class KScene_Intro : public KScene
{
public:
    bool    m_bStart = false;
public:
    bool    Load(std::wstring file) override;
public:
    virtual bool	Init(ID3D11DeviceContext* context);
    virtual bool	Frame();
    virtual bool	Render();
    virtual bool	Release();
};

