#pragma once
#include "KStd.h"
class KCamera
{
public:
	float				m_fSpeed;
	float				m_fMouseSensitivity;
	float				m_fOriginSpeed;
	KVector3			m_vCameraPos;
	KVector3			m_vCameraTarget;
	KVector3			m_vLook;
	KVector3			m_vSide;
	KVector3			m_vUp;
public:
	float				m_fYaw;
	float				m_fPitch;
	float				m_fRoll;
	float				m_fRadius;
public:
	KMatrix			m_matWorld;
	KMatrix			m_matView;
	KMatrix			m_matProj;
public:
	KMatrix				OnMouseRotation();
	KVector3*			GetCameraTarget();
	KVector3*			GetCameraPos();
	virtual KMatrix     CreateViewMatrix(KVector3 vPos, KVector3 vTarget, KVector3 vUp= KVector3(0,1,0));
	virtual KMatrix  	CreateProjMatrix(float fNear, float fFar, float fFov, float fAspect);
public:
	virtual	bool		Follow2DPos(KVector2* vPos, KVector2 offset = {0,0});
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	
public:
	KCamera();
	virtual ~KCamera();
};

class KDebugCamera : public KCamera
{
public:
	//virtual bool		Frame() override;
	virtual KMatrix		OnMouseRotation();
	virtual bool		Frame();
};

