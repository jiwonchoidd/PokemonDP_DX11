#pragma once
#include "KPlayer2D.h"
#include "KUI.h"
//���ϸ� ������ �޾ƿͼ� 
//���ϸ� ������Ʈ�� ����� Ŭ����

// mon_rect;
// mon_level; //����
// mon_height;//Ű
// mon_weight;//������
// type; //Ÿ��
// sex; //����
// skill;

class KPokemon :public KImage
{
public:
    PokemonInfo* m_pinfo;
    bool         m_bMine;
    bool         m_bAnimation;
    bool         m_bAttackMove;
    float        m_Timer;
    KSound*      m_Sound_Cries;
public:
    bool Init(ID3D11DeviceContext* context, PokemonInfo* info, bool ismine=false);
    bool Frame();
    bool Render(ID3D11DeviceContext* pContext);
public:
    KPokemon();
    ~KPokemon();
};

