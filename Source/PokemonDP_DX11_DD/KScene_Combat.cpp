#include "KScene_Combat.h"
#include "KSceneManager.h"
#include "KCombat.h"
#include "KUI.h"
#include "KWrite.h"
bool KScene_Combat::Load(std::wstring file)
{
#pragma region ����� �� ����
	// ���
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
	dialog_background->SetPosition(KVector2(g_rtClient.right / 2, g_rtClient.bottom-70));
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

	KUIModel* mystep = g_UIModelManager.GetPtr(L"combat_step")->Clone();
	mystep->SetRectDraw({ 0,0,128 * 4, 40 * 4 });
	mystep->SetPosition(KVector2(200, g_rtClient.bottom-150));
	mystep->UpdateData();
	KUIModel* enemystep = g_UIModelManager.GetPtr(L"combat_step")->Clone();
	enemystep->SetPosition(KVector2(g_rtClient.right-200, g_rtClient.bottom / 2));
	enemystep->UpdateData();
	//����
	m_UIObj.push_back(std::shared_ptr<KObject>(mystep));
	m_UIObj.push_back(std::shared_ptr<KObject>(enemystep));
	m_UIObj.push_back(std::shared_ptr<KObject>(dialog_background));
	
#pragma endregion

	return true;
}

bool KScene_Combat::Init(ID3D11DeviceContext* context)
{
	//��ӵ� �� �ʱ�ȭ
	KScene::Init(context);

	m_text_dialog = L"���! �߻� ����� �����ؿԴ�!";
	//���� �� ������ Ÿ�� ����
	m_SceneID = S_COMBAT;
	std::shared_ptr<KCombat> combat;
	//combat->Init();
	return true;
}

bool KScene_Combat::Frame()
{
	//�÷��̾� �̵�
	g_SceneManager.m_Timer += g_fSecPerFrame;
	if (g_SceneManager.m_Timer >= 2)
	{
		m_text_dialog = L"����! �ص���!";
	}
	KScene::Frame();
	return true;
}

bool KScene_Combat::Render()
{

	KScene::Render();

	//��ȭâ�ؽ�Ʈ : ������ ������ �־���ϱ� ������ ���߿� ������
	RECT  rt = { 25, g_rtClient.bottom - 125 , g_rtClient.right, g_rtClient.bottom};
	g_Write->RenderText_Sequence(rt, m_text_dialog,
		D2D1::ColorF(0.2f, 0.2f, 0.3f, 1));
	return true;
}

bool KScene_Combat::Release()
{
	KScene::Release();
	return true;
}
