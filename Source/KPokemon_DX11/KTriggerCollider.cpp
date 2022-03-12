#include "KTriggerCollider.h"
#include "KState.h"
bool KTriggerCollider::Init(ID3D11DeviceContext* context, KVector2 pos, RECT Size)
{
    m_cbData.vLightDir = {1.0f,1.0f,1.0f,1.0f};
    SetRectDraw(Size);
    SetPosition(pos);
    m_pContext = context;
    CreateObject_Mask(L"../../data/shader/VS_2D_Map.txt", L"../../data/shader/PS_2D_Map.txt",
        L"../../data/texture/menu_close.png", L"");
    SetCollisionType(KCollisionType::Overlap, KSelectType::Select_Ignore);
    m_bisTrigger = false;
    m_bVisibility = false;
    return true;
}

bool KTriggerCollider::Frame()
{
    if (g_InputData.bDebugRender)
    {
        m_bVisibility = !m_bVisibility;
    }
    return true;
}

bool KTriggerCollider::Render(ID3D11DeviceContext* pContext)
{
    ApplyDSS(pContext, KState::g_pDSS_Disabled);
    KObject::Render(pContext);
    ApplyDSS(pContext, KState::g_pDSS);
    return true;
}

void KTriggerCollider::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
    if(pObj->m_Name == L"Player0")
    m_bisTrigger = true;
}

void KTriggerCollider::SelectOverlap(KCollider* pObj, DWORD dwState)
{
}
