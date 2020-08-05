
//--------------------------
//���L�f�[�^
//--------------------------

#include"TShader.hlsli"

//--------------------------
//�O���s��
//--------------------------

row_major float4x4 ModelMat;

struct MatData
{
	row_major float4x4 ViewMat;
	row_major float4x4 ProMat;
};

MatData Mats;

//���_�V�F�_(VertexShader)//
//�|���S���o�[�W����//
VS_OUT main(
	float3 pos : POSITION
	, float4 color : COLOR0
	, float2 uv : TEXCOORD0

) {
	VS_OUT Out;

	Out.Pos = float4(pos, 1.0f);

	Out.Pos = mul(Out.Pos, ModelMat);

	Out.Pos = mul(Out.Pos, Mats.ViewMat);

	Out.Pos = mul(Out.Pos, Mats.ProMat);

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.UV = uv;

	//���_�̐F���//
	Out.Color = color;

	//�o��//
	return Out;
}
