
//--------------------------
//共通データ
//--------------------------

#include"TShader.hlsli"

//--------------------------
//画像データ
//--------------------------

texture Tex:register(t0);

sampler Smp = sampler_state {
	Texture = <Tex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture BackTex:register(t1);

sampler BackSmp = sampler_state {
	Texture = <BackTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 BaseColor;

//AddColFlg,,,;
float4 Flg = float4(-1.0f, -1.0f, -1.0f, -1.0f);

float4 AddColFunction(float4 _Col, VS_OUT _In);

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT In) : COLOR0
{
	float4 Out = BaseColor;

	Out *= tex2D(Smp, In.UV);

	Out *= In.Color;

	//Out = AddColFunction(Out, In);

	clip(Out.a < 0.1f ? -1 : 1);

	return Out;
}

float4 AddColFunction(float4 _Col, VS_OUT _In)
{
	if (Flg.x > 0.0f)return _Col;

	float4 Tmp;

	Tmp = _Col + tex2D(BackSmp, _In.UV);;

	Tmp /= 2.0f;

	return Tmp;
}
