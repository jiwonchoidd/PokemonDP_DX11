#pragma once
#include "KScene.h"
#include "KPlayer2D.h"
#include "KUI.h"
#include "KMapSpace.h"
#include "KCamera.h"
#include "KObjObject.h"
#include "KState.h"
#include "KSoundManager.h"
#include "KSpriteEffect.h"
class KScene_Combat : public KScene
{
public:
    std::shared_ptr<KSpriteEffect> m_EffectPlayer;
    std::wstring                   m_text_dialog;
public:
    bool    Load(std::wstring file) override;
public:
    virtual bool	Init(ID3D11DeviceContext* context);
    virtual bool	Frame();
    virtual bool	Render();
    virtual bool	Release();
};