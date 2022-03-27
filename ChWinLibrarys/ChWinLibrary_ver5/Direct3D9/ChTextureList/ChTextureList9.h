#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture��p��const enum������āASetTexture�̑������ɓ����B
	//�ȍ~�������ɓ��ꂽ�������g����Texture�𑀍삷��B
	typedef class TextureList9:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		~TextureList9()
		{
			Release();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//�����AXFile�t�H���_�[�Ȃǂ�����Ă��Ȃ��ꍇ�͑�������""������B//
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv
			, const std::string _fileInDirectoryPath)
		{
			device = _dv;

			directoryPath = _fileInDirectoryPath;

			SetInitFlg(true);
		}

		inline void Release()
		{

			if (texList.empty())return;
			texList.clear();

			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Texture�̓o�^//
		void SetTexture(
			const std::string& _textureName
			, const ChStd::DataNo _dataNum
			, const unsigned int _gameReSizeWidth
			, const unsigned int _gameReSizeHeight
			, const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

		//�����F�A��{�F�̐ݒ�//
		void SetBlendColor(
			const ChVec4& _color
			, const ChStd::DataNo _dataNum);

		//�摜�̓������ݒ�//
		void SetBlendAlpha(
			const unsigned char _a
			, const ChStd::DataNo _dataNum);

		//���߂��F��Texture�̍쐬//
		//�o�^���邽�߂�_DataNum�͂��Ԃ��Ă͂Ȃ�Ȃ�//
		void SetColorTex(
			const unsigned long& _color
			, const ChStd::DataNo _dataNum
			, const unsigned int _gameReSizeWidth
			, const unsigned int _gameReSizeHeight
			, const unsigned long _type = 0);


		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�O�����p���邽�߂̃e�N�X�`�����擾����//
		inline ChPtr::Shared<Texture9> GetTex(const ChStd::DataNo dataNum)
		{
			if (texList.find(dataNum) == texList.end())return nullptr;

			return texList[dataNum];

		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		std::string directoryPath;

		std::map<ChStd::DataNo, ChPtr::Shared<Texture9>>texList;

		LPDIRECT3DDEVICE9 device;

		///////////////////////////////////////////////////////////////////////////////////

	}ChTexList9;


}


#endif
//CopyRight Chronoss0518 2018/0
