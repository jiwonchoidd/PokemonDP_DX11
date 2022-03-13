#pragma once
#include "KPokemon.h"
class KCombat
{
public:
    ID3D11DeviceContext* m_pContext;
    KPlayer2D*          m_pPlayer; // ���ϸ�, �κ��丮 
    KPokemon m_mypoke; // �� ���ϸ�
    KPokemon m_enemypoke; // �� ���ϸ�
    std::shared_ptr<KImage> m_enemy_Health; // �� ���ϸ�
    std::shared_ptr<KImage> m_my_Health; // �� ���ϸ�
public:
    bool Init(ID3D11DeviceContext* context, KPlayer2D* player,int id= -1);
    bool Frame();
    bool Render(ID3D11DeviceContext* pContext);
    bool Release();
    //������ ���� ������ ����� ��ȯ��
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

