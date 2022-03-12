#include "KState.h"
ID3D11DepthStencilState* KState::g_pCurrentDSS = nullptr;
ID3D11SamplerState* KState::g_pCurrentSS[3] = { nullptr,nullptr,nullptr };
ID3D11RasterizerState* KState::g_pCurrentRS = nullptr;
ID3D11BlendState* KState::g_pCurrentBS = nullptr;

ID3D11BlendState* KState::g_pBlendState = nullptr;
ID3D11DepthStencilState* KState::g_pDSS = nullptr;
ID3D11DepthStencilState* KState::g_pDSS_Disabled = nullptr;
ID3D11SamplerState* KState::g_pClampSS = nullptr;
ID3D11SamplerState* KState::g_pWrapSS = nullptr;
ID3D11SamplerState* KState::g_pMirrorSS = nullptr;
ID3D11SamplerState* KState::g_pNoFilterSS =nullptr;
ID3D11RasterizerState* KState::g_pRSSolid = nullptr;
ID3D11RasterizerState* KState::g_pRSWireFrame = nullptr;
ID3D11RasterizerState* KState::g_pRSBackface = nullptr;
HRESULT KState::CreateDepthStenState()
{
    HRESULT hr = S_OK;
    D3D11_DEPTH_STENCIL_DESC dsd;
    ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
    dsd.DepthEnable = TRUE;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    //1.0, 0.6�� 0.5�� ���ؼ� ũ�� ����
    //���� �տ� �ִ� ���� �ѷ����� �ڿ��ִ¾ֵ��� ���� �ȵ�
    dsd.DepthFunc = D3D11_COMPARISON_LESS;
    dsd.StencilEnable = TRUE;
    dsd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
    dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    hr = g_pd3dDevice->CreateDepthStencilState(&dsd, &g_pDSS);

    ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
    dsd.DepthEnable = FALSE;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    //1.0, 0.6�� 0.5�� ���ؼ� ũ�� ����
    //���� �տ� �ִ� ���� �ѷ����� �ڿ��ִ¾ֵ��� ���� �ȵ�
    dsd.DepthFunc = D3D11_COMPARISON_ALWAYS;
    dsd.StencilEnable = TRUE;
    dsd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
    dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    hr = g_pd3dDevice->CreateDepthStencilState(&dsd, &g_pDSS_Disabled);

    if (FAILED(hr))
    {
        return hr;
    }
    //���� ���ٽ� ���� ������ ��� ������� �����ϴ� ���̱⿡ OM
    return hr;
}

HRESULT KState::CreateBlendState()
{
    HRESULT hr = S_OK;
    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

    bd.AlphaToCoverageEnable = true;
    //bd.IndependentBlendEnable = true;
    bd.RenderTarget[0].BlendEnable = TRUE;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    //// A ���� ����
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = g_pd3dDevice->CreateBlendState(&bd, &g_pBlendState);
    if (FAILED(hr))
    {
        return hr;
    }
}

HRESULT KState::CreateRasterizeState()
{
    HRESULT hr = S_OK;
    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    hr = g_pd3dDevice->CreateRasterizerState(&rd, &g_pRSWireFrame);
    ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_BACK;
    rd.DepthClipEnable = TRUE; // Clipping ȿ�� �⺻�� False��
    hr = g_pd3dDevice->CreateRasterizerState(&rd, &g_pRSSolid);

    ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_FRONT;
    rd.DepthClipEnable = TRUE; // Clipping ȿ�� �⺻�� False��
    hr = g_pd3dDevice->CreateRasterizerState(&rd, &g_pRSBackface);
    return hr;
}

HRESULT KState::CreateSamplerState()
{
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MinLOD = FLT_MAX;
    sd.MaxLOD = FLT_MIN;
    HRESULT hr = g_pd3dDevice->CreateSamplerState(&sd,
        &g_pClampSS);

    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.MinLOD = FLT_MAX;
    sd.MaxLOD = FLT_MIN;
    hr = g_pd3dDevice->CreateSamplerState(&sd, &g_pWrapSS);

    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.MinLOD = FLT_MAX;
    sd.MaxLOD = FLT_MIN;
    hr = g_pd3dDevice->CreateSamplerState(&sd,
        &g_pMirrorSS);

    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.MinLOD = FLT_MAX;
    sd.MaxLOD = FLT_MIN;
    hr = g_pd3dDevice->CreateSamplerState(&sd,
        &g_pNoFilterSS);

    return hr;
}

bool KState::SetState()
{
    CreateDepthStenState();
    CreateSamplerState();
    CreateRasterizeState();
    CreateBlendState();
	return true;
}

bool KState::ReleaseState()
{
    g_pRSSolid->Release();
    g_pRSWireFrame->Release();
    g_pRSBackface->Release();

    g_pDSS->Release();
    g_pDSS_Disabled->Release();

    g_pBlendState->Release();
    g_pMirrorSS->Release();
    g_pClampSS->Release();
    g_pWrapSS->Release();
    return true;
}