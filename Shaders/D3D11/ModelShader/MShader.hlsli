//--------------------------
//キャラクター構成データ
//--------------------------

cbuffer DrawData :register(b0)
{
	row_major float4x4 ViewMat;

	row_major float4x4 ProMat;

	float4 WindSize = float4(1280.0f, 720.0f, 0, 0);
};

cbuffer CharaData :register(b1)
{
	row_major float4x4 ModelMat;

	row_major float4x4 SkinWeightMat[1000];
};

cbuffer Material :register(b2)
{
	float4 Dif = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 SpeCol;
	float4 Anbient;
};

texture2D ModelTex :register(t0);

texture2D NormalTex:register(t1);

//画像から1ピクセルの色を取得するための物//
sampler ModelSmp:register(s0);

//画像から1ピクセルの色を取得するための物//
sampler NormalSmp:register(s1);

//--------------------------
//出力データ
//--------------------------

struct VS_OUT
{
	float4 Pos			:SV_POSITION;
	float3 Normal		:NORMAL0;
	float3 FaceNormal	:NORMAL1;
	float Temperature	:TEXCOORD4;
	float4 Color		:COLOR0;
	float4 UsePos		:TEXCOORD1;
	float4 ViewPos		:TEXCOORD2;
	float4 ProPos		:TEXCOORD3;
	float2 UV			:TEXCOORD0;
};

float4x4 BlendMatrix(uint4x4 _blend, float4x4 _blendPow,uint _blendNum)
{
	float4x4 BlendMat;

	for (uint i = 0; i < _blendNum; i++)
	{
		uint first = i / 4;
		uint second = i % 4;

		BlendMat += SkinWeightMat[_blend[first][second]] * _blendPow[first][second];
	}

	return BlendMat;


}