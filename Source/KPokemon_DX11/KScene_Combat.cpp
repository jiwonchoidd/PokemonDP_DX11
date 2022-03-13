#include "KScene_Combat.h"
#include "KSceneManager.h"
#include "KUI.h"
#include "KWrite.h"
bool KScene_Combat::Load(std::wstring file)
{
	#pragma region 사용할 모델 생성
	// 전투 배경
	std::shared_ptr<KImage> combat_background(new KImage);
	combat_background->m_Name = L"combat_background";
	combat_background->SetRectDraw({ 0,0,g_rtClient.right, g_rtClient.bottom});
	combat_background->SetPosition(KVector2(g_rtClient.right/2, g_rtClient.bottom/2));
	combat_background->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	combat_background->m_rtOffset = { 0, 0, 0, 0 };
	if (!combat_background->Init(m_pContext,
		L"../../data/shader/VS_UI_Move.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/combat_background.png",
		L""))
	{
		return false;
	}
	//전투 배경화면 초반에 쉐이더로 uv이동
	combat_background->m_bMoveImg = true;
	m_UIObj.push_back(std::shared_ptr<KObject>(combat_background));

	std::shared_ptr<KImage> dialog_background(new KImage);
	dialog_background->m_Name = L"dialog_background";
	dialog_background->SetRectDraw({ 0,0,g_rtClient.right, g_rtClient.bottom /4});
	dialog_background->SetPosition(KVector2(g_rtClient.right / 2, 70));
	dialog_background->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	dialog_background->m_rtOffset = { 10, 10, 10, 10 };
	if (!dialog_background->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - Text Boxes.png",
		L""))
	{
		return false;
	}
	std::shared_ptr<KImage> select_background(new KImage);
	select_background->m_Name = L"select_background";
	select_background->SetRectDraw({ 0,0,g_rtClient.right, g_rtClient.bottom / 4 });
	select_background->SetPosition(KVector2(g_rtClient.right / 2, g_rtClient.bottom - 70));
	select_background->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	select_background->m_rtOffset = { 30, 30, 30, 30 };
	if (!select_background->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/menu_background.png",
		L""))
	{
		return false;
	}
	g_UIModelManager.m_list.insert(std::make_pair(L"select_background", select_background));
	// 발판
	std::shared_ptr<KImage> combat_stepimg(new KImage);
	combat_stepimg->m_Name = L"combat_step";
	combat_stepimg->SetRectDraw({ 0,0,128 * 2, 40 * 2 });
	combat_stepimg->SetPosition(KVector2(g_rtClient.right / 2, g_rtClient.bottom / 2));
	combat_stepimg->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	combat_stepimg->m_rtOffset = { 0, 0, 0, 0 };
	if (!combat_stepimg->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/combat_foot.png",
		L""))
	{
		return false;
	}
	g_UIModelManager.m_list.insert(std::make_pair(L"combat_step", combat_stepimg));
#pragma endregion

	#pragma region 버튼 모델 생성
	//메뉴 버튼-------------------
	std::shared_ptr<KButton> btn(new KButton);
	btn->m_Name = L"combat_button";
	btn->m_rtOffset = { 40, 40, 40, 40 };
	btn->SetRectDraw({ 0, 0, 120, 50 });
	btn->SetPosition(KVector2(g_rtClient.right, g_rtClient.bottom));
	btn->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);

	KTexture* pTex = g_TextureMananger.Load(L"../../data/texture/blank.png");
	KSound* pSound = g_SoundManager.LoadSound(L"../../data/sound/menu_open.mp3");
	btn->m_datalist.emplace_back(pTex, pSound);

	pTex = g_TextureMananger.Load(L"../../data/texture/menu_hover.png");
	pSound = g_SoundManager.LoadSound(L"../../data/sound/menu_hover.mp3");
	btn->m_datalist.emplace_back(pTex, pSound);

	pTex = g_TextureMananger.Load(L"../../data/texture/menu_hover.png");
	//pSound = g_SoundManager.LoadSound(L"../../data/sound/menu_select.mp3");
	btn->m_datalist.emplace_back(pTex, pSound);

	if (!btn->Init(m_pContext, L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/blank.png", L""))
	{
		return false;
	}
	g_UIModelManager.m_list.insert(std::make_pair(L"combat_button", btn));
#pragma endregion
	
	//발판
	//-----------------------------------------------------
	KUIModel* mystep = g_UIModelManager.GetPtr(L"combat_step")->Clone();
	mystep->SetRectDraw({ 0,0,128 * 4, 40 * 4 });
	mystep->SetPosition(KVector2(200, g_rtClient.bottom - 150));
	mystep->UpdateData();
	KUIModel* enemystep = g_UIModelManager.GetPtr(L"combat_step")->Clone();
	enemystep->SetPosition(KVector2(g_rtClient.right - 200, g_rtClient.bottom / 2));
	enemystep->UpdateData();

	//싸운다.
	//도망간다.
	//가방.
	KUIModel* button1 = g_UIModelManager.GetPtr(L"combat_button")->Clone();
	button1->m_Name = L"menu_button_1";
	button1->SetPosition(KVector2(g_rtClient.right/2-120, g_rtClient.bottom-70));
	button1->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button1->UpdateData();
	KUIModel* button2 = g_UIModelManager.GetPtr(L"combat_button")->Clone();
	button2->m_Name = L"menu_button_2";
	float offset = 120.0f;
	button2->SetPosition(KVector2(button1->m_pos.x + offset, button1->m_pos.y));
	button2->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button2->UpdateData();
	KUIModel* button3 = g_UIModelManager.GetPtr(L"combat_button")->Clone();
	button3->m_Name = L"menu_button_3";
	button3->SetPosition(KVector2(button2->m_pos.x + offset, button1->m_pos.y));
	button3->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button3->UpdateData();
	std::shared_ptr<KUIModelComposite> compositeobj(new KUIModelComposite);
	compositeobj->m_Name = L"1_Menu";
	button1->m_cbData.vLightDir = { 1.0f,0.5f,0.3f,1 };
	button2->m_cbData.vLightDir = { 1.0f,0.5f,0.3f,1 };
	button3->m_cbData.vLightDir = { 1.0f,0.5f,0.3f,1 };

	compositeobj->Add(button1);
	compositeobj->Add(button2);
	compositeobj->Add(button3);
	//씬 유아이 리스트 추가
	m_UIObj.push_back(std::shared_ptr<KObject>(mystep));
	m_UIObj.push_back(std::shared_ptr<KObject>(enemystep));
	m_UIObj.push_back(std::shared_ptr<KObject>(dialog_background));
	m_UIObj.push_back(std::shared_ptr<KObject>(select_background));
	m_UIObj.push_back(std::shared_ptr<KObject>(compositeobj));

	m_Combat_Menu_0 = compositeobj;
	//시작시에 메뉴가 보이지 않기 위해 모든 컴포넌트 invisibility
	m_Combat_Menu_0.get()->m_bVisibility = false;
	for (auto list : m_Combat_Menu_0.get()->m_Components)
	{
		list->m_bVisibility = false;
	}
	//m_Combat_Menu_1 = 

	//effect---------------------------------------------
	m_EffectPlayer = std::make_shared<KSpriteEffect>();
	g_SpriteManager.Load(L"../../data/texture/Sprite.txt");
	m_EffectPlayer.get()->m_pSprite = g_SpriteManager.GetPtr(L"rtThrowPlayer");

	m_EffectPlayer.get()->SetPosition(KVector2(-0.6f, -0.14f));
	m_EffectPlayer.get()->SetRectDraw(0.4f, 0.8f);
	m_EffectPlayer.get()->SetRectSource(m_EffectPlayer.get()->m_pSprite->m_anim_array[0]);
	m_EffectPlayer.get()-> Init(m_pContext, L"../../data/shader/VS_UI_0.txt", L"../../data/shader/PS_UI_Mask.txt",
		L"../../data/texture/player_lucas.png", L"../../data/texture/player_lucas_mask.png");
	m_EffectPlayer.get()->m_bEnd = true;

	return true;
}

bool KScene_Combat::Init(ID3D11DeviceContext* context)
{
	//상속된 씬 초기화
	KScene::Init(context);

	m_text_dialog = L"우왓! 야생 찌르꼬가 돌진해왔다!";
	//현재 씬 열거형 타입 지정
	m_SceneID = S_COMBAT;

	//원래 랜덤으로 하는데 적포켓몬이 한명뿐임
	m_Combat.Init(m_pContext, g_SceneManager.m_Player, 0);
	m_Combat.m_mypoke.m_bVisibility = false;
	m_Combat.m_enemypoke.m_bAnimation = true;
	return true;
}

bool KScene_Combat::Frame()
{
	//처음 인트로 시작
	if (!m_Event_Intro)
	{
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer >= 2)
		{
			m_text_dialog = L"가랏! 팽도리!";
			g_SceneManager.m_Timer = 0;
			m_EffectPlayer.get()->m_bEnd = false;
			m_EffectPlayer.get()->Reset();
			m_EffectPlayer.get()->SetRectSource(m_EffectPlayer.get()->m_pSprite->m_anim_array[0]);
			m_Combat.m_enemypoke.m_Sound_Cries->SoundPlay_Once();
			m_Event_Intro = true;
			m_Event_Intro_End = true;
		}
	}
	//포켓몬볼 던지고 난 후, 또는 한 루틴이 끝났을때
	if (m_Event_Intro_End)
	{	
		g_SceneManager.m_Timer += g_fSecPerFrame;
		float temp = -0.5* g_fSecPerFrame;
		m_EffectPlayer.get()->AddPosition_UI(KVector2(temp, 0.0f));
		if (g_SceneManager.m_Timer >= 1.5f)
		{
			m_Combat.m_mypoke.m_Sound_Cries->SoundPlay_Once();
			m_Combat.m_mypoke.m_bVisibility = true;
			m_text_dialog = L"팽도리는 무엇을 할까?";
			ActiveSelect();
			g_SceneManager.m_Timer = 0;
			m_Event_Intro_End = false;
		}
	}


	if (m_bMenu)
	{
		int button_count = m_Combat_Menu_0.get()->m_ButtonComponents.size();

		//위아래로 버튼 리스트 조작
		if (g_InputData.bMenu_UP)
		{
			if (m_Combat_Menu_0.get()->m_iSelected > 0)
				m_Combat_Menu_0.get()->m_iSelected = m_Combat_Menu_0.get()->m_iSelected - 1;
		}
		if (g_InputData.bMenu_DOWN)
		{
			if (m_Combat_Menu_0.get()->m_iSelected < button_count - 1)
				m_Combat_Menu_0.get()->m_iSelected = m_Combat_Menu_0.get()->m_iSelected + 1;
		}
		//해당 버튼 호버 상태로 변환
		m_Combat_Menu_0.get()->m_ButtonComponents[m_Combat_Menu_0.get()->m_iSelected]->m_SelectState = KSelectState::S_HOVER;

		//선택 Z키 입력시 발동 또는 클릭 시에 m_bSelect가 true 가 된다.
		if (g_InputData.bMenu_SELECT)
		{
			m_Combat_Menu_0.get()->m_ButtonComponents[m_Combat_Menu_0.get()->m_iSelected]->m_SelectState = KSelectState::S_SELECTED;
		}
		//각 버튼의 동작
		//싸운다.
		if (m_Combat_Menu_0.get()->m_ButtonComponents[0]->m_bSelect)
		{
			ActiveSelect();
			m_Combat_Menu_0.get()->m_ButtonComponents[0]->m_SelectState = KSelectState::S_DEFAULT;
			m_Combat_Menu_0.get()->m_ButtonComponents[0]->m_bSelect = false;

			m_text_dialog = L"팽돌이의\n몸통박치기! ";
			m_bAttack = true;
		}
		//todo: 가방 : 미구현
		if (m_Combat_Menu_0.get()->m_ButtonComponents[1]->m_bSelect)
		{
			//아무 작동하지않음
			m_Combat_Menu_0.get()->m_ButtonComponents[1]->m_SelectState = KSelectState::S_DEFAULT;
			m_Combat_Menu_0.get()->m_ButtonComponents[1]->m_bSelect = false;
		}
		//todo : 도망가기
		if (m_Combat_Menu_0.get()->m_ButtonComponents[2]->m_bSelect)
		{
			//리포트
			m_text_dialog = L"무사히 도망쳤다!";
			m_bGameEnd = true;;
			ActiveSelect();
			KSound* sound = g_SoundManager.LoadSound(L"../../data/sound/scene.mp3");
			sound->SoundPlay_Once();
			m_Combat_Menu_0.get()->m_ButtonComponents[2]->m_SelectState = KSelectState::S_DEFAULT;
			m_Combat_Menu_0.get()->m_ButtonComponents[2]->m_bSelect = false;

		}
	}


	//공격발동
	if (m_bAttack)
	{
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 4.0f)
		{
			KSound* attack_sound = g_SoundManager.LoadSound(L"../../data/sound/kick.mp3");
			attack_sound->SoundPlay_Once();
			m_Combat.m_mypoke.m_bAttackMove = true;
			m_Combat.m_enemypoke.m_pinfo->DecHP(50);
			m_bAttack = false;
			m_bAttack_End = true;
			g_SceneManager.m_Timer = 0.0f;
		}
	}
	//공격 끝남
	if (m_bAttack_End)
	{
		m_text_dialog = L"찌르꼬의\n몸통 박치기!";
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 4.0f)
		{
			KSound* attack_sound = g_SoundManager.LoadSound(L"../../data/sound/kick.mp3");
			attack_sound->SoundPlay_Once();
			m_Combat.m_enemypoke.m_bAnimation = true;
			m_Combat.m_mypoke.m_pinfo->DecHP(10);
			m_Event_Intro_End = true;
			m_bAttack_End = false;
			g_SceneManager.m_Timer = 0.0f;
		}
	}

	//상대의 hp가 0보다 작다면
	if (m_Combat.m_enemypoke.m_pinfo->hp < 0)
	{
		m_text_dialog = L"찌르꼬를 물리쳤다!";
		m_Combat.m_enemypoke.m_bVisibility = false;
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 4.0f)
		{
			KSound* attack_sound = g_SoundManager.LoadSound(L"../../data/sound/scene.mp3");
			attack_sound->SoundPlay_Once();
			m_bGameEnd = true;
			g_SceneManager.m_Timer = 0.0f;
		}
	}

	if (m_bGameEnd)
	{
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 2.0f)
		{
			g_SceneManager.m_Timer = 0.0f;
			g_SceneManager.SetScene(2);
		}
	}
	m_EffectPlayer.get()->Frame();
	KScene::Frame();
	m_Combat.Frame();
	return true;
}

bool KScene_Combat::Render()
{

	KScene::Render();
    m_EffectPlayer.get()->Render(m_pContext);
	m_Combat.Render(m_pContext);

	//대화창텍스트 : 무조건 상위에 있어야하기 때문에 나중에 렌더함
	RECT  rt = { 25, 15 , g_rtClient.right, g_rtClient.bottom};
	g_Write->RenderText_Sequence(rt, m_text_dialog,
		D2D1::ColorF(0.2f, 0.2f, 0.3f, 1));

	//메뉴
	if (m_bMenu)
	{
		rt = { 320, g_rtClient.bottom -100, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, L"싸운다",
			D2D1::ColorF(0.5f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
		rt = { rt.left + 130,rt.top,rt.right,rt.bottom };
		g_Write->RenderText(rt, L"가방",
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
		rt = { rt.left + 100,rt.top,rt.right,rt.bottom };
		g_Write->RenderText(rt, L"도망간다",
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
	}
	
	return true;
}

bool KScene_Combat::Release()
{
	m_Combat.Release();
	KScene::Release();
	return true;
}

void KScene_Combat::ActiveSelect()
{
	g_SceneManager.m_Player->m_bMove = !g_SceneManager.m_Player->m_bMove;
	m_bMenu = !m_bMenu;
	m_Combat_Menu_0.get()->m_bVisibility = !m_Combat_Menu_0.get()->m_bVisibility;
	for (auto list : m_Combat_Menu_0.get()->m_Components)
	{
		list->m_bVisibility = !list->m_bVisibility;
	}
	KSound* sound = g_SoundManager.LoadSound(L"../../data/sound/menu_open.mp3");
	sound->SoundPlay_Once();
}
