#ifndef Ch_D3D9_StCo_h
#define Ch_D3D9_StCo_h

//(���ǒ�)(�g�p�s��)//
//���̏�ŕ�����p�e�N�X�`���𐶐��A�x�[�X�ƂȂ�e�N�X�`����p�ӂ���K�v������//
//����t�H���_�ɒu���ꂽ�ꕶ���Â̉摜�𑀍삷��R���g���[���[�B//
//�n�߂ɂ��̉摜�Q�̒u���ꂽ�f�B���N�g���p�X����͂���B//
//�摜�T�C�Y�͓��ꂷ��B//

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	typedef class StringController9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDextructer//

		StringController9(
			const LPDIRECT3DDEVICE9 _Dv
			, const std::string& _Path
			, const std::string& _Type
			, const unsigned short _OriginalWedth
			, const unsigned short _OriginalHeight);

		~StringController9() {};

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetStringColor(const ChStd::COLOR255& _Color);

		void SetStringAlpha(const unsigned char _a);

		///////////////////////////////////////////////////////////////////////////////////

		void DrawSprightString(
			const std::string& _Str
			, const ChMat_9& _Mat
			, Sprite9 &_Sp);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		std::string StrPath;
		std::string TypeName;
		unsigned short W;
		unsigned short H;
		ChPtr::Shared<Texture9> StrTex;
		LPDIRECT3DDEVICE9 Device = nullptr;

		///////////////////////////////////////////////////////////////////////////////////

		void SetStrTexture(const std::string& _Str);
		
		///////////////////////////////////////////////////////////////////////////////////


	}StrCon;
}


#endif