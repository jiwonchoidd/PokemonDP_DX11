#include "KSceneManager.h"

bool KSceneManager::Init(ID3D11DeviceContext* context)
{
	m_pContext = context;

	
	//ĳ���ʹ� �ϳ��� ��ü�� ���� �ֱ�� ��
	m_Player = new KPlayer2D();
	m_Player->SetRectDraw({ 0, 0, 3, 4 });
	m_Player->m_CollisonType = KCollisionType::Overlap;
	//ĳ���Ϳ� �ʰ� ��� ���´�.
	if (!m_Player->Init(m_pContext,
		L"../../data/shader/VS_2D.txt",
		L"../../data/shader/PS_2D.txt",
		L"../../data/texture/player_lucas.png",
		L"../../data/texture/player_lucas_mask.png"))
	{
		return false;
	}
	//-����������. ���ϸ� �κ��丮�� �߰��Ѵ�
	PokemonInfo temp;
	temp.hp = 100;
	temp.mon_height = 1.0f;
	temp.mon_weight = 1.0f;
	temp.mon_level = 1;
	temp.mon_rect = { 1621, 34, 79, 79 };
	temp.sex = true;
	temp.type = 0;
	temp.skill = { 0 };
	m_Player->m_inven.poketmon_list.push_back(temp);

	//ù��° ���� ��Ʈ�� �����Ѵ�. 
	//m_pCurrentScene = new KScene_Combat;
	//m_CurrentScene_Index = S_COMBAT;
	m_pCurrentScene = new KScene_Intro;
	m_CurrentScene_Index = S_INTRO;
	m_pCurrentScene->Init(m_pContext);
	m_pCurrentScene->Load(L"test");

	return true;
}

KScene* KSceneManager::GetScene()
{
	return m_pCurrentScene;
}

bool KSceneManager::SetScene(BYTE index)
{
	//�� ���� �ʱ�ȭ
	if (m_pCurrentScene != nullptr)
	{
		//������Ʈ ����Ʈ ����
		g_ObjManager.Release();
		if (m_pCurrentScene != nullptr)
		{
			m_pCurrentScene->Release();
			delete m_pCurrentScene;
			m_pCurrentScene = nullptr;
		}
	}
	//
	m_Player->RegisterOverlap();
	//���� ����
	switch (index)
	{
		/*	S_INTRO,
			S_GAME_0,
			S_GAME_1,
			S_COMBAT,*/
		case S_INTRO:
		{
			m_pCurrentScene = new KScene_Intro;
			m_CurrentScene_Index = S_INTRO;
			break;
		}
		case S_GAME_0:
		{
			m_pCurrentScene = new KScene_Game_0;
			m_CurrentScene_Index = S_GAME_0;
			break;
		}
		case S_GAME_1:
		{
			m_pCurrentScene = new KScene_Game_1;
			m_CurrentScene_Index = S_GAME_1;
			break;
		}
		case S_COMBAT:
		{
			m_pCurrentScene = new KScene_Combat;
			m_CurrentScene_Index = S_COMBAT;
			break;
		}
		default:
			break;
		}
	m_pCurrentScene->Init(m_pContext);
	m_pCurrentScene->Load(L"test");

	return true;
}

bool KSceneManager::Frame()
{
	m_pCurrentScene->Frame();
	return true;
}

bool KSceneManager::Render()
{
	m_pCurrentScene->Render();
	return true;
}

bool KSceneManager::Release()
{
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Release();
		delete m_pCurrentScene;
		m_pCurrentScene = nullptr;
		return true;
	}
	return true;
}

KSceneManager::KSceneManager()
{
	m_pCurrentScene = nullptr;
	m_bChangeScene = false;
	m_CurrentScene_Index = -1;
	m_Timer = 0.0f;
	m_pContext = nullptr;
	m_Player= nullptr;
	m_BGM = nullptr;
}
