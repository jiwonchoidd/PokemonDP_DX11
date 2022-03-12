#include "KDevice.h"
#include "ImGui/imgui_impl_dx11.h"
ID3D11Device* g_pd3dDevice = nullptr;		// 디바이스 객체
bool	KDevice::SetDevice()
{
	HRESULT hr;
	if (FAILED(CreateGIFactory()))
	{
		return false;
	}
	if (FAILED(CreateDeviceAndSwapChain()))
	{
		return false;
	}
	if (FAILED(SetRenderTargetView()))
	{
		return false;
	}
	if (FAILED(SetDepthStencilView()))
	{
		return false;
	}
	if (FAILED(SetViewPort()))
	{
		return false;
	}
	return true;
}
HRESULT KDevice::CreateGIFactory()
{
	HRESULT hr = S_OK;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory),
		(void**)(&m_pGIFactory));
	return hr;
}

HRESULT KDevice::CreateDeviceAndSwapChain()
{
	HRESULT hr = S_OK;
	if (m_pGIFactory == NULL) return S_FALSE;
	//D2DWrite 사용하려면 플래그해줘야함
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_12_0,
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);
	m_DriverType = driverTypes[0];

	ZeroMemory(&m_SwapChainDesc, sizeof(m_SwapChainDesc));
	m_SwapChainDesc.BufferCount = 1;
	m_SwapChainDesc.BufferDesc.Width = g_rtClient.right;
	m_SwapChainDesc.BufferDesc.Height = g_rtClient.bottom;
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_SwapChainDesc.OutputWindow = g_hWnd;
	//뎁스스텐실 count랑 스왑체인 count랑 맞춰야함,
	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.SampleDesc.Quality = 0;
	m_SwapChainDesc.Windowed = true;
	//m_SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	//백버퍼에 가장 적합한 디스플레이 모드로 자동 전환함
	m_SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		m_DriverType,
		NULL,
		createDeviceFlags,
		featureLevels,
		numFeatureLevels,
		D3D11_SDK_VERSION,
		&m_SwapChainDesc,
		&m_pSwapChain,
		&m_pd3dDevice,
		&m_FeatureLevel,
		&m_pImmediateContext);

	g_pd3dDevice = m_pd3dDevice;
	return hr;
}

HRESULT KDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	ID3D11Texture2D* pBackBuffer; // 백버퍼
	if (FAILED(hr = m_pSwapChain->GetBuffer(
		0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer), hr))
	{
		return hr;
	}

	hr=m_pd3dDevice->CreateRenderTargetView(
		pBackBuffer, NULL, 
		&m_pRenderTargetView);
	if (FAILED(hr))
	{
		pBackBuffer->Release();
		return hr;
	}
	pBackBuffer->Release();	
	return hr;
}

HRESULT KDevice::SetDepthStencilView()
{
	// 1)텍스처 생성 : 깊이,스텐실 값을 저장하는 버퍼용
	HRESULT hr = S_OK;
	m_pSwapChain->GetDesc(&m_SwapChainDesc);
	ID3D11Texture2D* pDSTexture = nullptr;
	D3D11_TEXTURE2D_DESC DescDepth;
	DescDepth.Width = m_SwapChainDesc.BufferDesc.Width;
	DescDepth.Height = m_SwapChainDesc.BufferDesc.Height;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	//RGB는 텍스쳐 리소스 D24는 뎁스
	DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&DescDepth, nullptr, &pDSTexture);
	if (FAILED(hr))
	{
		return hr;
	}
	if (pDSTexture == nullptr)
	{
		return E_FAIL;
	}
	//뎁스 스텐실 뷰 만듬
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = g_pd3dDevice->CreateDepthStencilView(pDSTexture, &descDSV,
		&m_DepthStencilView);
	if (FAILED(hr))
	{
		return hr;
	}
	return hr;
}

HRESULT KDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);
	// Setup the viewport    
	m_ViewPort.Width = Desc.BufferDesc.Width;
	m_ViewPort.Height = Desc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);

	// imgui d3d impl 초기화
	ImGui_ImplDX11_Init(g_pd3dDevice, m_pImmediateContext);

	return hr;
}

bool KDevice::ResizeDevice(UINT width, UINT height)
{
	if (m_pd3dDevice==nullptr)return false;
	//렌더타겟, 깊이 스텐실 버퍼 해제
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRenderTargetView)m_pRenderTargetView->Release();
	if (m_DepthStencilView)m_DepthStencilView->Release();


	HRESULT hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount,
		width, height,
		m_SwapChainDesc.BufferDesc.Format,
		m_SwapChainDesc.Flags);
	if (SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_SwapChainDesc);
	}
	SetRenderTargetView();
	SetDepthStencilView();
	SetViewPort();
	GetClientRect(g_hWnd, &g_rtClient);
	return true;
}

bool KDevice::CleanupDevice()
{
	//스마트 포인터 사용
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();
	if (m_pGIFactory) m_pGIFactory->Release();
	m_pd3dDevice = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
	m_pImmediateContext = nullptr;
	m_pGIFactory = nullptr;
	ImGui_ImplDX11_Shutdown();
	return true;
}

KDevice::KDevice()
{
	m_pd3dDevice = nullptr;
	m_pSwapChain = nullptr;;
	m_pRenderTargetView = nullptr;;
	m_pGIFactory = nullptr;
	m_pImmediateContext = nullptr;
	m_DepthStencilView = nullptr;
}
