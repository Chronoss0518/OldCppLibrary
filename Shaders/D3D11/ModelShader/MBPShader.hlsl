//--------------------------
//�O���s��
//--------------------------

float EasingValue = 0.0f;

//--------------------------
//���ʃf�[�^
//--------------------------

#include"MShader.hlsli"

//--------------------------
//���C�g�f�[�^
//--------------------------

struct Light
{
	float4 Dif;
	float3 Dir;
	float AmbPow;
};

struct PLight
{
	float3 Pos;
	float4 Dif;
	float Len;
	bool Flg;
};

cbuffer LightData :register(b8)
{
	float3 CamPos = float3(0.0f, 0.0f, 0.0f);

	bool LightUseFlg = false;

	Light light = {
		float4(1.0f,1.0f,1.0f,1.0f)
		,float3(0.0f,-1.0f,0.0f)
		,0.3f
	};

	int PlightCnt = 10;

	PLight pLight[10];

};


	//������
texture2D LightPowMap :register(t3);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler LightSmp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
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
float4 main(VS_OUT In) :SV_Target
{
	//�J�����̑O���ɂ��邩�̔���//

clip(In.ProPos.x > 1.0f && In.ProPos.x < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.y > 1.0f && In.ProPos.y < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.z > 1.0f && In.ProPos.z < 0.0f ? -1.0f : 1.0f);

	float4 Color = float4(0.0f,0.0f,0.0f,0.0f);

	Color = Mate.Dif * ModelTex.Sample(ModelSmp, In.UV);

	clip(Color.a < 1.0f ? -1 : 1);

	Color = LightCol(In, Color);

	for (int i = 0; i < 10; i++)
	{
		if (!LightUseFlg)break;

		Color = PLightCol(pLight[i], In , Color);

	}

	return Color;

}


float4 LightCol(VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if(!LightUseFlg)return Col;

	float Dot;

	Dot = dot(_Base.Normal, -light.Dir);

	Dot = saturate(Dot);

	float TmpPow = LightPowMap.Sample(LightSmp, float2(Dot, 0.5f)).r;

	Col.rgb *= (LamLightCol(light.Dif.rgb, TmpPow) + AmbLightCol());

	Col.rgb += SpeLightCol(light.Dir, _Base.UsePos.xyz, _Base.Normal);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if (!LightUseFlg)return Col;
	if (!plight.Flg)return Col;

	bool TmpFlg = false;

	float3 TmpVec = _Base.UsePos.xyz;

	TmpVec = TmpVec - plight.Pos;

	float Len;

	Len = length(TmpVec);

	TmpFlg = Len > plight.Len ? true : false;

	if (TmpFlg)return Col;

	TmpVec = normalize(TmpVec);

	float Par = Len / plight.Len;

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

float3 SpeLightCol(float3 _Dir, float3 _ModelPos,float3 _Normal)
{

	float3 TmpVec = normalize(CamPos - _ModelPos);//�s�N�Z������̃J��������

	TmpVec = normalize(-_Dir + TmpVec);

	float LCDot = dot(TmpVec, _Normal);

	float Pow = saturate(LCDot);

	float3 TmpLightCol = Mate.SpeCol.rgb * pow(Pow, Mate.SpePow);

	return TmpLightCol;
}

float3 AmbLightCol()
{

	float3 TmpLightCol = light.Dif.rgb;

	TmpLightCol *= light.AmbPow;

	return TmpLightCol;

}
