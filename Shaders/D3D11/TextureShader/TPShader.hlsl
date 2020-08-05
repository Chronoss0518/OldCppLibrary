
//--------------------------
//�摜�f�[�^
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
//���ʃf�[�^
//--------------------------

#include"TShader.hlsli"

//�s�N�Z���V�F�_(PixelShader)//
//���p//
float4 main(VS_OUT In) : SV_Target
{
	float4 Out = In.Color;
	Out *= Tex.Sample(Smp, In.UV);;

	Out *= BaseColor;

	clip(Out.a < 0.1f ? -1 : 1);

	return Out;

}