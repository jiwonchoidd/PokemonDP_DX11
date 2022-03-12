#pragma once
#include "KBoxObj.h"
class KSkyBox : public KBoxObj
{
public:
	KMatrix	m_matSkyWorld;
public:
	void SetMatrix(KMatrix* pMatWorld, KMatrix* pMatView, KMatrix* pMatProj);
	bool Init(std::wstring shader, std::wstring tex = nullptr);
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
public:
	KSkyBox();
	~KSkyBox();
};