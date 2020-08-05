
//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

//--------------------------
//外部行列
//--------------------------

row_major float4x4 ModelMat;

//--------------------------
//外部データ
//--------------------------

float4 WindSize = float4(1280.0f, 720.0f, 0.0f, 0.0f);

//頂点シェダ(VertexShader)//
//スプライトバージョン//
VS_OUT main(
	float3 pos : POSITION
	, float4 color : COLOR0
	, float2 uv : TEXCOORD0

) {
	VS_OUT Out;

	Out.Pos = float4(pos, 1.0f);

	float4x4 SpProMat;

	SpProMat = float4x4(
		2.0f / WindSize.x, 0.0f, 0.0f, 0.0f
		, 0.0f, -2.0f / WindSize.y, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, -1.0f, 1.0f, 0.0f, 1.0f
		);

	Out.Pos = mul(Out.Pos, ModelMat);

	Out.Pos = mul(Out.Pos, SpProMat);

	Out.Color = color;

	//テクスチャマップ上の位置情報//
	Out.UV = uv;

	//出力//
	return Out;
}
