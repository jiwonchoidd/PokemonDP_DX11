#include "KPokemon.h"
#include "KSpriteManager.h"
bool KPokemon::Init(ID3D11DeviceContext* context, PokemonInfo* info, bool ismine)
{
	m_Name = L"pokemon";
	m_cbData.vLightDir = {1,1,1,1};
	m_bAttackMove = false;
	m_pinfo = info;
	//이미지 오브젝트 생성
	SetRectSource(m_pinfo->mon_rect);
	//내 포켓몬이면, 위치 바꿔줌
	if (ismine)
	{
		m_bMine = true;
		SetRectDraw(0.5f, 1);
		SetPosition(KVector2(-0.6f,-0.01f));
	}
	else
	{
		m_bMine = false;
		SetRectDraw(0.5f/1.2f, 1.0f/1.2f);
		SetPosition(KVector2(0.58f, 0.18f));
		// 애니메이션 
		KSprite* attack = new KSprite;
		attack->m_Name = L"attack";
		attack->m_anim_time = 0.0f;
		RECT rc = m_pinfo->mon_rect;
		RECT rc1 = { rc.left + 81, rc.top, rc.right, rc.bottom };
		attack->SetAnimArray(rc);
		attack->SetAnimArray(rc1);
		attack->SetAnimArray(rc);
		attack->SetAnimArray(rc1);
		g_SpriteManager.Load(attack);
		SetRectSource(attack->m_anim_array[0]);
	}
	m_pContext = context;
	K2DAsset::CreateObject_Mask(L"../../data/shader/VS_UI_0.txt", 
		L"../../data/shader/PS_UI_Mask.txt", 
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - Pokemon 4th Generation.png", L"../../data/texture/Pokemon 4th Generation_Mask.jpg");
	return true;
}

bool KPokemon::Frame()
{
	//적일 경우만 애니메이션이 있음
	//적 애니메이션-----------------
	if (!m_bMine)
	{
		if (m_bAnimation)
		{
			KSprite* attack = g_SpriteManager.GetPtr(L"attack");
			attack->RunAnim(1, 0,2);
			AddPosition(KVector2(0, 0));
			SetRectSource(attack->m_anim_array[attack->m_AnimIndex]);
			m_Timer += g_fSecPerFrame;
			if (m_Timer > 3.0f)
			{
				SetRectSource(attack->m_anim_array[0]);
				m_Timer = 0.0f;
				m_bAnimation = false;
			}
		}
	}

	if (m_bAttackMove)
	{
		m_Timer += g_fSecPerFrame;
		KVector2 dir;
		if (m_bMine)
		{
			KVector2 dir = { 1,1 };
		}
		else
		{
			KVector2 dir = { -1,-1 };
		}
		dir= 10.0f*dir *g_fSecPerFrame;
		AddPosition_UI(dir);
		if (m_Timer > 0.5f)
		{
			
			m_Timer = 0.0f;
			m_bAttackMove = false;
		}
	}
	KObject::Frame();
	return true;
}

bool KPokemon::Render(ID3D11DeviceContext* pContext)
{
	KObject::Render(pContext);
	return true;
}

KPokemon::KPokemon()
{
	m_pinfo = nullptr;
}

KPokemon::~KPokemon()
{
}
