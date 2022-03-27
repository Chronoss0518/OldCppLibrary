#ifndef Ch_D3D9_DiLi_h
#define Ch_D3D9_DiLi_h

//Light�p�萔//
const enum{ L_POINT = 1,L_SPOT,L_DIRECTIONAL};

//�g����//
//�W���@�\�ŗ��p����Light�̐ݒ�(���㗘�p����\����)//
class ChLight9
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestRucter//

	ChLight9(LPDIRECT3DDEVICE9 _Dv);

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//Light���g�p���邩���Ȃ����̐ݒ�//
	void SetLight(bool Flg);

	//Light�̊p�x�̐ݒ�//
	void SetDir(const ChVec3_9& _Dir);

	//Light�̊p�x�̐ݒ�//
	void SetPos(const D3DXVECTOR3 *_Pos);

	//Light�̌����F�̃Z�b�g//
	void SetLightDif(const float _a, const float _r, const float _g, const float _b);

	//Light�̌�����ʂ̃Z�b�g//
	void SetLightSpe(bool _SpeFlg, const float _r, const float _g, const float _b);

	//Light�̌�����ʂ̃Z�b�g//
	void SetLightAmb(bool _AmbFlg, const float _r, const float _g, const float _b);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	const inline D3DLIGHT9* GetLight(void) { return &Light; }

	///////////////////////////////////////////////////////////////////////////////////

private:

	LPDIRECT3DDEVICE9 Device;

	void RegisterLight();

	D3DLIGHT9 Light;

};

#endif
//CopyRight Chronoss0518 2018/08

