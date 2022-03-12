#include "KSkyBox.h"
void KSkyBox::SetMatrix(KMatrix* pMatWorld, KMatrix* pMatView, KMatrix* pMatProj)
{
    if (pMatWorld != nullptr)
    {
        pMatWorld->_11 = 5.0f;
        pMatWorld->_22 = 5.0f;
        pMatWorld->_33 = 5.0f;
        m_cbData.matWorld = pMatWorld->Transpose();
    }
    if (pMatView != nullptr)
    {
        m_cbData.matView = pMatView->Transpose();
    }
    if (pMatProj != nullptr)
    {
        m_cbData.matProj = pMatProj->Transpose();
    }
    m_cbData.matNormal = m_cbData.matNormal.Transpose();
}

bool KSkyBox::Init(std::wstring shader, std::wstring tex)
{
    KBoxObj::Init(shader, shader,tex);
    return true;
}

bool KSkyBox::Frame()
{
    return true;
}

bool KSkyBox::Render(ID3D11DeviceContext* pContext)
{
    KObject::Render(pContext);
    return true;
}

bool KSkyBox::Release()
{
    return true;
}

KSkyBox::KSkyBox()
{
    D3DKMatrixIdentity(&m_matSkyWorld);
    m_matSkyWorld._11 = 10.0f;
    m_matSkyWorld._22 = 10.0f;
    m_matSkyWorld._33 = 10.0f;
}

KSkyBox::~KSkyBox()
{
}
