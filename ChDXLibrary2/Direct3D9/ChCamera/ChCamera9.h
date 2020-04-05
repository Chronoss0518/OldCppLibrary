#ifndef Ch_D3D9_Cam_h
#define Ch_D3D9_Cam_h

namespace ChSystem
{
	class BaseSystem;
}

//(���ǒ�)//
//��{�I��View.Projection�s���ݒ肷�邽�߂̃N���X//
class ChCamera9:public ChCpp::ChCp::InitPack
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChCamera9(const LPDIRECT3DDEVICE9 _Dv,const ChSystem::BaseSystem* _Sys);

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//�J�����̈ʒu�ݒ�//
	void SetCamPos(const D3DXVECTOR3& _CamPos) { CamP = _CamPos; }

	//�J�����̌���ʒu�̐ݒ�//
	void SetCamLook(const D3DXVECTOR3& _CamLook) { CamL = _CamLook; }

	//�f�[�^���r���[�s��ɐݒ�//
	void SetView();

	//�`�悷��ő勗���ݒ�//
	void SetLookMaxLen(const float _Len) { LookMaxLen = _Len; }

	//�J�����̏�����̌������o�����߂̃}�g���b�N�X�̐ݒ�//
	void SetCamMat(const ChMatrix_9 *_Mat) { CamHMat = *_Mat; }

	//�Œ�@�\�`����s���ۂ̖����ʐݒ�//
	void SetFog(const bool _Flg
		, const float _LookMin
		, const float _LookMax
		, const D3DCOLOR _color);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	//�J�����̌��݈ʒu�擾//
	inline D3DXVECTOR3 GetCamPos() { return CamP; }

	//�J�����̌��Ă���ʒu�擾//
	inline D3DXVECTOR3 GetCamLook() { return CamL; }

	///////////////////////////////////////////////////////////////////////////////////

	//�J�����̕`�悷�邽�߂��Ő���̊p�x//
	void ZoomUpRadian(const float _UpRad);

	///////////////////////////////////////////////////////////////////////////////////

	//�J�����̃x�[�X�ƂȂ��Ő���̊p�x�ɖ߂�//
	void  ReSetForFalcomDeg() { ForFalcomDeg = StartForFalcomDeg; }


private:

	LPDIRECT3DDEVICE9 Device = nullptr;
	ChSystem::BaseSystem* System = nullptr;
	float LookMaxLen;
	float FogMin, FogMax;
	float ForFalcomDeg = 60;
	float StartForFalcomDeg = 60;
	ChVec3_9 CamH;
	ChVec3_9 CamP, CamL;
	ChMat_9 CamHMat;

};

#endif
//CopyRight Chronoss0518 2018/08