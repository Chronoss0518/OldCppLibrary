//--------------------------
//外部行列
//--------------------------

cbuffer DrawData :register(b7)
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
};

//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"

//--------------------------
//出力データ
//--------------------------


//頂点シェーダ(VertexShader)//
//通常描画//
VS_OUT main
(
	float4 Pos		: POSITION,
	float3 Normal : NORMAL,
	float2 UV : TEXCOORD0
)
{
	VS_OUT Out;

	Out.Pos = mul(Pos, ModelMat);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);

	Out.ProPos = Out.Pos;

	Out.UV = UV;

	Out.Normal = normalize(mul(Normal, (float3x3)ModelMat));

	return Out;
}


