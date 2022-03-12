#pragma once
#include "KScene_Intro.h" // intro
#include "KScene_Game_0.h"// game_0
#include "KScene_Game_1.h"//game_1
#include "KScene_Combat.h" //combat
#include "KSoundManager.h"
//�� ��� ����
class KSceneManager : public Singleton <KSceneManager>
{
public:
	enum SceneID
	{
		S_INTRO,
		S_GAME_0,
		S_GAME_1,
		S_COMBAT,
	};
public:
	friend class Singleton<KSceneManager>;
public:
	KScene*						m_pCurrentScene;
	BYTE						m_CurrentScene_Index;
	ID3D11DeviceContext*		m_pContext;	// ����̽� ���ؽ�Ʈ ��ü
public:
	KPlayer2D*					m_Player;
	KSound*						m_BGM;
public:
	bool	m_bChangeScene;
	float	m_Timer;
public:
	KScene* GetScene();
	bool	SetScene(BYTE index);
public:
	bool	Init(ID3D11DeviceContext* context);
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	KSceneManager();
};

#define g_SceneManager KSceneManager::Get()