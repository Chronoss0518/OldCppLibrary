
//--------------------------
//���ʃf�[�^
//--------------------------

#include"TShader.hlsli"

//���_�V�F�_(VertexShader)//
//�X�v���C�g�o�[�W����//
VS_OUT main(
	float4 pos : POSITION0
	, float2 uv : TEXCOORD0
	, float4 color : COLOR0
) {
	VS_OUT Out;

	Out.Pos = pos;

	Out.Pos = mul(Out.Pos, ModelMat);

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.UV = uv;

	Out.Color = color;

	//�o��//
	return Out;
}
