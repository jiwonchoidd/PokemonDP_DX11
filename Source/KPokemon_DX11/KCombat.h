#pragma once
#include "KPokemon.h"
class KCombat
{
public:
    ID3D11DeviceContext* m_pContext;
    KPlayer2D*          m_pPlayer; // 포켓몬, 인벤토리 
    KPokemon m_mypoke; // 적 포켓몬
    KPokemon m_enemypoke; // 적 포켓몬
    std::shared_ptr<KImage> m_enemy_Health; // 적 포켓몬
    std::shared_ptr<KImage> m_my_Health; // 적 포켓몬
public:
    bool Init(ID3D11DeviceContext* context, KPlayer2D* player,int id= -1);
    bool Frame();
    bool Render(ID3D11DeviceContext* pContext);
    bool Release();
    //레벨에 따라 랜덤한 사이즈를 반환함
    void LevelToSize(int level_value, float& weight, float& height)
    {
        //kg, m
        weight = randstep(0.1 * level_value, 0.9 * level_value);
        height = randstep(0.15, 2);
    }
public:
    KCombat();
    ~KCombat();
};

