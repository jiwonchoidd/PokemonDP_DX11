#pragma once
#include "KObject.h"
class KPlaneObj : public KObject
{
public:
	bool Init(std::wstring vs , std::wstring ps , std::wstring tex =nullptr);
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
public:
	KPlaneObj();
	~KPlaneObj();
};

