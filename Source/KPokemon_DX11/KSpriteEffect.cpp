#include "KSpriteEffect.h"

bool KSpriteEffect::Init(ID3D11DeviceContext* context, std::wstring vs, std::wstring ps, std::wstring tex, std::wstring mask)
{
	m_pContext = context;
	m_Current_Index=0;
	m_Timer=0.0f;
	m_Color = { 1,1,1,1 };
	return true;
}

bool KSpriteEffect::Frame()
{
	m_Change_Time = m_pSprite->m_anim_time / m_pSprite->m_anim_array.size();
	m_Timer += g_fSecPerFrame;
	if (m_Timer >= m_Change_Time)
	{
		m_Current_Index++;
		if (m_Current_Index >= m_pSprite->m_anim_array.size())
		{
			m_Current_Index = 0;
		}
		m_Timer -= m_Change_Time;
		SetRectSource(m_pSprite->m_anim_array[m_Current_Index]);
		SetRectDraw({ 0,0,
			m_pSprite->m_anim_array[m_Current_Index].right,
			m_pSprite->m_anim_array[m_Current_Index].bottom });
	}
	m_cbData.vLightDir= m_Color;
	m_cbData.vValue= KVector4(g_fSecTimer, 0, 0, 1.0f);

	AddPosition({ 0,0 });
	return true;
}

bool KSpriteEffect::Render(ID3D11DeviceContext* pContext)
{
	KObject::Render(pContext);
	return true;
}

bool KSpriteEffect::Release()
{
	KObject::Release();
	return true;
}

void KSpriteEffect::Reset()
{
	m_Current_Index = 0;
	m_Timer = 0.0f;
}

void KSpriteEffect::ObjectOverlap(KCollider* pObj, DWORD dwState)
{
}

void KSpriteEffect::SelectOverlap(KCollider* pObj, DWORD dwState)
{
}
