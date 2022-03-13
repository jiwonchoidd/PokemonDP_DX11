#include "KCombat.h"
#include "KUI.h"
#include "KWrite.h"
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
		m_mypoke.Init(m_pContext, &m_pPlayer->m_inven.poketmon_list.front(), true);
		m_mypoke.m_Sound_Cries = g_SoundManager.LoadSound(L"../../data/sound/cries_0.ogg");
	}
	
	//랜덤 숫자 받는 적 포켓몬--------------
	m_enemypoke.m_pinfo = new PokemonInfo();
	m_enemypoke.m_pinfo->hp = 100;
	float random = randstep(1.0f, 4.0f);
	m_enemypoke.m_pinfo->mon_level = fabs(random);
	LevelToSize(m_enemypoke.m_pinfo->mon_level, m_enemypoke.m_pinfo->mon_weight, m_enemypoke.m_pinfo->mon_height);
	switch (id)
	{
	case 0:
	{
		m_enemypoke.m_pinfo->sex = randstep(0,1);
		m_enemypoke.m_pinfo->mon_rect = {1,229,79,79};
		m_enemypoke.m_pinfo->type=0;
		m_enemypoke.m_pinfo->skill = {0};
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
	m_enemypoke.Init(m_pContext, m_enemypoke.m_pinfo, false);
	m_enemypoke.m_Sound_Cries = g_SoundManager.LoadSound(L"../../data/sound/cries_1.ogg");
	//체력바 
	m_my_Health = std::make_shared<KImage>();
	m_enemy_Health = std::make_shared<KImage>();
	m_my_Health->m_Name = L"health_bar";
	m_my_Health->SetRectDraw(0.6f, 0.4f);
	m_my_Health->SetRectSource({ 2,54,121,44});
	m_my_Health->SetPosition(KVector2(0.72f,-0.3f));
	m_my_Health->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	m_my_Health->m_rtOffset = { 0, 0, 0, 0 };
	if (!m_my_Health->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - HP Bars.png",
		L""))
	{
		return false;
	}
	
	m_enemy_Health->m_Name = L"health_bar";
	m_enemy_Health->SetRectDraw(0.6f, 0.3f);
	m_enemy_Health->SetRectSource({ 3,15,119,32 });
	m_enemy_Health->SetPosition(KVector2(-0.75f, 0.3f));
	m_enemy_Health->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	m_enemy_Health->m_rtOffset = { 0, 0, 0, 0 };
	if (!m_enemy_Health->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - HP Bars.png",
		L""))
	{
		return false;
	}
	//체력바 
	KImage* my_hp_bar = new KImage();
	KImage* enemy_hp_bar = new KImage();
	my_hp_bar->m_Name = L"bar1";
	my_hp_bar->SetRectDraw(0.25f, 0.1f);
	my_hp_bar->SetRectSource({ 137,11,50,14 });
	my_hp_bar->SetPosition(KVector2(m_my_Health->m_pos.x+ 0.13f, m_my_Health->m_pos.y-0.05f));
	my_hp_bar->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	my_hp_bar->m_rtOffset = { 30, 30, 30, 30 };
	if (!my_hp_bar->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - HP Bars.png",
		L""))
	{
		return false;
	}
	enemy_hp_bar->m_Name = L"bar2";
	enemy_hp_bar->SetRectDraw(0.25f, 0.1f);
	enemy_hp_bar->SetRectSource({ 137,11,50,14 });
	enemy_hp_bar->SetPosition(KVector2(m_enemy_Health->m_pos.x+ 0.065f, m_enemy_Health->m_pos.y-0.09f));
	enemy_hp_bar->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	enemy_hp_bar->m_rtOffset = { 30, 30, 30, 30 };
	if (!enemy_hp_bar->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - HP Bars.png",
		L""))
	{
		return false;
	}
	m_my_Health.get()->m_pParent = my_hp_bar;
	m_enemy_Health.get()->m_pParent = enemy_hp_bar;
	return true;
}

bool KCombat::Frame()
{
	m_mypoke.Frame();
	m_enemypoke.Frame();
	m_my_Health.get()->Frame();
	m_my_Health.get()->m_pParent->Frame();
	m_enemy_Health.get()->Frame();
	m_enemy_Health.get()->m_pParent->Frame();

	//health bar
	KImage* heath_bar = static_cast<KImage*>(m_my_Health.get()->m_pParent);
	heath_bar->SetRectDraw(0.25f *(m_mypoke.m_pinfo->hp/ 100), heath_bar->m_rtSize.height);
	heath_bar->AddPosition_UI(KVector2(0,0));
	return true;
}

bool KCombat::Render(ID3D11DeviceContext* pContext)
{
	if(m_mypoke.m_bVisibility)
	m_mypoke.Render(pContext);
	if (m_enemypoke.m_bVisibility)
	m_enemypoke.Render(pContext);

	if (m_my_Health.get()->m_bVisibility && m_mypoke.m_bVisibility)
	{
		m_my_Health.get()->m_pParent->Render(pContext);
		m_my_Health.get()->Render(pContext);
		std::wstring level = std::to_wstring(m_mypoke.m_pinfo->mon_level);
		std::wstring hp = std::to_wstring(m_mypoke.m_pinfo->hp);
		std::wstring name = L"팽도리";
		//대화창텍스트 : 무조건 상위에 있어야하기 때문에 나중에 렌더함
		RECT  rt = { g_rtClient.right - 230, g_rtClient.bottom - 242 , g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, name.c_str(),
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
		rt = { g_rtClient.right-40, g_rtClient.bottom - 242, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, level.c_str(),
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
	}
	if (m_enemy_Health.get()->m_bVisibility&& m_enemypoke.m_bVisibility)
	{
		m_enemy_Health.get()->m_pParent->Render(pContext);
		m_enemy_Health.get()->Render(pContext);
		std::wstring level = std::to_wstring(m_enemypoke.m_pinfo->mon_level);
		std::wstring hp = std::to_wstring(m_enemypoke.m_pinfo->hp);
		std::wstring name = L"찌르꼬";
		//이름
		RECT  rt = { 15, 145, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, name.c_str(),
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
		//레벨
		rt = { 180, 145, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, level.c_str(),
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
	}

	return true;
}

bool KCombat::Release()
{
	m_mypoke.Release();
	m_enemypoke.Release();
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
