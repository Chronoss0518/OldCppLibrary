
//--------------------------
//���ʃf�[�^
//--------------------------

#include"MCShader.hlsli"

//--------------------------
//���f���f�[�^
//--------------------------

float4 BaseColor = float4(1.0f, 0.0f, 0.0f, 0.0f);

//�s�N�Z���V�F�_(PixelShader)//
//�ʏ�`��//
float4 main(VS_OUT In) :COLOR0
{
	//�J�����̑O���ɂ��邩�̔���//

clip(In.ProPos.x > 1.0f && In.ProPos.x < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.y > 1.0f && In.ProPos.y < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.z > 1.0f && In.ProPos.z < 0.0f ? -1.0f : 1.0f);

	float4 Color = BaseColor;

	clip(Color.a < 1.0f ? -1 : 1);

	return Color;

}
