
//--------------------------
//���ʃf�[�^
//--------------------------

#include"MCShader.hlsli"

//--------------------------
//�O���s��
//--------------------------

struct MatData
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
};

MatData Mats;

row_major float4x4 ModelMat;

float4 ContourSize = 1.0f;

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

	float3 TmpVec;

	TmpVec = normalize(Normal);

	Pos.xyz += TmpVec * ContourSize.x;

	Out.Pos = mul(Pos, ModelMat);

	Out.Pos = mul(Out.Pos, Mats.ViewMat);

	Out.Pos = mul(Out.Pos, Mats.ProMat);

	Out.ProPos = Out.Pos.xyz;

	return Out;
}
