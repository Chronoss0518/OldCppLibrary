
//--------------------------
//外部行列
//--------------------------

cbuffer DrawData :register(b7)
{
	row_major float4x4 ModelMat;
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
	float2 WindSize = float2(1280.0f, 720.0f);
};



//--------------------------
//シェーダー
//--------------------------
struct VS_OUT {
	float4 Pos	: VS_Position;
	float4 Color : COLOR0;
	float2 UV	: TEXCOORD0;
};
