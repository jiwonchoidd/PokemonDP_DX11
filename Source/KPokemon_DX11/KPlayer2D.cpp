#include "KPlayer2D.h"
#include "ImGuiManager.h"
#include "KSpriteManager.h"
#include <math.h>
bool KPlayer2D::Init(ID3D11DeviceContext* context, std::wstring vs, std::wstring ps, std::wstring tex, std::wstring mask)
{
	m_pContext = context;
	m_Speed = 5.0f;
	m_Name = L"Player0";

	//�ȴ� �ִϸ��̼� ���� �߶󳻱�
	KSprite* walk = new KSprite;
	walk->m_Name = L"Player_Walk";
	walk->m_anim_time = 0.0f;
	for (int resource = 0; resource < 12; resource++)
	{
		RECT rc = { 15 + (resource * 35),30,35,35 };
		walk->SetAnimArray(rc);
		//Ȧ����
		if (resource == 1 || resource == 4 || resource == 7 || resource == 10 || resource == 13)
		{
			RECT rc = { 15 + ((resource-1) * 35),30,35,35 };
			walk->SetAnimArray(rc);
		}
	}
	//
	g_SpriteManager.Load(walk);
	
	SetRectSource(walk->m_anim_array[8]);
	
	K2DAsset::CreateObject_Mask(vs, ps, tex, mask);
	return true;
}

bool KPlayer2D::Frame()
{
	KSprite* walk = g_SpriteManager.GetPtr(L"Player_Walk");
	KVector2 pos = {0,0};

	#pragma region Ű �Է� �̵� ó��
	if (g_InputData.bUpKey && m_bMove)
	{
		m_dir = { 0,1 };

		//8421 BCD �ڵ� 
		if (!(m_blockstate & 1))
		{
			walk->RunAnim(3.0f, 8, 11);
		}
		else
		{
			//�� ���� �浹������, 
			m_dir = { 0,0 };
			walk->m_AnimIndex = 8;
		}
	}
	else if (g_InputData.bDownKey && m_bMove)
	{
		m_dir = { 0,-1 };
		if (!(m_blockstate & 4))
		{
			walk->RunAnim(3.0f, 0, 3);
		}
		else
		{
			m_dir = { 0,0 };
			walk->m_AnimIndex = 0;
		}
	}
	else if (g_InputData.bLeftKey && m_bMove)
	{
		m_dir = { -1,0 };
		if (!(m_blockstate & 8))
		{
			walk->RunAnim(3.0f, 12, 15);
		}
		else
		{
			m_dir = { 0,0 };
			walk->m_AnimIndex = 12;
		}
	}
	else if (g_InputData.bRightKey && m_bMove)
	{
		m_dir = { 1,0 };
		if (!(m_blockstate & 2))
		{
			walk->RunAnim(3.0f, 4, 7);
		}
		else
		{
			m_dir = { 0,0 };
			walk->m_AnimIndex = 4;
		}
	}
#pragma endregion
	
	//Ű �Է��� ������
	else
	{
		if (m_dir == KVector2{ 0,1 })
		{
			walk->m_AnimIndex = 8;
		}
		if (m_dir == KVector2{ 0,-1 })
		{
			walk->m_AnimIndex = 0;
		}
		if (m_dir == KVector2{ -1,0 })
		{
			walk->m_AnimIndex = 12;
		}
		if (m_dir == KVector2{ 1,0 })
		{
			walk->m_AnimIndex = 4;
		}
		//�ݿø����� ���ö����� �̵��ϰ� ����
		m_dir = { 0,0 };
	}

	pos = m_dir * m_Speed * g_fSecPerFrame;
	AddPosition(pos);

	return true;
}
bool KPlayer2D::Render(ID3D11DeviceContext* pContext)
{
	KSprite* walk = g_SpriteManager.GetPtr(L"Player_Walk");
	//m_AnimIndex �迭�� ����� ��ǥ�� ���
	SetRectSource(walk->m_anim_array[walk->m_AnimIndex]);

	//�÷��̾� �����
	if (ImGui::Begin(u8"�÷��̾� �����"))
	{
		ImGui::Text("m_pos %f, %f", m_pos.x, m_pos.y);
		ImGui::Text("rt_coll %d, %d", (int)m_rtColl.max.x, (int)m_rtColl.max.y);
		ImGui::Text("rt_size %d, %d", (int)m_rtSize.width, (int)m_rtSize.height);
		ImGui::Text("matrix %d, %d", (int)m_matWorld._41, (int)m_matWorld._42);
		ImGui::Text("blockstae %d, ", m_blockstate);
	}
	ImGui::End();

	KObject::Render(pContext);
	return true;
}

bool KPlayer2D::AutoMove(KVector2 move)
{
	KSprite* walk = g_SpriteManager.GetPtr(L"Player_Walk");
	KVector2 pos = { 0,0 };

	m_dir = move;
	if (m_dir == KVector2( 0,-1 ))
	{
		walk->RunAnim(3.0f, 0, 3);
	}
	else if (m_dir == KVector2(-1, 0))
	{
		walk->RunAnim(3.0f, 12, 15);
	}
	else if (m_dir == KVector2(1, 0))
	{
		walk->RunAnim(3.0f, 4, 7);
	}
	else if (m_dir == KVector2(0, 1))
	{
		walk->RunAnim(3.0f, 8, 11);;
	}
	pos = m_dir * m_Speed * g_fSecPerFrame;
	AddPosition(pos);
	return true;
}

void KPlayer2D::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
	//���� ������Ʈ�� ��� ������Ʈ�� Ÿ���� ����
	
}

void KPlayer2D::SelectOverlap(KCollider* pObj, DWORD dwState)
{
}


KPlayer2D::KPlayer2D()
{
	m_Speed = 0.0f;
	m_pre_pos = {0,0};
	m_bMove = true;
}

KPlayer2D::~KPlayer2D()
{
}
