#include "KBoxObj.h"

bool KBoxObj::Init(std::wstring vsfile, std::wstring psfile, std::wstring texturefile)
{
	const KVector3 vertices[] =
	{
		{-1.0f,-1.0f,-1.0f},
		{ 1.0f,-1.0f,-1.0f},
		{-1.0f,1.0f,-1.0f},
		{ 1.0f,1.0f,-1.0f},//Á¤¸é3
		{1.0f,-1.0f,1.0f},
		{ -1.0f,-1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{-1.0f,1.0f,1.0f},//µÞ¸é7
		{1.0f,-1.0f,-1.0f},
		{ 1.0f,-1.0f,1.0f},
		{1.0f,1.0f,-1.0f},
		{ 1.0f,1.0f,1.0f},//¿À¸¥ÂÊ¸é11
		{-1.0f,-1.0f,1.0f},
		{ -1.0f,-1.0f,-1.0f},
		{-1.0f,1.0f,1.0f},
		{ -1.0f,1.0f,-1.0f},//¿ÞÂÊ¸é15
		{-1.0f,1.0f,-1.0f},
		{ 1.0f,1.0f,-1.0f},
		{-1.0f,1.0f,1.0f},
		{ 1.0f,1.0f,1.0f},//À­ÂÊ¸é19
		{-1.0f,-1.0f,1.0f},
		{ 1.0f,-1.0f,1.0f},
		{-1.0f,-1.0f,-1.0f},
		{ 1.0f,-1.0f,-1.0f},//¾Æ·§¸é23
	};
	const KVector2 uv[] =
	{
		{0.0f,1.0f},
		{1.0f,1.0f},
		{0.0f,0.0f},
		{1.0f,0.0f},//Á¤¸é
		{0.0f,1.0f},
		{1.0f,1.0f},
		{0.0f,0.0f},
		{1.0f,0.0f},//µÞ¸é
		{0.0f,1.0f},
		{1.0f,1.0f},
		{0.0f,0.0f},
		{1.0f,0.0f},//¿À¸¥¸é
		{0.0f,1.0f},
		{1.0f,1.0f},
		{0.0f,0.0f},
		{1.0f,0.0f},//¿Þ¸é
		{0.0f,1.0f},
		{1.0f,1.0f},
		{0.0f,0.0f},
		{1.0f,0.0f},//À­¸é
		{0.0f,1.0f},
		{1.0f,1.0f},
		{0.0f,0.0f},
		{1.0f,0.0f},//¾Æ·§¸é
	};
	const unsigned short indices[] =
	{
		2,1,0,	 2,3,1,//Á¤¸é
		6,5,4,	 6,7,5,//µÞ¸é
		10,9,8,  10,11,9,//¿À¸¥ÂÊ¸é
		14,13,12, 14,15,13,//¿ÞÂÊ¸é
		18,17,16, 18,19,17, //À­ÂÊ¸é
		22,21,20, 22,23,21,//¾Æ·§¸é
		//0,2,1, 2,3,1,
		//1,3,5, 3,7,5,
		//2,6,3, 3,6,7,
		//4,5,7, 4,7,6,
		//0,4,2, 2,4,6,
		//0,1,4, 1,5,4,
	};
	for (int num = 0; num < sizeof(vertices) / sizeof(KVector3); num++)
	{
		PNCT_VERTEX pnct;
		pnct.pos = vertices[num];
		pnct.color = { 1.0f,1.0f,1.0f,1.0f };
		pnct.tex = uv[num];
		m_VertexList.push_back(pnct);
	}

	for (int num = 0; num < sizeof(indices)/ sizeof(short); num++)
	{
		m_IndexList.push_back(indices[num]);
	}

	if (CreateObject(vsfile,
		psfile,
		texturefile, L""))
	{
		return true;
	}

	return false;
}

bool KBoxObj::Frame()
{
	return true;
}

bool KBoxObj::Render(ID3D11DeviceContext* pContext)
{
	KObject::Render(pContext);
	return true;
}

bool KBoxObj::Release()
{
	return true;
}

KBoxObj::KBoxObj()
{
}

KBoxObj::~KBoxObj()
{
}
