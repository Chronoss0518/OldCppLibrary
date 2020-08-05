
//--------------------------
//画像データ
//--------------------------

cbuffer TextureData :register(b7)
{
	texture2D Tex;
	float4 BaseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
};

sampler Smp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT In) : SV_Target
{
	float4 Out = In.Color;
	Out *= Tex.Sample(Smp, In.UV);;

	Out *= BaseColor;

	clip(Out.a < 0.1f ? -1 : 1);

	return Out;

}