#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChShader���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

void ChEffect::SmpXfileDraw(const LpChSmpX _x,const D3DXMATRIX *_Mat, ChEffectType _Type)
{
	
	SetVPMatrix();

	//�ˉe�s��ƃr���[�s��̃Z�b�g
	Effect->SetMatrix("g_mW", _Mat);

	Effect->SetTechnique("Tech");//�e�N�j�b�N�Z���N�g

	Effect->Begin(0, 0);//�e�N�j�b�N�X�^�[�g

	Effect->BeginPass(0);//�p�X�X�^�[�g




	for (int i = 0; i < _x->NumMaterial; i++) {

		D3DMATERIAL9* mate = ((_x->Mat) + i);
		//diffuse���Z�b�g
		Effect->SetVector("g_MateDiffuse", (D3DXVECTOR4*)&mate->Diffuse);

		//specura�̃Z�b�g
		Effect->SetVector("g_MateSpecular", (D3DXVECTOR4 *)&mate->Specular);
		Effect->SetFloat("g_MateSpePower", mate->Power);

		//���ȏƖ�(�G�~�b�V�u)
		Effect->SetVector("g_MateEmissive", (D3DXVECTOR4*)&mate->Emissive);

		LPDIRECT3DTEXTURE9 pTex = nullptr;

		pTex = *_x->Tex;

		if (pTex == nullptr)pTex = WhiteTexture;//Texture���擾�ł��Ȃ������Ƃ��ɔ��F�̃e�N�X�`�����Z�b�g����B

		Effect->SetTexture("g_MateDiffuseTex", *_x->Tex);

		Effect->SetTexture("g_ToonTex",LightEffectTex[_Type]);
		//�f�[�^�̃Z�b�g��҂�
		Effect->CommitChanges();
		_x->LpMesh->DrawSubset(i);
	}


	Effect->EndPass();

	Effect->End();


}

#endif