#include "KCombat.h"
#include "KUI.h"
//적 포켓몬을 담당함
//플레이어 포켓몬 레벨에 맞는 적당한 
//포켓몬 레벨을 가진 몬스터로
//랜덤으로 나옴
bool KCombat::Init(ID3D11DeviceContext* context, KPlayer2D* player, int id)
{
	m_pContext = context;
	m_pPlayer = player;
	//포켓몬 정보를 사전에 갖고 있음
	//만약에 본인 포켓몬이 있으면 정보 가져옴
	if (m_pPlayer->m_inven.poketmon_list.size() > 0)
	{
		PokemonInfo mineinfo = m_pPlayer->m_inven.poketmon_list.front();

		m_mypoke = std::make_shared<KPokemon>();
		m_mypoke.get()->Init(m_pContext, &mineinfo, true);
	}
	
	//랜덤 숫자 받는 적 포켓몬
	m_enemypoke = std::make_shared<KPokemon>();
	PokemonInfo enemyinfo;
	enemyinfo.hp = 100;
	enemyinfo.mon_level = randstep(1,(m_mypoke.get()->m_pinfo->mon_level)+2);
	LevelToSize(enemyinfo.mon_level, enemyinfo.mon_weight, enemyinfo.mon_height);
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

KCombat::KCombat()
{
	m_pPlayer = nullptr;
}

KCombat::~KCombat()
{
	m_pPlayer = nullptr;
}
