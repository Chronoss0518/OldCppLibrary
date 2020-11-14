
//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

//頂点シェダ(VertexShader)//
//スプライトバージョン//
VS_OUT main(
	float4 pos : POSITION0
	, float2 uv : TEXCOORD0
	, float4 color : COLOR0
) {
	VS_OUT Out;

	Out.Pos = pos;

	Out.Pos = mul(Out.Pos, ModelMat);

	//テクスチャマップ上の位置情報//
	Out.UV = uv;

	Out.Color = color;

	//出力//
	return Out;
}
