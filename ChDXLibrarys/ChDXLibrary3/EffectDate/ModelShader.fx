//--------------------------
//�O���s��
//--------------------------

float4x4 ModelMat;
float4x4 ViewMat;
float4x4 ProMat;

float EasingValue = 0.0f;

//--------------------------
//���f���f�[�^
//--------------------------

struct Material
{
	float4 Dif;
	float4 SpeCol;
	float SpePow;
};

Material Mate;

texture ModelTex;

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
texture NormalTex;

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

float3 CamPos = float3(0.0f, 0.0f, 0.0f);

bool LightUseFlg = false;

struct Light
{
	float4 Dif;
	float3 Dir;
	float AmbPow;
};

Light light = { float4(1.0f,1.0f,1.0f,1.0f),float3(0.0f,-1.0f,0.0f),0.3f };

struct PLight
{
	float3 Pos;
	float4 Dif;
	float Len;
	bool Flg;
};

int PlightCnt = 10;

PLight pLight[10];

//������
texture LightPowMap;

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

struct VS_OUT
{
	float4 Pos		:POSITION;
	float3 Normal	:NORMAL;
	float2 UV		:TEXCOORD0;
	float4 UsePos	:TEXCOORD1;
	float4 ViewPos	:TEXCOORD2;
	float4 ProPos	:TEXCOORD3;
};

float4 LightCol(VS_OUT _Base, float4 _Color);

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color);

float3 LamLightCol(float3 _Dif, float _Pow);

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal);

float3 AmbLightCol();


//���_�V�F�[�_(VertexShader)//
//�ʏ�`��//
VS_OUT BaseVS
(
	float4 Pos		: POSITION,
	float3 Normal : NORMAL,
	float2 UV : TEXCOORD0
)
{
	VS_OUT Out;

	Out.Pos = mul(Pos, ModelMat);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);

	Out.ProPos = Out.Pos;

	Out.UV = UV;

	Out.Normal = normalize(mul(Normal, (float3x3)ModelMat));

	return Out;
}


//�s�N�Z���V�F�_(PixelShader)//
//�ʏ�`��//
float4 BasePS(VS_OUT In) :COLOR0
{
	//�J�����̑O���ɂ��邩�̔���//

clip(In.ProPos.x > 1.0f && In.ProPos.x < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.y > 1.0f && In.ProPos.y < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.z > 1.0f && In.ProPos.z < 0.0f ? -1.0f : 1.0f);

	float4 Color = float4(0.0f,0.0f,0.0f,0.0f);

	Color = Mate.Dif * tex2D(ModelSmp, In.UV);

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

	float TmpPow = tex2D(LightSmp, float2(Dot, 0.5f)).r;

	Col.rgb *= (LamLightCol(light.Dif.rgb, TmpPow) + AmbLightCol());

	Col.rgb += SpeLightCol(light.Dir, _Base.UsePos.xyz, _Base.Normal);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

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

//--------------------------
//�e�N�j�b�N
//--------------------------
technique BaseTech {
	pass P0 {
		VertexShader = compile vs_3_0 BaseVS();
		PixelShader = compile ps_3_0 BasePS();
	}
}