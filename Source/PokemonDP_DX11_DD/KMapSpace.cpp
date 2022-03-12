#include "KMapSpace.h"
#include "KSceneManager.h"
#include "KState.h"
#include "ImGuiManager.h"
bool KMapSpace::Init(ID3D11DeviceContext* context, KVector2 offset, float width, float height)
{
	m_Player = g_SceneManager.m_Player;
	KQuadTree::Init(context, offset , width, height);
	return true;
}

bool KMapSpace::Frame()
{
	if (g_InputData.bDebugRender)
	{
		m_bDebugRender = !m_bDebugRender;
	}

	//�÷��̾��� ��ġ�� ã�� �ش��ϴ� ��带 ��ȯ�Ѵ�,
	if (m_Player != nullptr)
	{
		KNode* pNode = FindLeafNode(m_Player->m_pos);
		if (pNode != nullptr)
		{
			if (pNode->m_data != NULL)
			{
				// ����, ������, �Ʒ���, ����
				m_Player->m_blockstate = pNode->m_data;
			}
			else
			{
				m_Player->m_blockstate = 0;
			}
		}
		if(ImGui::Begin("map node"))
		{
			ImGui::Text(u8"�ش� ��� ���� %d %d", pNode->m_index, pNode->m_data);
		}
		ImGui::End();
	}
	KObject::Frame();
	return true;
}
bool KMapSpace::Render(ID3D11DeviceContext* context)
{
	if (m_bDebugRender)
	{

		KQuadTree::Render(context);
	}
	return true;
}
void KMapSpace::HitOverlap(KCollider* pObj, DWORD dwState)
{
}

//�÷��̾� ��ġ
void KMapSpace::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
	if (m_Player == nullptr)
	{
		if (pObj->m_Name == L"Player0")
		{
			m_Player = pObj;
		}
	}
}

KMapSpace::KMapSpace()
{
	m_Player = nullptr;
	m_bDebugRender = false;
}

KMapSpace::~KMapSpace()
{
}
