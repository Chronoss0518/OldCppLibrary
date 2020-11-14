
//--------------------------
//���ʃf�[�^
//--------------------------

#include"MShader.hlsli"

//--------------------------
//�V�F�[�_�[
//--------------------------
//���_�V�F�_(VertexShader)//
//�|���S���o�[�W����//
VS_OUT main(
	float4 pos		: POSITION0
	, float2 uv		: TEXCOORD0
	, float4 color	: COLOR0
	, float3 normal : NORMAL0
) {
	VS_OUT Out;

	Out.Pos = pos;

	Out.Pos = mul(Out.Pos, ModelMat);
	//Out.Pos = mul(ModelMat, Out.Pos);

	Out.UsePos = Out.Pos;

	Out.Pos = mul(Out.Pos, ViewMat);
	//Out.Pos = mul(ViewMat, Out.Pos);

	Out.ViewPos = Out.Pos;

	Out.Pos = mul(Out.Pos, ProMat);
	//Out.Pos = mul(ProMat, Out.Pos);

	Out.ProPos = Out.Pos;

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.UV = uv;

	//���_�̐F���//
	Out.Color = color;

	Out.Normal = normal;
	Out.FaceNormal = normal;

	Out.Temperature = 0.0f;
	//�o��//
	return Out;
}
