
//--------------------------
//�O���s��
//--------------------------

float4x4 ModelMat;
float4x4 ViewMat;
float4x4 ProMat;

float2 WindSize = float2(1280.0f, 720.0f);

//--------------------------
//�摜�f�[�^
//--------------------------

texture Tex;

sampler Smp = sampler_state {
	Texture = <Tex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR; 
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 BaseColor = float4(1.0f,1.0f,1.0f,1.0f);


//--------------------------
//�V�F�[�_�[
//--------------------------
struct VS_OUT {
	float4 Pos	: POSITION;
	float4 Color : COLOR0;
	float2 UV	: TEXCOORD0;
};

//���_�V�F�_(VertexShader)//
//�|���S���o�[�W����//
VS_OUT PoBoVS(
	float3 pos : POSITION
	, float4 color : COLOR0
	, float2 uv : TEXCOORD0

) {
	VS_OUT Out;

	Out.Pos = float4(pos, 1.0f);

	Out.Pos = mul(Out.Pos, ModelMat);

	Out.Pos = mul(Out.Pos, ViewMat);

	Out.Pos = mul(Out.Pos, ProMat);

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.UV = uv;

	//���_�̐F���//
	Out.Color = color;

	//�o��//
	return Out;
}

//���_�V�F�_(VertexShader)//
//�X�v���C�g�o�[�W����//
VS_OUT SpVS(
	float3 pos : POSITION
	, float4 color : COLOR0
	, float2 uv : TEXCOORD0

) {
	VS_OUT Out;

	Out.Pos = float4(pos, 1.0f);

	float4x4 SpProMat;

	SpProMat = float4x4(
		2.0f / WindSize.x, 0.0f, 0.0f, 0.0f
		, 0.0f, 2.0f / WindSize.y, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, -1.0f, 1.0f, 0.0f, 1.0f
		);

	Out.Pos = mul(Out.Pos, ModelMat);

	Out.Pos = mul(Out.Pos, SpProMat);

	Out.Color = color;

	//�e�N�X�`���}�b�v��̈ʒu���//
	Out.UV = uv;

	//�o��//
	return Out;
}

//�s�N�Z���V�F�_(PixelShader)//
//���p//
float4 PS(VS_OUT In) : COLOR0
{
	float4 Out = In.Color;
	Out *= tex2D(Smp, In.UV);

	Out *= BaseColor;

	clip(Out.a < 0.1f ? -1 : 1);

	return Out;
}

//--------------------------
//�e�N�j�b�N
//--------------------------
technique PoBoTech {
	pass P0 {
		VertexShader = compile vs_3_0 PoBoVS();
		PixelShader = compile ps_3_0 PS();
	}
}

technique SpTech {
	pass P0 {
		VertexShader = compile vs_3_0 SpVS();
		PixelShader = compile ps_3_0 PS();
		CullMode = NONE;
	}
}