#pragma once
#include "K2DAsset.h"
#include "KQuadTree.h"
#include "KCamera.h"
#include "KPlayer2D.h"
class KMapSpace : public KQuadTree
{
public:
    KCollider* m_Player;
    bool       m_bDebugRender=false;
public:
    bool Init(ID3D11DeviceContext* context, KVector2 offset, float width, float height);
    bool Frame();
    bool Render(ID3D11DeviceContext* context);
    void ObjectOverlap(KCollider* pObj, DWORD dwState);
    void HitOverlap(KCollider* pObj, DWORD dwState);
public:
    KMapSpace();
    ~KMapSpace();
};

