#include "KNpc2D.h"
#include "ImGuiManager.h"

void	KNpc2D::SelectOverlap(KCollider* pObj, DWORD dwState)
{
	if (m_SelectState & S_HOVER)
	{
		INT K = 0;
	}
	if (m_SelectState & S_FOCUS)
	{
		INT K = 0;
	}
	if (m_SelectState & S_ACTIVE)
	{
		INT K = 0;
	}
	if (m_SelectState & S_SELECTED)
	{
		m_bSelect = true;
	}
}
bool KNpc2D::Init(ID3D11DeviceContext* context, std::wstring vs, std::wstring ps, std::wstring tex, std::wstring mask)
{
	m_pContext = context;
	K2DAsset::CreateObject_Mask(vs, ps, tex, mask);
	return true;
}

bool KNpc2D::Frame()
{
	AddPosition(KVector2(0, 0));

	//플레이어 디버거
	if (ImGui::Begin(u8"디버거"))
	{
		ImGui::Text("m_pos %d, %d", (int)m_pos.x, (int)m_pos.y);
		ImGui::Text("rt_coll %d, %d", (int)m_rtColl.max.x, (int)m_rtColl.max.y);
		ImGui::Text("rt_size %d, %d", (int)m_rtSize.width, (int)m_rtSize.height);
	}
	ImGui::End();
	return true;
}

void KNpc2D::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
	if (dwState == pObj->m_CollisonType)
	{
		int kkk = 0;
	}
}

KNpc2D::KNpc2D()
{
}

KNpc2D::~KNpc2D()
{
}
