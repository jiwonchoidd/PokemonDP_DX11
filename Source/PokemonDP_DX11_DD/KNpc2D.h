#pragma once
#include "K2DAsset.h"
class KNpc2D : public K2DAsset
{
public:
    bool Init(ID3D11DeviceContext* context, std::wstring vs, std::wstring ps,
        std::wstring tex = nullptr, std::wstring mask = nullptr);
    bool Frame()override;
    virtual void	ObjectOverlap(KCollider* pObj, DWORD dwState);
    virtual void	SelectOverlap(KCollider* pObj, DWORD dwState);
public:
    KNpc2D();
    ~KNpc2D();
};

