#ifndef Ch_D3D9_Li_h
#define Ch_D3D9_Li_h

#include"../../CGameIncludeFile.h"

//Light�p�萔
const enum{ L_POINT = 1,L_SPOT,L_DIRECTIONAL};

class ChLight 
{
private:
	LPDIRECT3DDEVICE9 Device;
	bool PointFlg;
	bool LightFlg;
	void RegisterLight()
	{
		Device->SetLight(0, &Light);
		Device->LightEnable(0, TRUE);
	}

public:
	D3DLIGHT9 Light;

	ChLight(LPDIRECT3DDEVICE9 _Dv);

	D3DLIGHT9 GetLight(void) { return Light; }


	//Light�p�萔��p���ăZ�b�g����
	void SetType(unsigned char _LightTypeNum);

	//Light���g�p���邩���Ȃ����̐ݒ�
	void SetLight(bool Flg) 
	{
		Device->SetRenderState(D3DRS_LIGHTING, Flg); 
		LightFlg = Flg;
	}

	//Light�̈ʒu�̐ݒ�
	void SetPos(const D3DXVECTOR3 *_Pos)
	{
		Light.Position = *_Pos;
		RegisterLight();
	}

	//Light�̊p�x�̐ݒ�
	void SetDir(const D3DXVECTOR3 *_Dir)
	{
		Light.Direction = *_Dir;
		RegisterLight();
	}

	//���C�g�̌��ʋ�����ݒ肷��
	void SetRange(const float _Range)
	{
		Light.Range = _Range;
		RegisterLight();
	}


	//Light�̌����F�̃Z�b�g
	void SetLightDif(const float _a, const float _r, const float _g, const float _b)
	{
		Light.Diffuse.a = _a;
		Light.Diffuse.r = _r;
		Light.Diffuse.g = _g;
		Light.Diffuse.b = _b;
		RegisterLight();
	}

	//Light�̌�����ʂ̃Z�b�g
	void SetLightSpe(bool _SpeFlg, const float _r, const float _g, const float _b)
	{
		Device->SetRenderState(D3DRS_SPECULARENABLE, _SpeFlg);
		Light.Specular.r = _r;
		Light.Specular.g = _g;
		Light.Specular.b = _b;
		RegisterLight();
	}

	//Light�̌�����ʂ̃Z�b�g
	void SetLightAmb(bool _AmbFlg, const float _r, const float _g, const float _b)
	{
		Device->SetRenderState(D3DRS_AMBIENT, _AmbFlg);
		Light.Ambient.r = _r;
		Light.Ambient.g = _g;
		Light.Ambient.b = _b;
		RegisterLight();
	}

	//�ϐ����Ō���̐����̒l��������Α�����قǁA�������f�����C�g�������Ȃ�
	void SetAtt(const float _Attenuation0, const float _Attenuation1, const float _Attenuation2)
	{
		Light.Attenuation0 = _Attenuation0;
		Light.Attenuation1 = _Attenuation1;
		Light.Attenuation2 = _Attenuation2;
		RegisterLight();
	}

};

#endif
//CopyRight Chronoss0518 2018/08