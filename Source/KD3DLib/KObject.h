#pragma once
#include "KShaderManager.h"
#include "KTextureManager.h"
struct PNCT_VERTEX
{
	KVector3 pos;
	KVector3 normal;
	KVector4 color;
	KVector2 tex;
	PNCT_VERTEX()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
		normal.x = 0.0f;
		normal.y = 0.0f;
		normal.z = 0.0f;
		tex.x = 0.0f;
		tex.y = 0.0f;
	}
};
struct CB_DATA
{
	KMatrix  matWorld;
	KMatrix  matView;
	KMatrix  matProj;
	KMatrix  matNormal;
	KVector4 vLightDir;
	KVector4 vValue; // 시간 값 xyzw
};
namespace wrl = Microsoft::WRL;
class KObject
{
//오브젝트 월드 행렬
public:
	KMatrix					m_matWorld;
	bool					m_bVisibility=true;
//상속관계 구현
public:
	KObject*				m_pParent = nullptr;
	ID3D11DeviceContext*	m_pContext = nullptr;
public:
	UINT					m_iNumIndex = 0;
	UINT					m_iVertexSize = 0;
	CB_DATA					m_cbData;
public:
	std::vector <PNCT_VERTEX>		m_VertexList;
	std::vector <DWORD>				m_IndexList;
public:
	KShader*		m_pVS = nullptr;
	KShader*		m_pPS = nullptr;
	KTexture*		m_pColorTex = nullptr;
	KTexture*		m_pMaskTex = nullptr;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;
public:
	wrl::ComPtr <ID3D11Buffer>	 	 m_pVertexBuffer;
	wrl::ComPtr <ID3D11Buffer>		 m_pIndexBuffer;
	wrl::ComPtr <ID3D11Buffer>		 m_pConstantBuffer;
	wrl::ComPtr <ID3D11InputLayout>  m_pVertexLayout;
public:
	virtual void		SetMatrix(KMatrix* pMatWorld,
		KMatrix* pMatView, KMatrix* pMatProj);
	virtual void		SetMatrix_Billboard(KMatrix* pMatWorld,
		KMatrix* pMatView, KMatrix* pMatProj);
	virtual bool		LoadShader(std::wstring vsFile, std::wstring psFile);
	virtual bool		LoadTexture(std::wstring filename, std::wstring mask = L"");
public:
	virtual bool		CheckVertexData();
	virtual bool		CheckIndexData();
	virtual HRESULT		CreateConstantBuffer();
	virtual HRESULT		CreateVertexBuffer();
	virtual HRESULT		CreateIndexBuffer();
	virtual HRESULT		CreateVertexLayout();
public:
	virtual bool		CreateObject(std::wstring vsFile, std::wstring psFile,
						std::wstring tex1= L"", std::wstring tex2=L"");
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		PreRender(ID3D11DeviceContext* pContext);
	virtual bool		Render(ID3D11DeviceContext* pContext);
	virtual bool		PostRender(ID3D11DeviceContext* pContext, UINT iNumIndex = 0);
	virtual bool		Release();
	KObject();
};

