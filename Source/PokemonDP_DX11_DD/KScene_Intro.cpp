#include "KScene_Intro.h"
#include "KSceneManager.h"
#include "KUI.h"
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
	obj->m_fAlpha = 0.0f;
	obj->m_bFadeIn = true;
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
	if (g_InputData.bUpKey)
	{
		g_SceneManager.SetScene(1);
		return true;
	}
	KScene::Frame();
	return true;
}

bool KScene_Intro::Render()
{
	KScene::Render();
	return true;
}

bool KScene_Intro::Release()
{
	g_SceneManager.m_BGM->SoundStop();
	KScene::Release();
	return true;
}
