#include "KCore.h"
#include "KObjectManager.h"

KWrite*	g_Write= nullptr;

bool	KCore::GameRun()
{
    if (!GameFrame()) return false;
    if (!GameRender()) return false;
    return true;
}
bool	KCore::GameInit()
{
    KDevice::SetDevice();
    KState::SetState();
    m_Write.Init();
    m_Timer.Init();
    g_Input.Init();
    //g_Input.m_bInputAvailable = false;
    IDXGISurface1* m_pBackBuffer;
    m_pSwapChain->GetBuffer(0, 
        __uuidof(IDXGISurface),
        (void**)&m_pBackBuffer);
    m_Write.CreateDeviceResources(m_pBackBuffer);
    if (m_pBackBuffer)m_pBackBuffer->Release();
    g_Write = &m_Write;
    Init();

    return true;
}
bool	KCore::GameFrame() 
{
    // TODO : Frame Timer
    m_Timer.Frame();
    g_Input.Frame();
    //실시간 모든 콜라이더 충돌 프레임
    g_ObjManager.Frame();
    m_ImGuiManager.Frame();
    if (g_InputData.bDebugRender)
    {
        m_bDebugText = !m_bDebugText;
    }

    if (g_Input.GetKey(DIK_F2) == KEY_PUSH)
    {
        m_ImGuiManager.OnOffImgui();   
    }
    Frame();
    return true;
}
bool	KCore::GameRender() 
{
    PreRender();
        // TODO : Render Timer
        m_Timer.Render();
        g_Input.Render();
        
        Render();
        m_ImGuiManager.Render();
        if (m_bDebugText)
        {
            RECT  rt = { 0, 0, m_rtClient.right, m_rtClient.bottom };
            m_Write.RenderText(rt, m_Timer.m_szTimerString,
                D2D1::ColorF(1, 0, 0, 1), m_Write.m_pTextFormat);
        }
    PostRender();
    return true;
}

bool	KCore::PreRender() {

    //새 스왑체인 뷰포트
    float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

    m_pImmediateContext->ClearDepthStencilView(
        m_DepthStencilView,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    m_pImmediateContext->OMSetRenderTargets(1,
        &m_pRenderTargetView, m_DepthStencilView);

    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ApplyDSS(m_pImmediateContext, KState::g_pDSS);
    ApplySS(m_pImmediateContext, KState::g_pNoFilterSS, 0);
    ApplyRS(m_pImmediateContext, KState::g_pCurrentRS);
    ApplyBS(m_pImmediateContext, KState::g_pBlendState);

    return true;
}

bool	KCore::Render() {
    return true;
}

bool	KCore::PostRender() {
    //스왑체인 작업
    assert(m_pSwapChain);
    m_pSwapChain->Present(0, 0);
    return true;
}

bool	KCore::GameRelease() 
{
    Release();
    KState::ReleaseState();

    m_Timer.Release();
    g_Input.Release();
    m_Write.Release();

    CleanupDevice();
    return true;
}
bool    KCore::ResizeDevice(UINT iWidth, UINT iHeight)
{
    if (m_pd3dDevice == nullptr) return false;
    DeleteResizeDevice(iWidth, iHeight);


    m_Write.DeleteDeviceResize();
    KDevice::ResizeDevice(iWidth, iHeight);
    KWindow::ResizeDevice(iWidth, iHeight);

    IDXGISurface1* pSurface = nullptr;
    HRESULT hr = m_pSwapChain->GetBuffer(0,
        __uuidof(IDXGISurface1),
        (void**)&pSurface);
    if (SUCCEEDED(hr))
    {
        m_Write.CreateDeviceResources(pSurface);
    }
    if (pSurface) pSurface->Release();

    CreateResizeDevice(iWidth, iHeight);
    return true;
}
bool    KCore::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
    return true;
}
bool    KCore::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
    return true;
}
bool	KCore::Init()
{
    return true;
}
bool	KCore::Frame() {
    return true;
}
bool	KCore::Release() {
    return true;
}

KCore::KCore()
{
}

KCore::~KCore()
{
}
