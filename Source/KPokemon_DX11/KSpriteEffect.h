#pragma once
#include "KSpriteManager.h"
#include "K2DAsset.h"
class KSpriteEffect : public K2DAsset
{
public:
	KSprite*    m_pSprite;
	int		    m_Current_Index;
	float	    m_Timer;
	float	    m_Change_Time;
    KVector4    m_Color;
    bool        m_bEnd;
public:
    bool Init(ID3D11DeviceContext* context, std::wstring vs,
        std::wstring ps, std::wstring tex = nullptr, std::wstring mask = nullptr);
    bool Frame()override;
    bool Render(ID3D11DeviceContext* pContext)override;
    bool Release()override;
public:
    void    Reset();
};

