TextureCube		g_txSky : register(t0);
SamplerState	g_Sample : register(s0);

cbuffer CBuf
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	matrix g_matNormal : packoffset(c12);
	float4 g_light : packoffset(c16);
	float4 g_value : packoffset(c17); 
};

struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float3 t : TEXTURE;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float3 t : TEXTURE;	// float3임
};

VS_OUTPUT VS(VS_INPUT vIn) 
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	vOut.p			= mul( float4(vIn.p,1.0f), g_matWorld );
	vOut.p			= mul(vOut.p, g_matView );
	vOut.p			= mul(vOut.p, g_matProj );
	vOut.p			= vOut.p.xyww;

	vOut.c			= vIn.c;
	vOut.t			= normalize(vIn.p.xyz); 
	vOut.n			= normalize(mul(vIn.n, (float3x3)g_matWorld));	
    return vOut;
}


float4 PS(VS_OUTPUT input) : SV_TARGET
{	
	//텍스처에서 t좌표에 해당하는 컬러값(픽셀) 반환
	return g_txSky.Sample(g_Sample, input.t);
}