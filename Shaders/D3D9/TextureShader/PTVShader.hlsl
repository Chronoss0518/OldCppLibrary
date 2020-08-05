
//--------------------------
//共有データ
//--------------------------

#include"TShader.hlsli"

//--------------------------
//外部行列
//--------------------------

row_major float4x4 ModelMat;

struct MatData
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
};

MatData Mats;

//頂点シェダ(VertexShader)//
//板ポリゴンバージョン//
VS_OUT main(
	float3 pos : POSITION
	, float4 color : COLOR0
	, float2 uv : TEXCOORD0

) {
	VS_OUT Out;

	Out.Pos = float4(pos, 1.0f);

	Out.Pos = mul(Out.Pos, ModelMat);

	Out.Pos = mul(Out.Pos, Mats.ViewMat);

	Out.Pos = mul(Out.Pos, Mats.ProMat);

	//テクスチャマップ上の位置情報//
	Out.UV = uv;

	//頂点の色情報//
	Out.Color = color;

	//出力//
	return Out;
}
