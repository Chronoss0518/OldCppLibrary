//--------------------------
//�L�����N�^�[�\���f�[�^
//--------------------------

struct Material
{
	float4 Dif;
	float4 SpeCol;
	float SpePow;
};

cbuffer CharaData :register(b0)
{
	row_major float4x4 ModelMat;
	Material Mate;

};

texture2D ModelTex :register(t0);
//������
texture2D NormalTex:register(t1);

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler ModelSmp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//�摜����1�s�N�Z���̐F���擾���邽�߂̕�//
sampler NormalSmp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//--------------------------
//�o�̓f�[�^
//--------------------------

struct VS_OUT
{
	float4 Pos		:SV_Position;
	float3 Normal	:TEXCOORD0;
	float2 UV		:TEXCOORD1;
	float4 UsePos	:TEXCOORD2;
	float4 ViewPos	:TEXCOORD3;
	float4 ProPos	:TEXCOORD4;
};
