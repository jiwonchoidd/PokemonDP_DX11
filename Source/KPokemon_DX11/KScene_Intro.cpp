#include "KScene_Intro.h"
#include "KSceneManager.h"
#include "KUI.h"
#include "KWrite.h"
bool KScene_Intro::Load(std::wstring file)
{
	//사운드 바로 실행
	if (g_SceneManager.m_BGM==nullptr)
	{
		//g_SceneManager.m_BGM->SoundStop();
		g_SceneManager.m_BGM = g_SoundManager.LoadSound(L"../../data/sound/bgm/Opening Movie.wav");
		g_SceneManager.m_BGM->SoundPlay(true);
	}
	//UI 생성
	KImage* obj = new KImage;
	obj->SetRectSource({ 5,590,250,105});
	obj->SetRectDraw({ 0, 0, 1, 1});
	if (!obj->Init(m_pContext,L"../../data/shader/VS_UI_0.txt", L"../../data/shader/PS_UI_Mask.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - Intro Movie.png", L"../../data/texture/intro_mask.jpg"))
	{
		return false;
	}
	obj->m_fAlpha = 0.35f;

	m_UIObj.push_back(std::shared_ptr<KObject>(obj));
	return true;
}

bool KScene_Intro::Init(ID3D11DeviceContext* context)
{
	KScene::Init(context);
	m_SceneID = S_INTRO;
	return true;
}

bool KScene_Intro::Frame()
{
	g_SceneManager.m_BGM->Frame();

	g_SceneManager.m_Timer += g_fSecPerFrame;
	if (g_SceneManager.m_Timer > 3.0f)
	{
		m_bStart = true;
		g_SceneManager.m_Timer = 0.0;
	
	}
	if (m_bStart)
	{
		static_cast<KImage*>(m_UIObj[0].get())->m_bFadeIn = true;
		//m_UIObj[0].get()->m_cbData.vLightDir = { 1.0f,1.0f,1.0f,1.0f };
		if (g_InputData.bZKey)
		{
			g_SceneManager.m_Timer = 0.0f;
			g_SceneManager.SetScene(1);
			return true;
		}
	}
	KScene::Frame();
	return true;
}

bool KScene_Intro::Render()
{
	KScene::Render();
		RECT  rt = { 30, g_rtClient.bottom - 50, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, L"©2006 Pokemon. ©1995-2006 Nintendo/Creatures Inc./GAME FREAK inc. This content has been created in agreement with the Terms of Use for the Pokemon DP Sound Library.",
			D2D1::ColorF(0.5f, 0.5f, 0.5f, 1), g_Write->m_pTextGame10);
		rt = { 30,20, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, L"이동 -> 방향키\n확인 -> Z\n취소-> X\n메뉴 -> A",
			D2D1::ColorF(0.5f, 0.5f, 0.5f, 1), g_Write->m_pTextGame25);
		if (m_bStart)
		{
			rt = { g_rtClient.right/2-140,g_rtClient.bottom /2 +140, g_rtClient.right, g_rtClient.bottom };
			g_Write->RenderText_Sequence(rt, L"계속하려면 Z키를 누르세요.",
				D2D1::ColorF(1.0f, 1.0f, 1.0f, 1), g_Write->m_pTextGame25);
		}
	return true;
}

bool KScene_Intro::Release()
{
	g_SceneManager.m_BGM->SoundStop();
	KScene::Release();
	return true;
}
