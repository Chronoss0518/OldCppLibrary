
//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

//--------------------------
//シェーダー
//--------------------------
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

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.Pos = mul(Out.Pos, ProMat);

	//テクスチャマップ上の位置情報//
	Out.UV = uv;

	//頂点の色情報//
	Out.Color = color;

	//出力//
	return Out;
}
