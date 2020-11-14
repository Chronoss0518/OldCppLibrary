

//--------------------------
//���ʃf�[�^
//--------------------------

#include"TShader.hlsli"

//--------------------------
//�摜�f�[�^
//--------------------------

texture2D Tex : register(t0);

sampler Smp :register(s0);

//�s�N�Z���V�F�_(PixelShader)//
//���p//
float4 main(VS_OUT In) : SV_Target0
{
	float4 Out = In.Color;
	Out *= Tex.Sample(Smp, In.UV);

	//Out = BaseColor;

	clip(Out.a < 0.01f ? -1 : 1);

	return Out;

}