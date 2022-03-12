#include "KCombat.h"
#include "KCombatCalculator.h"
#include "KUI.h"
//�� ���ϸ��� �����
//�÷��̾� ���ϸ� ������ �´� ������ 
//���ϸ� ������ ���� ���ͷ�
//�������� ����
bool KCombat::Init(ID3D11DeviceContext* context, KPlayer2D* player, int id)
{
	m_pContext = context;
	m_pPlayer = player;
	//���ϸ� ������ ������ ���� ����
	//���࿡ ���� ���ϸ��� ������ ���� ������
	if (m_pPlayer->m_inven.poketmon_list.size() > 0)
	{
		PokemonInfo mineinfo = m_pPlayer->m_inven.poketmon_list.front();

		m_mypoke = std::make_shared<KPokemon>();
		m_mypoke.get()->Init(m_pContext, &mineinfo, true);
	}
	
	//���� ���� �޴� �� ���ϸ�
	m_enemypoke = std::make_shared<KPokemon>();
	PokemonInfo enemyinfo;
	enemyinfo.hp = 100;
	enemyinfo.mon_level = randstep(1,(m_mypoke.get()->m_pinfo->mon_level)+2);
	leveltosize(enemyinfo.mon_level, enemyinfo.mon_weight, enemyinfo.mon_height);
	switch (id)
	{
	case 0:
	{
		enemyinfo.sex = randstep(0,1);
		enemyinfo.mon_rect = {1,229,79,79};
		enemyinfo.type=0;
		enemyinfo.skill = {0};
	}break;
	case 1:
	{

	}break;
	case 2:
	{

	}break;
	case 3:
	{

	}break;
	default:
		break;
	}
	m_enemypoke.get()->Init(m_pContext, &enemyinfo, true);
	return true;
}

bool KCombat::Frame()
{
	m_mypoke.get()->Frame();
	m_enemypoke.get()->Frame();
	return true;
}

bool KCombat::Render(ID3D11DeviceContext* pContext)
{
	m_mypoke.get()->Render(pContext);
	m_enemypoke.get()->Render(pContext);
	return true;
}

bool KCombat::Release()
{
	m_mypoke.get()->Release();
	m_enemypoke.get()->Release();
	return true;
}

void KCombat::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
}

KCombat::KCombat()
{
	m_pPlayer = nullptr;
}

KCombat::~KCombat()
{
	m_pPlayer = nullptr;
}
