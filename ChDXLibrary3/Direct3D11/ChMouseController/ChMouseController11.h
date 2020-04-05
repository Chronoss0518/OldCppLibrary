#ifndef Ch_D3D9_Mou_h
#define Ch_D3D9_Mou_h

namespace ChSystem
{
	class Windows;
}

//�}�E�X���Ǘ�����N���X//
//Windows�ł̂݋@�\����//
typedef class ChMouseController9 {
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChMouseController9(
		const ChStd::Bool _MouseCamSetFlg
		, const ChSystem::Windows* _Win);

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//�J�[�\���摜���Z�b�g����֐�//
	inline void SetCursorTex(const std::string _TexName) { CursorTexName = _TexName; }

	//�J�[�\���̈ʒu���Z�b�g����֐�//
	void SetCursolOffsetPos(void);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	//�J�[�\���̓������ʂ�Ԃ��֐�//
	void GetMovePos(ChStd::FPOINT *_OutMoveVec);

	//�J�[�\����3D��ԏ�łǂ̈ʒu�ɑ��݂��邩���`�F�b�N����֐�//
	//(���e�X�g)//
	void GetCamCursorPos(
		const D3DXVECTOR3 *_CamPos
		,const D3DXVECTOR3 *_CamLook
		, D3DXVECTOR3 *_OutVec);

	//�J�[�\���摜�𗘗p����ۂ̒l��Ԃ��֐�//
	inline std::string GetCursorTexNo(){ return CursorTexName; }

	///////////////////////////////////////////////////////////////////////////////////

	//�W���̃J�[�\����������悤�ɂ��邩�̃t���O//
	inline void ShouFlg(const ChStd::Bool _f) { ShowCursor(_f); }

	///////////////////////////////////////////////////////////////////////////////////

private:
	HWND hWind;
	POINT MouSPos;
	POINT MouNPos;
	ChStd::Bool MouseCamLFlg;
	std::string CursorTexName;

}ChMouCon,*LpMouCon;

#endif
//CopyRight Chronoss0518 2018/08