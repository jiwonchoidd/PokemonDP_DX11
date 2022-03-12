#pragma once
#include "KPlayer2D.h"
#include "KUI.h"
//포켓몬 정보를 받아와서 
//포켓몬 오브젝트를 만드는 클래스

// mon_rect;
// mon_level; //레벨
// mon_height;//키
// mon_weight;//몸무게
// type; //타입
// sex; //성별
// skill;

class KPokemon :public KImage
{
public:
    PokemonInfo* m_pinfo;
public:
    bool Init(ID3D11DeviceContext* context, PokemonInfo* info, bool ismine=false);
    bool Frame();
    bool Render(ID3D11DeviceContext* pContext);
    virtual void	ObjectOverlap(KCollider* pObj, DWORD dwState);
    virtual void	SelectOverlap(KCollider* pObj, DWORD dwState);
public:
    KPokemon();
    ~KPokemon();
};

