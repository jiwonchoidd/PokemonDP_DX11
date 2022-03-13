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
#include "KCombat.h"
class KScene_Combat : public KScene
{
public:
    KCombat    m_Combat;
    std::shared_ptr<KSpriteEffect> m_EffectPlayer;
    std::wstring                   m_text_dialog;
    std::shared_ptr<KUIModelComposite> m_Combat_Menu_0;
    std::shared_ptr<KUIModelComposite> m_Combat_Menu_1;
    bool       m_Event_Intro = false;
    bool       m_Event_Intro_End = false;
    bool       m_bMenu = false;
    bool       m_bGameEnd = false;
    bool       m_bAttack = false;
    bool       m_bAttack_End = false;
public:
    bool    Load(std::wstring file) override;
public:
    virtual bool	Init(ID3D11DeviceContext* context);
    virtual bool	Frame();
    virtual bool	Render();
    virtual bool	Release();
    void            ActiveSelect();
};