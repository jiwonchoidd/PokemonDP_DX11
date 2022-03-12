#pragma once
#include "K2DAsset.h"
class KTriggerCollider : public K2DAsset
{
public:
    bool        m_bisTrigger = false;
public:
    bool Init(ID3D11DeviceContext* context, KVector2 pos, RECT Size);
    bool Frame()override;
    bool Render(ID3D11DeviceContext* pContext)override;
    virtual void	ObjectOverlap(KCollider* pObj, DWORD dwState);
    virtual void	SelectOverlap(KCollider* pObj, DWORD dwState);
};

