#include "KScene_Game_1.h"
#include "KSceneManager.h"
#include "KUI.h"
#include "KWrite.h"
void KScene_Game_1::ActiveMenu()
{
	g_SceneManager.m_Player->m_bMove = !g_SceneManager.m_Player->m_bMove;
	m_bMenu = !m_bMenu;
	m_Menu.get()->m_bVisibility = !m_Menu.get()->m_bVisibility;
	for (auto list : m_Menu.get()->m_Components)
	{
		list->m_bVisibility = !list->m_bVisibility;
	}
	KSound* sound = g_SoundManager.LoadSound(L"../../data/sound/menu_open.mp3");
	sound->SoundPlay_Once();
}

bool KScene_Game_1::Load(std::wstring file)
{
	#pragma region ����� �� ����
	//��ü ���̵� �ƿ� �̹���-------------------
	std::shared_ptr<KImage> fade_background(new KImage);
	fade_background->m_Name = L"fade_background";
	fade_background->SetRectDraw({ 0, 0, g_rtClient.right, g_rtClient.bottom });
	fade_background->SetPosition(KVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	fade_background->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	fade_background->m_rtOffset = { 0, 0, 0, 0 };
	if (!fade_background->Init(m_pContext,
		L"../../data/shader/VSPS_UI_Alpha.txt",
		L"../../data/shader/VSPS_UI_Alpha.txt",
		L"",
		L""))
	{
		return false;
	}
	fade_background->m_fAlpha = 1.0f;
	fade_background->m_bFadeOut = true;
	g_UIModelManager.m_list.insert(std::make_pair(L"fade_background", fade_background));

	//�޴� ���ȭ��-------------------
	std::shared_ptr<KImage> menu_background(new KImage);
	menu_background->m_Name = L"menu_background";
	menu_background->SetRectDraw({ 0, 0, g_rtClient.right / 3, (g_rtClient.bottom / 2) + 50 });
	menu_background->SetPosition(KVector2(g_rtClient.right / 1.2f, g_rtClient.bottom / 3.5f));
	menu_background->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	menu_background->m_rtOffset = { 20, 20, 20, 20 };
	if (!menu_background->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/menu_background.png",
		L""))
	{
		return false;
	}
	g_UIModelManager.m_list.insert(std::make_pair(L"menu_background", menu_background));

	//�޴� ������-------------------
	std::shared_ptr<KImage> menu_icon(new KImage);
	menu_icon->m_Name = L"menu_icon";
	menu_icon->SetRectDraw({ 0, 0, 50, 50 });
	menu_icon->SetPosition(KVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	menu_icon->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
	menu_icon->m_rtOffset = { 0, 0, 0, 0 };
	if (!menu_icon->Init(m_pContext,
		L"../../data/shader/VS_UI_0.txt",
		L"../../data/shader/PS_UI_0.txt",
		L"../../data/texture/menu_bag.png",
		L""))
	{
		return false;
	}
	g_UIModelManager.m_list.insert(std::make_pair(L"menu_icon", menu_icon));

	//�޴� ��ư-------------------
	std::shared_ptr<KButton> btn(new KButton);
	btn->m_Name = L"menu_button";
	btn->m_rtOffset = { 40, 40, 40, 40 };
	btn->SetRectDraw({ 0, 0, (g_rtClient.right / 3) - 20, ((g_rtClient.bottom / 2) / 4) - 6 });
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
	g_UIModelManager.m_list.insert(std::make_pair(L"menu_button", btn));

	//----------------------- �޴� ��

#pragma endregion

	#pragma region �ε��� �𵨷� �޴� ����
	KUIModel* background = g_UIModelManager.GetPtr(L"menu_background")->Clone();
	background->m_Name = L"menu_background_1";
	background->UpdateData();

	KUIModel* button1 = g_UIModelManager.GetPtr(L"menu_button")->Clone();
	button1->m_Name = L"menu_button_1";
	button1->SetPosition(KVector2(background->m_pos.x, background->m_pos.y - 120));
	button1->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button1->UpdateData();
	KUIModel* button2 = g_UIModelManager.GetPtr(L"menu_button")->Clone();
	button2->m_Name = L"menu_button_2";
	float offset = 60.0f;
	button2->SetPosition(KVector2(background->m_pos.x, button1->m_pos.y + offset));
	button2->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button2->UpdateData();
	KUIModel* button3 = g_UIModelManager.GetPtr(L"menu_button")->Clone();
	button3->m_Name = L"menu_button_3";
	button3->SetPosition(KVector2(background->m_pos.x, button2->m_pos.y + offset));
	button3->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button3->UpdateData();
	KUIModel* button4 = g_UIModelManager.GetPtr(L"menu_button")->Clone();
	button4->m_Name = L"menu_button_4";
	button4->SetPosition(KVector2(background->m_pos.x, button3->m_pos.y + offset));
	button4->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button4->UpdateData();
	KUIModel* button5 = g_UIModelManager.GetPtr(L"menu_button")->Clone();
	button5->m_Name = L"menu_button_5";
	button5->SetPosition(KVector2(background->m_pos.x, button4->m_pos.y + offset));
	button5->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
	button5->UpdateData();

	KUIModel* icon1 = g_UIModelManager.GetPtr(L"menu_icon")->Clone();
	icon1->m_Name = L"menu_icon_1";
	icon1->SetPosition(KVector2(button1->m_pos.x - 115.0f, button1->m_pos.y));
	icon1->UpdateData();
	KUIModel* icon2 = g_UIModelManager.GetPtr(L"menu_icon")->Clone();
	icon2->m_Name = L"menu_icon_2";
	icon2->m_pColorTex = g_TextureMananger.Load(L"../../data/texture/menu_user.png");
	icon2->SetPosition(KVector2(button1->m_pos.x - 115.0f, button2->m_pos.y));
	icon2->UpdateData();
	KUIModel* icon3 = g_UIModelManager.GetPtr(L"menu_icon")->Clone();
	icon3->m_Name = L"menu_icon_3";
	icon3->m_pColorTex = g_TextureMananger.Load(L"../../data/texture/menu_report.png");
	icon3->SetPosition(KVector2(button1->m_pos.x - 115.0f, button3->m_pos.y));
	icon3->UpdateData();
	KUIModel* icon4 = g_UIModelManager.GetPtr(L"menu_icon")->Clone();
	icon4->m_Name = L"menu_icon_4";
	icon4->m_pColorTex = g_TextureMananger.Load(L"../../data/texture/menu_setting.png");
	icon4->SetPosition(KVector2(button1->m_pos.x - 115.0f, button4->m_pos.y));
	icon4->UpdateData();
	KUIModel* icon5 = g_UIModelManager.GetPtr(L"menu_icon")->Clone();
	icon5->m_Name = L"menu_icon_5";
	icon5->m_pColorTex = g_TextureMananger.Load(L"../../data/texture/menu_close.png");
	icon5->SetPosition(KVector2(button1->m_pos.x - 115.0f, button5->m_pos.y));
	icon5->UpdateData();

	button1->m_pParent = icon1;
	button2->m_pParent = icon2;
	button3->m_pParent = icon3;
	button4->m_pParent = icon4;
	button5->m_pParent = icon5;

	std::shared_ptr<KUIModelComposite> compositeobj(new KUIModelComposite);
	compositeobj->m_Name = L"Menu";
	compositeobj->Add(background);
	compositeobj->Add(button1);
	compositeobj->Add(button2);
	compositeobj->Add(button3);
	compositeobj->Add(button4);
	compositeobj->Add(button5);
	compositeobj->Add(icon1);
	compositeobj->Add(icon2);
	compositeobj->Add(icon3);
	compositeobj->Add(icon4);
	compositeobj->Add(icon5);

#pragma endregion

	//�� Ŭ�������� ����ϱ����� �ɹ������ͷ� �޾ƿ�
	m_Menu = compositeobj;

	//���۽ÿ� �޴��� ������ �ʱ� ���� ��� ������Ʈ invisibility
	m_Menu.get()->m_bVisibility = false;
	for (auto list : m_Menu.get()->m_Components)
	{
		list->m_bVisibility = false;
	}

	//�� ������ ������Ʈ �ε�---------------------------------------
	m_UIObj.push_back(std::shared_ptr<KObject>(compositeobj));
	KUIModel* fadeimg = g_UIModelManager.GetPtr(L"fade_background")->Clone();
	m_UIObj.push_back(std::shared_ptr<KObject>(fadeimg));

	//����Ǵ� ������ �ش� ������ �ƴ϶�� �ٲ��ش�.
	if (g_SceneManager.m_BGM->m_name != L"Twinleaf Town (Day)")
	{
		g_SceneManager.m_BGM->SoundStop();
		g_SceneManager.m_BGM = g_SoundManager.LoadSound(L"../../data/sound/bgm/Twinleaf Town (Day).wav");
		g_SceneManager.m_BGM->SoundPlay(true);
	}
	
	//�÷��̾� �ʱ� ��ġ
	D3DKMatrixTranslation(&g_SceneManager.m_Player->m_matWorld, 8.5f, -15.0f, -1.0f);
	g_SceneManager.m_Player->m_dir = { 0,-1 };

	//�� �ε�---------------------------
	//OBJ ���� ��
	KMatrix s, r, t;
	D3DKMatrixIdentity(&s);
	D3DKMatrixScaling(&s, 2.0f, 2.0f, 1.5f);
	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<KObjObject> map3D_1 = std::make_shared<KObjObject>();
		D3DKMatrixIdentity(&r);
		D3DKMatrixIdentity(&t);
		if (!map3D_1.get()->Init(m_pContext,
			L"../../data/shader/VS_0.txt",
			L"../../data/shader/PS_0.txt",
			L"../../data/model/map_01tex.png",
			L"../../data/model/map1.obj"))
		{
			return false;
		}
		if (i == 0)
		{
			D3DKMatrixTranslation(&t, 0.0f, 0.0f, 0.0f);
			D3DKMatrixRotationZ(&r, 0.0f);
		}
		if (i == 1)
		{
			D3DKMatrixTranslation(&t, 64.0f, 0.0f, 0.0f);
		}
		if (i == 2)
		{
			D3DKMatrixTranslation(&t, -64.0f, 0.0f, 0.0f);
		}
		map3D_1.get()->m_matWorld = map3D_1.get()->m_matWorld * s * t * r;
		m_MapObj.push_back(std::shared_ptr<KObject>(map3D_1));
	}

	//Ʈ���� 1 : ������ ���� Ʈ����----------------
	//Ʈ���� 2 : ���� Ʈ����

	std::shared_ptr<KTriggerCollider> combat_trigger = std::make_shared<KTriggerCollider>();
	combat_trigger.get()->Init(m_pContext, KVector2(0.0f, 2.5f), {0,0,3,3});
	m_Trigger_Combat = combat_trigger.get();
	m_Trigger_Combat->m_matWorld = m_Trigger_Combat->m_matWorld * s;
	m_MapObj.push_back(std::shared_ptr<KObject>(combat_trigger));
	std::shared_ptr<KTriggerCollider> enter_trigger = std::make_shared<KTriggerCollider>();
	enter_trigger.get()->Init(m_pContext, KVector2(8.7f, -12.9f), { 0,0,1,1 });
	m_Trigger_Home = enter_trigger.get();
	m_Trigger_Home->m_matWorld = m_Trigger_Home->m_matWorld * s;
	m_MapObj.push_back(std::shared_ptr<KObject>(enter_trigger));

	//�ǹ� ��ġ------------------------------
	#pragma region �ǹ� ��ġ �ݺ���
	for (int build = 0; build < 4; build++)
	{
		KMatrix s, r, t;
		std::shared_ptr<KObjObject> building = std::make_shared<KObjObject>();;
		if (!building.get()->Init(m_pContext,
			L"../../data/shader/VS_0.txt",
			L"../../data/shader/PS_0.txt",
			L"../../data/model/house1tex.jpg",
			L"../../data/model/house_01.obj"))
		{
			return false;
		}
		D3DKMatrixIdentity(&s);
		D3DKMatrixIdentity(&r);
		D3DKMatrixIdentity(&t);
		D3DKMatrixScaling(&s, 3.5f, 3.5f, 3.5f);
		D3DKMatrixRotationX(&r, -1 * (3.14 / 2));

		if (build == 0)
		{
			D3DKMatrixTranslation(&t, -11.0f, 17.0f, 0.0f);
		}
		if (build == 1)
		{
			D3DKMatrixTranslation(&t, 11.0f, 17.0f, 0.0f);
		}
		if (build == 2)
		{
			D3DKMatrixTranslation(&t, -11.0f, -7.0f, 0.0f);
		}
		if (build == 3)
		{
			D3DKMatrixTranslation(&t, 11.0f, -7.0f, 0.0f);
		}
		building.get()->m_matWorld = building.get()->m_matWorld * s * r *t;
		m_MapObj.push_back(std::shared_ptr<KObject>(building));
	}
#pragma endregion
	//Ǯ ��ġ
	std::shared_ptr<KImage> map_grass = std::make_shared<KImage>();
	map_grass.get()->SetRectDraw({ 0, 0, 32, 28 });
	map_grass.get()->SetPosition(KVector2(0, 0));
	if (!map_grass.get()->Init(m_pContext,
		L"../../data/shader/VS_2D_Map.txt", L"../../data/shader/PS_2D_Map.txt",
		L"../../data/texture/DS DSi - Pokemon Diamond Pearl - Players House.png", L""))
	{
		return false;
	}

	//��ƮƮ��-------------------------------
	std::shared_ptr<KMapSpace> map_space = std::make_shared<KMapSpace>();
	map_space.get()->Init(m_pContext, KVector2(0, 0),
		32*2,32*2);
	map_space.get()->LoadLeafData(L"../../data/map/map_1.txt");
	m_MapObj.push_back(std::shared_ptr<KObject>(map_space));
	return true;

}

bool KScene_Game_1::Init(ID3D11DeviceContext* context)
{
	//��ӵ� �� �ʱ�ȭ
	KScene::Init(context);
	//���� �� ������ Ÿ�� ����
	m_SceneID = S_GAME_1;

	//ī�޶� �ʱ�ȭ
	m_Camera.Init();
	m_Camera.CreateViewMatrix(KVector3(0, 0, -28), KVector3(0, 0, 0));
	m_Camera.CreateProjMatrix(1.0f, 1000.0f, XM_PI * 0.18f, (float)g_rtClient.right / (float)g_rtClient.bottom);
	return true;
}

bool KScene_Game_1::Frame()
{
	g_SceneManager.m_BGM->Frame();
	//�÷��̾� �̵�
	g_SceneManager.m_Player->Frame();
	//ī�޶� �̵�
	m_Camera.Follow2DPos(&g_SceneManager.m_Player->m_pos, {0, 20});
	//������ ���̵�
	if (g_InputData.bAKey)
	{
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 1.0f)
		{
			g_SceneManager.m_BGM->SoundStop();
			g_SceneManager.m_BGM = g_SoundManager.LoadSound(L"../../data/sound/bgm/Battle! (Wild Pokemon).wav");
			g_SceneManager.m_BGM->SoundPlay(true);
			g_SceneManager.m_Timer = 0.0f;
			g_SceneManager.SetScene(3);
			return true;
		}
	}
	//������ ���� Ʈ����
	if (m_Trigger_Home->m_bisTrigger)
	{
		//m_Fade->m_bFadeIn = true;
		g_SceneManager.m_Player->m_bMove = false;
		g_SceneManager.m_Player->AutoMove(KVector2(0, 1));
		g_SceneManager.m_Timer += g_fSecPerFrame;
		if (g_SceneManager.m_Timer > 1.0f)
		{
			KSound* sound = g_SoundManager.LoadSound(L"../../data/sound/scene.mp3");
			sound->SoundPlay_Once();
			g_SceneManager.m_Timer = 0.0f;
			g_SceneManager.m_Player->m_bMove = true;
			g_SceneManager.SetScene(1);
			return true;
		}
	}

	#pragma region �޴� ����
	//�޴� ���� ĳ���� �̵� �Ұ�
	if (g_InputData.bMenu)
	{
		ActiveMenu();
	}

	if (m_bMenu)
	{
		int button_count = m_Menu.get()->m_ButtonComponents.size();

		//���Ʒ��� ��ư ����Ʈ ����
		if (g_InputData.bMenu_UP)
		{
			if (m_Menu.get()->m_iSelected > 0)
				m_Menu.get()->m_iSelected = m_Menu.get()->m_iSelected - 1;
		}
		if (g_InputData.bMenu_DOWN)
		{
			if (m_Menu.get()->m_iSelected < button_count - 1)
				m_Menu.get()->m_iSelected = m_Menu.get()->m_iSelected + 1;
		}
		//�ش� ��ư ȣ�� ���·� ��ȯ
		m_Menu.get()->m_ButtonComponents[m_Menu.get()->m_iSelected]->m_SelectState = KSelectState::S_HOVER;

		for (int i = 0; i < button_count; i++)
		{
			static_cast<KImage*>(m_Menu.get()->m_ButtonComponents[i]->m_pParent)->m_fAlpha = 0.25f;
		}
		static_cast<KImage*>(m_Menu.get()->m_ButtonComponents[m_Menu.get()->m_iSelected]->m_pParent)->m_fAlpha = 1.0f;

		//���� ZŰ �Է½� �ߵ� �Ǵ� Ŭ�� �ÿ� m_bSelect�� true �� �ȴ�.
		if (g_InputData.bMenu_SELECT)
		{
			m_Menu.get()->m_ButtonComponents[m_Menu.get()->m_iSelected]->m_SelectState = KSelectState::S_SELECTED;
		}
		//�� ��ư�� ����
		if (m_Menu.get()->m_ButtonComponents[0]->m_bSelect)
		{
			//����
			ActiveMenu();
			m_Menu.get()->m_ButtonComponents[0]->m_SelectState = KSelectState::S_DEFAULT;
			m_Menu.get()->m_ButtonComponents[0]->m_bSelect = false;
		}
		if (m_Menu.get()->m_ButtonComponents[1]->m_bSelect)
		{
			//������
			ActiveMenu();
			m_Menu.get()->m_ButtonComponents[1]->m_SelectState = KSelectState::S_DEFAULT;
			m_Menu.get()->m_ButtonComponents[1]->m_bSelect = false;
		}
		if (m_Menu.get()->m_ButtonComponents[2]->m_bSelect)
		{
			//����Ʈ
			ActiveMenu();
			m_Menu.get()->m_ButtonComponents[2]->m_SelectState = KSelectState::S_DEFAULT;
			m_Menu.get()->m_ButtonComponents[2]->m_bSelect = false;

		}
		if (m_Menu.get()->m_ButtonComponents[3]->m_bSelect)
		{
			//����
			ActiveMenu();
			m_Menu.get()->m_ButtonComponents[3]->m_SelectState = KSelectState::S_DEFAULT;
			m_Menu.get()->m_ButtonComponents[3]->m_bSelect = false;
		}
		if (m_Menu.get()->m_ButtonComponents[4]->m_bSelect)
		{
			//�ݴ´�
			ActiveMenu();
			m_Menu.get()->m_ButtonComponents[4]->m_SelectState = KSelectState::S_DEFAULT;
			m_Menu.get()->m_ButtonComponents[4]->m_bSelect = false;
		}
		if (g_InputData.bExit)
		{
			ActiveMenu();
		}
	}
#pragma endregion
	KScene::Frame();
	return true;
}

bool KScene_Game_1::Render()
{
	//��
	for (int map = 0; map < m_MapObj.size(); map++)
	{
		m_MapObj[map]->SetMatrix(&m_MapObj[map]->m_matWorld,
			&m_Camera.m_matView, &m_Camera.m_matProj);
	}
	//�÷��̾� ������
	// Y�� ȸ������� _11, _13, _31, _33�� ��Ŀ� ȸ������ ����
	// ī�޶��� Y�� ȸ����İ��� �о ������� ����� X,Z���� ������
	// Y�� ȸ�� ������ ����� ����� �ִ�

	g_SceneManager.m_Player->SetMatrix_Billboard(&g_SceneManager.m_Player->m_matWorld, 
		&m_Camera.m_matView, &m_Camera.m_matProj);
	g_SceneManager.m_Player->Render(m_pContext);
	KScene::Render();

	//�޴� �ؽ�Ʈ
	if (m_bMenu)
	{
		RECT  rt = { g_rtClient.right - 235, 8, g_rtClient.right, g_rtClient.bottom };
		g_Write->RenderText(rt, L"����\n����\n����Ʈ\n����\n�ݴ´�",
			D2D1::ColorF(0.2f, 0.2f, 0.3f, 1), g_Write->m_pTextGame40_Space);
	}
	return true;
}

bool KScene_Game_1::Release()
{
	m_Camera.Release();
	KScene::Release();
	return true;
}
