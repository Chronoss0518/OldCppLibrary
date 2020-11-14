
//--------------------------
//外部行列
//--------------------------


cbuffer DrawData :register(b0)
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
	float4 WindSize = float4(1280.0f, 720.0f,0,0);
};


cbuffer PolygonData:register(b1)
{
	row_major float4x4 ModelMat;
	float4 BaseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
}


//--------------------------
//シェーダー
//--------------------------
struct VS_OUT {
	float4 Pos	: SV_POSITION;
	float4 Color : COLOR0;
	float2 UV	: TEXCOORD0;
};
