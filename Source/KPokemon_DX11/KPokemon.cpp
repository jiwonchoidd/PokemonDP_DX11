#include "KPokemon.h"

bool KPokemon::Init(ID3D11DeviceContext* context, PokemonInfo* info, bool ismine)
{
	m_pContext = context;
	m_Name = L"pokemon";
	m_pinfo = info;
	SetRectSource(m_pinfo->mon_rect);
	//�� ���ϸ��̸�, ��ġ �ٲ���
	if (ismine)
	{
		SetPosition(KVector2(-2,-2));
	}
	else
	{
		SetPosition(KVector2(2, 2));
	}
	//ũ��
	SetRectDraw({ 0,0,1,1 });
	//�̹��� ������Ʈ ����
	K2DAsset::CreateObject_Mask(L"../../data/shader/VS_UI_0", 
		L"../../data/shader/PS_UI_0", 
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - Pokemon 4th Generation.png", L"");
	return true;
}

bool KPokemon::Frame()
{
	return true;
}

bool KPokemon::Render(ID3D11DeviceContext* pContext)
{
	return true;
}

void KPokemon::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
}

void KPokemon::SelectOverlap(KCollider* pObj, DWORD dwState)
{
}

KPokemon::KPokemon()
{
	m_pinfo = nullptr;
}

KPokemon::~KPokemon()
{
}
