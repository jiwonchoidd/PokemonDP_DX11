#pragma once
#include "KScene.h"
#include "KPlayer2D.h"
#include "KUI.h"
#include "KMapSpace.h"
#include "KCamera.h"
#include "KObjObject.h"
#include "KState.h"
#include "KSoundManager.h"
#include "KTriggerCollider.h"
class KScene_Game_1 : public KScene
{
public:
    KCamera                 m_Camera;
    KTriggerCollider*       m_Trigger_Home;
    KTriggerCollider*       m_Trigger_Combat;
    bool                    m_bCombat=false;
    KUIModel*               m_Fade;

public:
    std::shared_ptr<KUIModelComposite> m_Menu;
    bool                               m_bMenu = false;
    void                               ActiveMenu();
public:
    bool    Load(std::wstring file) override;
public:
    virtual bool	Init(ID3D11DeviceContext* context);
    virtual bool	Frame();
    virtual bool	Render();
    virtual bool	Release();
};
