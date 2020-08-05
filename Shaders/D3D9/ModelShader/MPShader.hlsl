
//--------------------------
//���ʃf�[�^
//--------------------------

#include"MShader.hlsli"


//--------------------------
//���f���f�[�^
//--------------------------


struct Material
{
	float4 Dif;
	float4 SpeCol;
};


Material Mate:register(c1);

//float4 M_Dif;
//float4 M_SpeCol;

float4 CamPos:register(c0);

texture ModelTex :register(t0);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler ModelSmp = sampler_state {
	Texture = <ModelTex>;
	MinFilter = LINEAR;//�k���t�B���^//
	MagFilter = LINEAR;//�g��t�B���^//
	MipFilter = LINEAR;//�~�j�}�b�v�t�B���^// 
	AddressU = Wrap;
	AddressV = Wrap;
};


//������
texture NormalTex :register(t2);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler NormalSmp = sampler_state {
	Texture = <NormalTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//--------------------------
//���C�g�f�[�^
//--------------------------



struct Light
{
	float4 Dif;
	float4 Dir;
};

Light light : register(c3);

struct PLight
{
	float4 Dif;
	float4 Pos;
};

int PLightCnt = 7;


struct LightFlg
{
	float4 LF1;
	float4 LF2;
};

LightFlg LFlg:register(c5);

PLight pLight[7] :register(c7);


//������
texture LightPowMap :register(t1);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler LightSmp = sampler_state {
	Texture = <LightPowMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//--------------------------
//BaseShader
//--------------------------

float4 LightCol(VS_OUT _Base, float4 _Color);

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color);

float3 LamLightCol(float3 _Dif, float _Pow);

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal);

float3 AmbLightCol();

//�s�N�Z���V�F�_(PixelShader)//
//�ʏ�`��//
float4 main(VS_OUT In) :COLOR0
{
	//�J�����̑O���ɂ��邩�̔���//

clip(In.ProPos.x > 1.0f && In.ProPos.x < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.y > 1.0f && In.ProPos.y < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.z > 1.0f && In.ProPos.z < 0.0f ? -1.0f : 1.0f);

	float4 Color = float4(0.0f,0.0f,0.0f,1.0f);

	Color = Mate.Dif * tex2D(ModelSmp, In.UV);

	//Color = tex2D(ModelSmp, In.UV);

	clip(Color.a < 0.1f ? -1 : 1);

	Color = LightCol(In, Color);

	float PFlg[7] =
	{
		LFlg.LF1.x,LFlg.LF1.y,
		LFlg.LF1.z,LFlg.LF1.w,
		LFlg.LF2.x,LFlg.LF2.y,
		LFlg.LF2.z
	};

	for (int i = 0; i < PLightCnt; i++)
	{
		if (LFlg.LF2.w <= 0.0f)break;

		if (PFlg[i] <= 0.0f)continue;

		Color = PLightCol(pLight[i], In , Color);

	}

	return Color;

}


float4 LightCol(VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if (LFlg.LF2.w <= 0.0f)return Col;

	float Dot;

	Dot = dot(_Base.Normal, -light.Dir.xyz);

	Dot = saturate(Dot);

	float TmpPow = tex2D(LightSmp, float2(Dot, 0.5f)).r;

	Col.rgb *= (LamLightCol(light.Dif.rgb, TmpPow) + AmbLightCol());

	Col.rgb += SpeLightCol(light.Dir.xyz, _Base.UsePos.xyz, _Base.Normal);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	bool TmpFlg = false;

	float3 TmpVec = _Base.UsePos.xyz;

	TmpVec = TmpVec - plight.Pos.xyz;

	float Len;

	Len = length(TmpVec);

	TmpFlg = Len > plight.Pos.w ? true : false;

	if (TmpFlg)return Col;

	TmpVec = normalize(TmpVec);

	float Par = Len / plight.Pos.w;

	float Dot;

	Dot = dot(_Base.Normal, -TmpVec);

	Dot = saturate(Dot);

	Col.rgb *= LamLightCol(plight.Dif.rgb, Dot) * Par;

	Col.rgb += SpeLightCol(TmpVec, _Base.UsePos.xyz, _Base.Normal) * Par;

	return Col;
}

float3 LamLightCol(float3 _Dif, float _Pow)
{

	float3 TmpLightCol = _Dif;

	TmpLightCol *= _Pow;

	return TmpLightCol;
}

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal)
{
	float3 TmpLightCol = {0.0f,0.0f,0.0f};

	if (Mate.SpeCol.a < 0)return TmpLightCol;

	float3 TmpVec = normalize(CamPos.xyz - _ModelPos);//�s�N�Z������̃J��������

	TmpVec = normalize(-_Dir + TmpVec);

	float LCDot = dot(TmpVec, _Normal);

	float Pow = saturate(LCDot);

	TmpLightCol = Mate.SpeCol.rgb * pow(Pow, Mate.SpeCol.a);

	return TmpLightCol;
}

float3 AmbLightCol()
{

	float3 TmpLightCol = light.Dif.rgb;

	TmpLightCol *= light.Dir.w;

	return TmpLightCol;

}
