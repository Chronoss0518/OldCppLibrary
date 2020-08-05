//--------------------------
//�O���s��
//--------------------------

cbuffer DrawData :register(b7)
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
};

//--------------------------
//���ʃf�[�^
//--------------------------

#include"MShader.hlsli"

//--------------------------
//�o�̓f�[�^
//--------------------------


//���_�V�F�[�_(VertexShader)//
//�ʏ�`��//
VS_OUT main
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


