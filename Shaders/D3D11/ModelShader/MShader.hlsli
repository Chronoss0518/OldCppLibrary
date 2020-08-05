//--------------------------
//キャラクター構成データ
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
//未実装
texture2D NormalTex:register(t1);

//画像から1ピクセルの色を取得するための物//
sampler ModelSmp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//画像から1ピクセルの色を取得するための物//
sampler NormalSmp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//--------------------------
//出力データ
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
