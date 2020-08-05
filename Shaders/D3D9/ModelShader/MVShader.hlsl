
//--------------------------
//���ʃf�[�^
//--------------------------

#include"MShader.hlsli"

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

//���_�V�F�[�_(VertexShader)//
//�ʏ�`��//
VS_OUT main
(
	float4 Pos		: POSITION,
	float3 Normal	: NORMAL,
	float2 UV		: TEXCOORD0
)
{
	VS_OUT Out;

	Out.Pos = mul(Pos, ModelMat);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, Mats.ViewMat);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, Mats.ProMat);

	Out.ProPos = Out.Pos;

	Out.UV = UV;

	Out.Normal = Normal;

/*
	float3 BiNormal = cross(normalize(Normal), normalize(Tangent));

	BiNormal = normalize(BiNormal);

	float3x3 TmpNormals ={ normalize(ModelMat), normalize(BiNormal), normalize(Tangent) };
	
	Out.Normals = TmpNormals;

	Out.Normal = mul(Normal, Out.Normals);
*/
	return Out;
}
