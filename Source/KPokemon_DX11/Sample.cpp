#include "Sample.h"
//----------------------------------
//------------------2022-3-12 최지원
//이동 : 방향키
//확인 : Z키
//취소 : X키
//메뉴 : A키
bool Sample::Init()
{
    //사운드 초기화 
	g_SoundManager.Init();
	//씬 매니져
	g_SceneManager.Init(m_pImmediateContext);

    return true;
}
// 프레임 함수
bool Sample::Frame()
{
	g_SceneManager.Frame();
    return true;
}
bool Sample::Render()
{
	g_SceneManager.Render();
    return true;
}
bool Sample::Release()
{
	g_SceneManager.Release();
    return true;
}

Sample::Sample()
{
}

Sample::~Sample()
{
}

WinMain_OPT(최지원 포켓몬스터 모작, 960, 540);
