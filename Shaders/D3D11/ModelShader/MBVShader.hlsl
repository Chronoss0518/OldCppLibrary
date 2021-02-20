
//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"

//--------------------------
//外部行列
//--------------------------

//--------------------------
//出力データ
//--------------------------


//頂点シェーダ(VertexShader)//
//通常描画//
VS_OUT main
(
	float4 Pos			: POSITION0,
	float3 Normal		: NORMAL0,
	float3 FaceNormal	: NORMAL1,
	float4 Color		: COLOR0,
	float2 UV			: TEXCOORD0,
	float Temperature	: TEXCOORD1,
	uint4x4 Blend		: BLENDINDEX0,
	float4x4 BlendPow	: BLENDWEIGHT0,
	uint BlendNum		: BLENDINDEX4
)
{

	VS_OUT Out;

	Out.Pos = Pos;

	float4x4 WorldMat = mul(FrameMatrix, ModelMat);

	Out.Pos = mul(Out.Pos, WorldMat);

	float4x4 TmpMat
		= float4x4(
			1.0f, 0.0f, 0.0f, 1.0f
			, 0.0f, 1.0f, 0.0f, 1.0f
			, 0.0f, 0.0f, 1.0f, 1.0f
			, 0.0f, 0.0f, 0.0f, 1.0f);

	TmpMat = BlendNum > 0 ?  BlendMatrix(Blend, BlendPow, BlendNum) : TmpMat;

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);

	Out.ProPos = Out.Pos;

	Out.UV = UV;

	//Out.Normal = normalize(mul(Normal, (float3x3)ModelMat));

	Out.Normal = float3(0.0f, 0.0f, 1.0f);
	Out.FaceNormal = float3(0.0f, 0.0f, 1.0f);

	Out.Color = 1.0f;

	Out.Temperature = Temperature;
	//Out.Temperature = 0.0f;

	return Out;
}


