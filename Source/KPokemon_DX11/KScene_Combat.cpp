#include "KScene_Combat.h"
#include "KSceneManager.h"
#include "KUI.h"
#include "KWrite.h"
bool KScene_Combat::Load(std::wstring file)
{
	#pragma region ����� �� ����
	// ���� ���
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
	//���� ���ȭ�� �ʹݿ� ���̴��� uv�̵�
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
	// ����
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

	#pragma region ��ư �� ����
	//�޴� ��ư-------------------
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
	
	//����
	//-----------------------------------------------------
	KUIModel* mystep = g_UIModelManager.GetPtr(L"combat_step")->Clone();
	mystep->SetRectDraw({ 0,0,128 * 4, 40 * 4 });
	mystep->SetPosition(KVector2(200, g_rtClient.bottom - 150));
	mystep->UpdateData();
	KUIModel* enemystep = g_UIModelManager.GetPtr(L"combat_step")->Clone();
	enemystep->SetPosition(KVector2(g_rtClient.right - 200, g_rtClient.bottom / 2));
	enemystep->UpdateData();

	//�ο��.
	//��������.
	//����.
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
	//�� ������ ����Ʈ �߰�
	m_UIObj.push_back(std::shared_ptr<KObject>(mystep));
	m_UIObj.push_back(std::shared_ptr<KObject>(enemystep));
	m_UIObj.push_back(std::shared_ptr<KObject>(dialog_background));
	m_UIObj.push_back(std::shared_ptr<KObject>(select_background));
	m_UIObj.push_back(std::shared_ptr<KObject>(compositeobj));

	m_Combat_Menu_0 = compositeobj;
	//���۽ÿ� �޴��� ������ �ʱ� ���� ��� ������Ʈ invisibility
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
	//��ӵ� �� �ʱ�ȭ
	KScene::Init(context);

	m_text_dialog = L"���! �߻� ����� �����ؿԴ�!";
	//���� �� ������ Ÿ�� ����
	m_SceneID = S_COMBAT;

	//���� �������� �ϴµ� �����ϸ��� �Ѹ����
	m_Combat.Init(m_pContext, g_SceneManager.m_Player, 0);
	m_Combat.m_mypoke.m_bVisibility = false;
	m_Combat.m_enemypoke.m_bAnimation = true;
	return true;
}

bool KScene_Combat::Frame()
{
	//ó�� ��Ʈ�� ����
	if (!m_Event_Intro)
	{
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer >= 2)
		{
			m_text_dialog = L"����! �ص���!";
			g_SceneManager.m_Timer = 0;
			m_EffectPlayer.get()->m_bEnd = false;
			m_EffectPlayer.get()->Reset();
			m_EffectPlayer.get()->SetRectSource(m_EffectPlayer.get()->m_pSprite->m_anim_array[0]);
			//m_Combat.m_enemypoke.m_Sound_Cries->SoundPlay_Once();
			m_Event_Intro = true;
			m_Event_Intro_End = true;
		}
	}
	//���ϸ� ������ �� ��, �Ǵ� �� ��ƾ�� ��������
	if (m_Event_Intro_End)
	{	
		g_SceneManager.m_Timer += g_fSecPerFrame;
		float temp = -0.5* g_fSecPerFrame;
		m_EffectPlayer.get()->AddPosition_UI(KVector2(temp, 0.0f));
		if (g_SceneManager.m_Timer >= 1.5f)
		{
			m_Combat.m_mypoke.m_Sound_Cries->SoundPlay_Once();
			m_Combat.m_mypoke.m_bVisibility = true;
			m_text_dialog = L"�ص����� ������ �ұ�?";
			ActiveSelect();
			g_SceneManager.m_Timer = 0;
			m_Event_Intro_End = false;
		}
	}


	if (m_bMenu)
	{
		int button_count = m_Combat_Menu_0.get()->m_ButtonComponents.size();

		//���Ʒ��� ��ư ����Ʈ ����
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
		//�ش� ��ư ȣ�� ���·� ��ȯ
		m_Combat_Menu_0.get()->m_ButtonComponents[m_Combat_Menu_0.get()->m_iSelected]->m_SelectState = KSelectState::S_HOVER;

		//���� ZŰ �Է½� �ߵ� �Ǵ� Ŭ�� �ÿ� m_bSelect�� true �� �ȴ�.
		if (g_InputData.bMenu_SELECT)
		{
			m_Combat_Menu_0.get()->m_ButtonComponents[m_Combat_Menu_0.get()->m_iSelected]->m_SelectState = KSelectState::S_SELECTED;
		}
		//�� ��ư�� ����
		//�ο��.
		if (m_Combat_Menu_0.get()->m_ButtonComponents[0]->m_bSelect)
		{
			ActiveSelect();
			m_Combat_Menu_0.get()->m_ButtonComponents[0]->m_SelectState = KSelectState::S_DEFAULT;
			m_Combat_Menu_0.get()->m_ButtonComponents[0]->m_bSelect = false;

			m_text_dialog = L"�ص�����\n�����ġ��! ";
			m_bAttack = true;
		}
		//todo: ���� : �̱���
		if (m_Combat_Menu_0.get()->m_ButtonComponents[1]->m_bSelect)
		{
			//�ƹ� �۵���������
			m_Combat_Menu_0.get()->m_ButtonComponents[1]->m_SelectState = KSelectState::S_DEFAULT;
			m_Combat_Menu_0.get()->m_ButtonComponents[1]->m_bSelect = false;
		}
		//todo : ��������
		if (m_Combat_Menu_0.get()->m_ButtonComponents[2]->m_bSelect)
		{
			//����Ʈ
			m_text_dialog = L"������ �����ƴ�!";
			m_bGameEnd = true;;
			ActiveSelect();
			KSound* sound = g_SoundManager.LoadSound(L"../../data/sound/scene.mp3");
			sound->SoundPlay_Once();
			m_Combat_Menu_0.get()->m_ButtonComponents[2]->m_SelectState = KSelectState::S_DEFAULT;
			m_Combat_Menu_0.get()->m_ButtonComponents[2]->m_bSelect = false;

		}
	}

	//���ݹߵ�
	if (m_bAttack)
	{
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 4.0f)
		{
			KSound* attack_sound = g_SoundManager.LoadSound(L"../../data/sound/kick.mp3");
			attack_sound->SoundPlay_Once();
			m_Combat.m_mypoke.m_bAttackMove = true;
			//���� ������
			float random = randstep(0.5f, 1.0f);
			float damage = 50.0f * random;
			m_Combat.m_enemypoke.m_pinfo->DecHP(static_cast<int>(damage));
			m_bAttack = false;
			m_bAttack_End = true;
			g_SceneManager.m_Timer = 0.0f;
		}
	}
	//���� ����
	if (m_bAttack_End)
	{
		m_text_dialog = L"�����\n���� ��ġ��!";
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 4.0f)
		{
			KSound* attack_sound = g_SoundManager.LoadSound(L"../../data/sound/kick.mp3");
			attack_sound->SoundPlay_Once();
			m_Combat.m_enemypoke.m_bAnimation = true;
			float random = randstep(0.5f, 1.0f);
			float damage = 30.0f * random;
			m_Combat.m_mypoke.m_pinfo->DecHP(static_cast<int>(damage));
			m_Event_Intro_End = true;
			m_bAttack_End = false;
			g_SceneManager.m_Timer = 0.0f;
		}
	}

	//����� hp�� 0���� �۴ٸ�
	if (m_Combat.m_enemypoke.m_pinfo->hp <= 0)
	{
		m_text_dialog = L"����� �����ƴ�!";
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
	//�ص����� hp�� 0���� �۴ٸ�
	if (m_Combat.m_mypoke.m_pinfo->hp <= 0)
	{
		m_text_dialog = L"�ص��̴� ������ ����������!";
		m_Combat.m_mypoke.m_bVisibility = false;
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
			return true;
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

	//��ȭâ�ؽ�Ʈ : ������ ������ �־���ϱ� ������ ���߿� ������
	RECT  rt = { 25, 15 , g_rtClient.right, g_rtClient.bottom};
	g_Write->RenderText_Sequence(rt, m_text_dialog,
		D2D1::ColorF(0.2f, 0.2f, 0.3f, 1));

	//�޴�
	if (m_bMenu)
	{
		rt = { 320, g_rtClient.bottom -100, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, L"�ο��",
			D2D1::ColorF(0.5f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
		rt = { rt.left + 130,rt.top,rt.right,rt.bottom };
		g_Write->RenderText(rt, L"����",
			D2D1::ColorF(0.2f, 0.2f, 0.2f, 1), g_Write->m_pTextGame25);
		rt = { rt.left + 100,rt.top,rt.right,rt.bottom };
		g_Write->RenderText(rt, L"��������",
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
