#pragma once
#include "KPlayer2D.h"
#include "KPokemon.h"
class KCombat
{
public:
    ID3D11DeviceContext* m_pContext;
    KPlayer2D*          m_pPlayer; // ���ϸ�, �κ��丮 
    std::shared_ptr<KPokemon> m_mypoke; // �� ���ϸ�
    std::shared_ptr<KPokemon> m_enemypoke; // �� ���ϸ�
public:
    bool Init(ID3D11DeviceContext* context, KPlayer2D* player,int id= -1);
    bool Frame();
    bool Render(ID3D11DeviceContext* pContext);
    bool Release();
    virtual void	ObjectOverlap(KCollider* pObj, DWORD dwState);
public:
    KCombat();
    ~KCombat();
};

