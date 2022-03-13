#include "KSpriteEffect.h"
bool KSpriteEffect::Init(ID3D11DeviceContext* context, std::wstring vs, std::wstring ps, std::wstring tex, std::wstring mask)
{
	m_pContext = context;
	m_Current_Index=0;
	m_Timer=0.0f;
	m_bEnd = false;
	m_Color = { 1,1,1,1 };
	m_cbData.vLightDir = m_Color;
	K2DAsset::CreateObject_Mask(vs,ps,tex,mask);
	return true;
}

bool KSpriteEffect::Frame()
{
	if (m_bEnd)
	{
		Reset();
		return false;
	}
	else
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
		
			/*SetRectDraw({ 0,0,
				m_pSprite->m_anim_array[m_Current_Index].right,
				m_pSprite->m_anim_array[m_Current_Index].bottom });*/
			AddPosition(KVector2(0, 0));
			if (m_Current_Index == m_pSprite->m_anim_array.size()-1)
			{
				m_bEnd = true;
			}
		}
		m_cbData.vLightDir= m_Color;
	}
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

