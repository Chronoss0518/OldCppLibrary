
//--------------------------
//出力データ
//--------------------------

struct VS_OUT
{
	float4 Pos		:POSITION;
	float3 Normal	:NORMAL;
	float2 UV		:TEXCOORD0;
	float4 UsePos	:TEXCOORD1;
	float4 ViewPos	:TEXCOORD2;
	float4 ProPos	:TEXCOORD3;

};
