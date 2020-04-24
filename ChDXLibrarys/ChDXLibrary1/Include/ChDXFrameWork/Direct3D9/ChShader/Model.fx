
//--------------------------
//�O���o���萔
//--------------------------
float4x4 g_mW;//�L�����N�^���[�J���ϊ��s��
float4x4 g_mV;//�r���[�s��
float4x4 g_mP;//�ˉe�ϊ��s��


//�}�e���A���f�[�^=====================================================================

float4 g_MateDiffuse = float4(1, 1, 1, 1);

float4 g_MateSpecular = float4(1,1,1,1);//���ːF

float g_MateSpePower = 50;//���ːF�̉s��

float4 g_MateEmissive;//���ȏƖ�

float g_InkSize = 0.01f;	//�֊s�̑���

float4 g_InkColor = float4(0.0f, 0.0f, 0.0f, 1.0f);//�֊s�̐F

//�e�N�X�`��===========================================================================
texture g_MateDiffuseTex;//�}�e���A���̃e�N�X�`��
texture g_ToonTex;

//���}�b�v�p�O���[�o��===========================================================

texture g_EnvTex;//�L���[�u���}�b�v
float g_ReflectionPower = 0.5;//�f�荞�ݗ�

samplerCUBE g_EnvSmp = sampler_state {
	Texture = <g_EnvTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//�e�N�X�`���p�T���v��
sampler g_MateDiffuseSmp = sampler_state {
	TexTure = <g_MateDiffuseTex>;//�g�p����e�N�X�`��
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler g_ToonSmp = sampler_state {
	TexTure = <g_ToonTex>;//�g�p����e�N�X�`��
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};


//float3 g_LightDir;
float3 normal;

//�J�����֌W===========================================================================

float3 g_CamPos;//�J�����̈ʒu


//////���C�g�֌W=======================================================================
//���s��

float LPow;
int g_LightEnable = 1;//���C�g�̗L��
float3 g_LightDir = float3(0.0f, -1.0f, 0.0f);//���C�g�̕���
float4 g_LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);//���C�g�F

//����
float4 g_LightAmbient = float4(0.2f, 0.2f, 0.2f, 0.2f);

//���ˌ�
float SpcPow;

//--------------------------
//���_�V�F�_===========================================================================
//--------------------------

//�o�͗p�\����
struct VS_OUT {
	float4 Pos	: POSITION;
	float3 wN	: TEXCOORD0;//���[���h�@��
	float3 wPos : TEXCOORD1;//���[���h���W
	float2 UV	: TEXCOORD2;//UV���W
};

//���_�V�F�_
VS_OUT VS(
	float4 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0
){
	VS_OUT Out;
	
	//���W��2D��
	Out.Pos = mul(pos, g_mW);
	Out.wPos = Out.Pos.xyz;//float4.xyz���s����float3��xyz���g�p���邱�Ƃ��ł���B

	Out.Pos = mul(Out.Pos, g_mV);
	Out.Pos = mul(Out.Pos, g_mP);
	Out.UV = uv;

	Out.wN = normalize(mul(normal, (float3x3)g_mW));
	//�o��
	return Out;
}

//--------------------------
//�s�N�Z���V�F�_�֘A
//--------------------------
//�o�͍\����
struct PS_OUT {
	float4 Color : COLOR0;
};
//�s�N�Z���V�F�_
PS_OUT PS(VS_OUT In)
{
	//�J�����ւ̕���
	float3 vCam = normalize(g_CamPos - In.wPos);//�s�N�Z������̃J��������

	//�@���𐳋K��

	float3 w_normal = normalize(In.wN);

	//���f���J���[=====================================================================

	float4 texCol = tex2D(g_MateDiffuseSmp, In.UV);//�T���v���̎����Ă���F���擾

	if (texCol.a < 0.1f)discard;//�A���t�@�e�X�g

	float4 modelCol = g_MateDiffuse * texCol;

	//���}�b�s���O
	float3 vRef = reflect(-vCam, w_normal);
	float4 envCol = texCUBE(g_EnvSmp, vRef);

	modelCol.rgb = lerp(modelCol.rgb, envCol.rgb, g_ReflectionPower);

	//���C�g�J���[=====================================================================
	
	float3 lightCol = 0;//�S���C�g�̍��v�g�U�F

	float3 lightSpe = 0;//�S���C�g�̍��v���ːF

	if (g_LightEnable) {

		//���s��=======================================================================
		//�g�U��(�����o�[�g)

		float LPow = dot(-g_LightDir, w_normal);

		LPow = saturate(LPow);//���ꂽ���l��1�ȏ�̒l�����ׂ�1�ցA0�ȉ��̂��̂�0�֑������B

		float4 ToonCol = tex2D(g_ToonSmp, float2(LPow, 0.5f));

		lightCol += g_LightColor.rgb * ToonCol.rgb;

		//����(�A���r�G���g)=========================================================

		lightCol += g_LightAmbient.rgb;

		//���ˌ�(�X�y�L����============================================================
		//PhonegShading

		//float3 vRef = reflect(g_LightDir, w_normal);//���ˊp
		//float SpePow = dot(vRef, vCam);

		//BlinnPhongShading:�v�Z�ʂ��y���Ȃ�B(��������тт₷���Ȃ�)

		float3 vH = normalize(-g_LightDir + vCam);

		float SpePow = dot(vH, w_normal);

		SpePow = saturate(SpePow);

		SpePow = pow(SpePow, g_MateSpePower);

		lightSpe += g_LightColor.rgb * SpePow;
	}
	else {
		lightCol = 1;
	}

	//�g�U�F===========================================================================

	float4 diffuseCol = modelCol;

	diffuseCol.rgb *= lightCol;//�g�U�F�̏ꍇ�͍���(�|���Z)���s���B
	//���ːF

	float4 SpeCol;

	SpeCol.rgb = g_MateSpecular.rgb * lightSpe;

	SpeCol.a = 0;

	//�o��=============================================================================

	PS_OUT Out;
	Out.Color = diffuseCol + SpeCol;
	Out.Color.rgb += g_MateEmissive.rgb;
	
	return Out;
}

//--------------------------
//�e�N�j�b�N
//--------------------------
technique Tech{
	pass P0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();

		CullMode = CCW;
	}
}

//--------------------------
//�֊s�V�F�[�_
//--------------------------

struct InkVS_OUT {
	float4 Pos : POSITION;//�ˉe���W
	float2 UV : TEXCOORD0;//UV
};

InkVS_OUT InkVS(
	float4 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0
) {
	InkVS_OUT Out;

	//���W��@�������ɂ��炷
	pos.xyz += normal * g_InkSize;


	Out.Pos = mul(pos, g_mW);
	Out.Pos = mul(Out.Pos, g_mV);
	Out.Pos = mul(Out.Pos, g_mP);

	Out.UV = uv;

	return Out;
}

struct InkPS_OUT {
	float4 Color:COLOR;
};

InkPS_OUT InkPS(
	InkVS_OUT In
) {
	InkPS_OUT Out;

	float4 texCol = tex2D(g_MateDiffuseSmp, In.UV);//�T���v���̎����Ă���F���擾
	if (texCol.a < 0.1f)discard;//�A���t�@�e�X�g
	Out.Color = g_InkColor;
	return Out;
}

technique InkTech {
	pass P0{
		VertexShader = compile vs_3_0 InkVS();
		PixelShader = compile ps_3_0 InkPS();

		CullMode = CW;//�\�ʃJ�����O���[�h
	}
};

//--------------------------
//���}�b�s���O
//--------------------------

