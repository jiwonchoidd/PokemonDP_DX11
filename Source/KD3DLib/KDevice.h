#pragma once
#include "KStd.h"
class KDevice
{
public:
	ID3D11Device*			m_pd3dDevice;		// 디바이스 객체
	ID3D11DeviceContext*	m_pImmediateContext;// 디바이스 컨텍스트
	IDXGISwapChain*			m_pSwapChain;		// 스왑체인 객체
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰
	ID3D11DepthStencilView*	m_DepthStencilView;
	IDXGIFactory*			m_pGIFactory;		// DXGI 객체
	ID3D11ShaderResourceView* m_pTextureSRV;
public:
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	// 스왑체인 속성값
	D3D_DRIVER_TYPE         m_driverType;		// 디바이스 타입( 디폴트:하드웨어 가속 )
	D3D11_VIEWPORT			m_ViewPort;			// 뷰포트 
	D3D_DRIVER_TYPE			m_DriverType;		// 디바이스 타입
	D3D_FEATURE_LEVEL       m_FeatureLevel;		// DirectX의 기능수준
public:
	bool	SetDevice();
	//--------------------------------------------------------------------------------------
	// 디바이스 및 스왑체인 생성 : 
	// 1, CreateDevice()
	// 2, CreateGIFactory()
	// 3, CreateSwapChain()
	// 4, SetRenderTargetView()
	// 5, SetViewPort()
	//--------------------------------------------------------------------------------------
	HRESULT		CreateDeviceAndSwapChain();
	HRESULT		CreateGIFactory();
	HRESULT		SetRenderTargetView();
	HRESULT		SetDepthStencilView();
	HRESULT		SetViewPort();
	bool		CleanupDevice();
public:
	bool		ResizeDevice(UINT width, UINT height);

	#pragma region 테스트 박스
	//bool DrawTestBox(float angle, float x, float y, float z, KMatrix* w, KMatrix* v, KMatrix* p)
//{
//	namespace wrl = Microsoft::WRL;
//	HRESULT hr = S_OK;
//	struct Vertex
//	{
//		struct {
//			float x;
//			float y;
//			float z;
//		}pos;
//	};
//	const Vertex vertices[] =
//	{
//		{-1.0f,-1.0f,-1.0f},
//		{ 1.0f,-1.0f,-1.0f},
//		{-1.0f,1.0f,-1.0f},
//		{ 1.0f,1.0f,-1.0f},
//		{-1.0f,-1.0f,1.0f},
//		{ 1.0f,-1.0f,1.0f},
//		{-1.0f,1.0f,1.0f},
//		{ 1.0f,1.0f,1.0f},
//	};
//	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
//	D3D11_BUFFER_DESC bd;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.CPUAccessFlags = 0u;
//	bd.MiscFlags = 0u;
//	bd.ByteWidth = sizeof(vertices);
//	bd.StructureByteStride = sizeof(Vertex);

//	D3D11_SUBRESOURCE_DATA sd;
//	ZeroMemory(&sd,sizeof(D3D11_SUBRESOURCE_DATA));
//	sd.pSysMem = vertices;
//	hr=g_pd3dDevice->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf());
//	if (FAILED(hr)) return false;
//	const UINT stride = sizeof(Vertex);
//	const UINT offset = 0u;
//	//배열이 들어갈수있다.
//	m_pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

//	const unsigned short indices[] =
//	{
//		0,2,1, 2,3,1,
//		1,3,5, 3,7,5,
//		2,6,3, 3,6,7,
//		4,5,7, 4,7,6,
//		0,4,2, 2,4,6,
//		0,1,4, 1,5,4,
//	};
//	wrl::ComPtr<ID3D11Buffer>pIndexBuffer;
//	D3D11_BUFFER_DESC ibd = {};
//	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	ibd.Usage = D3D11_USAGE_DEFAULT;
//	ibd.CPUAccessFlags = 0u;
//	ibd.MiscFlags = 0u;
//	ibd.ByteWidth = sizeof(indices);
//	ibd.StructureByteStride = sizeof(unsigned short);
//	D3D11_SUBRESOURCE_DATA isd;
//	isd.pSysMem = indices;
//	hr = g_pd3dDevice->CreateBuffer(&ibd, &isd, pIndexBuffer.GetAddressOf());
//	if (FAILED(hr)) return false;

//	m_pImmediateContext->IASetIndexBuffer(pIndexBuffer.Get(),DXGI_FORMAT_R16_UINT,0);  

//	//상수버퍼
//	struct ConstantBuffer
//	{
//		KMatrix  matWorld;
//		KMatrix  matView;
//		KMatrix  matProj;
//	};
//	//VS 상수 버퍼
//	ConstantBuffer cb;
//	if (w == nullptr)
//	{
//		KMatrix d =
//			dx::XMMatrixRotationZ(angle) *
//			dx::XMMatrixRotationY(angle) *
//			dx::XMMatrixTranslation(x, y, z);
//		cb.matWorld =d.Transpose();
//	}
//	if (v != nullptr)
//	{
//		cb.matView = v->Transpose();
//	}
//	if (p != nullptr)
//	{
//		cb.matProj = p->Transpose();
//	}
//	wrl::ComPtr<ID3D11Buffer>pConstantBuffer;
//	D3D11_BUFFER_DESC cbd = {};
//	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbd.Usage = D3D11_USAGE_DYNAMIC;
//	cbd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
//	cbd.MiscFlags = 0u;
//	cbd.ByteWidth = sizeof(cb);
//	cbd.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA csd;
//	csd.pSysMem = &cb;
//	hr = g_pd3dDevice->CreateBuffer(&cbd, &csd, pConstantBuffer.GetAddressOf());
//	if (FAILED(hr)) return false;
//	//m_pImmediateContext->UpdateSubresource(pConstantBuffer.Get(), 0, NULL, &cb, 0, 0);
//	m_pImmediateContext->VSSetConstantBuffers(0,1,pConstantBuffer.GetAddressOf());

//	//PS 상수버퍼
//	struct ConstantBuffer2
//	{
//		struct
//		{
//			float r;
//			float g;
//			float b;
//			float a;
//		}face_colors[6];
//	};
//	const ConstantBuffer2 cb2 =
//	{
//		{
//			{0.5f,1.0f,0.0f},
//			{0.0f,0.5f,1.0f},
//			{1.0f,0.0f,0.5f},
//			{0.5f,0.5f,1.0f},
//			{0.5f,1.0f,0.5f},
//			{1.0f,0.5f,0.5f},
//		}
//	};
//	wrl::ComPtr<ID3D11Buffer>pConstantBuffer2;
//	D3D11_BUFFER_DESC cbd2 = {};
//	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbd2.Usage = D3D11_USAGE_DYNAMIC;
//	cbd2.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
//	cbd2.MiscFlags = 0u;
//	cbd2.ByteWidth = sizeof(cb2);
//	cbd2.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA csd2;
//	csd2.pSysMem = &cb2;
//	hr = g_pd3dDevice->CreateBuffer(&cbd2, &csd2, pConstantBuffer2.GetAddressOf());
//	if (FAILED(hr)) return false;
//	m_pImmediateContext->PSSetConstantBuffers(0, 1, pConstantBuffer2.GetAddressOf());

//	wrl::ComPtr<ID3DBlob> pBlob;

//	//1. 픽셀 셰이더 생성
//	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
//	hr=D3DReadFileToBlob(L"PixelShader.cso", pBlob.GetAddressOf());
//	if (FAILED(hr)) return false;
//	hr = g_pd3dDevice->CreatePixelShader(pBlob->GetBufferPointer(),
//		pBlob->GetBufferSize(), nullptr, pPixelShader.GetAddressOf());
//	if (FAILED(hr)) return false;

//	//2. 바인드 픽셀 셰이더
//	m_pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

//	//3. 버텍스 셰이더 생성
//	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
//	hr=D3DReadFileToBlob(L"VertexShader.cso", pBlob.GetAddressOf());
//	if (FAILED(hr)) return false;
//	hr = g_pd3dDevice->CreateVertexShader(pBlob->GetBufferPointer(),
//		pBlob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf());
//	if (FAILED(hr)) return false;

//	//4. 바인드 버텍스 셰이더
//	m_pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

//	//5. Input 버텍스 레이아웃 (2D 위치만)
//	wrl::ComPtr<ID3D11InputLayout> pInputLayout;

//	const D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
//	};
//	hr = g_pd3dDevice->CreateInputLayout(layout, _countof(layout),
//		pBlob->GetBufferPointer(),
//		pBlob->GetBufferSize(),
//		pInputLayout.GetAddressOf()
//	);
//	if (FAILED(hr)) return false;

//	//6. 바인드 버텍스 레이아웃
//	m_pImmediateContext->IASetInputLayout(pInputLayout.Get());

//	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


//	m_pImmediateContext->DrawIndexed((UINT)(std::size(indices)),0u,0u);
//	
//	return true;
//};
#pragma endregion
	KDevice();
};

