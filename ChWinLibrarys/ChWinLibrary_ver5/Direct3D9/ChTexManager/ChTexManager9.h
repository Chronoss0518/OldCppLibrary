#ifndef Ch_D3D9_TexMa_h
#define Ch_D3D9_TexMa_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture��p��const enum������āASetTexture�̑������ɓ����B
	//�ȍ~�������ɓ��ꂽ�������g����Texture�𑀍삷��B
	class TextureManager9:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(LPDIRECT3DDEVICE9 _dv);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�e�N�X�`����o�^����//
		//�������ɓo�^����e�N�X�`�����킩��₷�����邽�߂̖��O������//
		void SetTexture(
			const std::string& _textureName
			, const std::string& _dataName
			, const std::string& _usePathName
			, const unsigned int _gameReSizeWidth
			, const unsigned int _gameReSizeHeight
			, const D3DCOLOR& _colorKey = D3DCOLOR_ARGB(255,255,255,255)
		);

		//��{�F�̐ݒ�//
		void SetBlendColor(
			const ChVec4& _color
			, const std::string _dataName);

		//�摜�̓������ݒ�//
		void SetBlendAlpha(
			const unsigned char _a
			, std::string _dataName);

		//���߂��F��Texture�̍쐬//
		void SetColorTex(
			const unsigned long& _color
			, const std::string& _dataName
			, const unsigned int _gameReSizeWidth
			, const unsigned int _gameReSizeHeight
			, const unsigned long _type = 0);

		//���p����e�N�X�`���̓����Ă���f�B���N�g����ݒ肷��//
		//SetTexture���ĂԑO�ɂ��̊֐����Ă�//
		void SetDirectoryPath(
			std::string _directoryPath
			, const std::string _useDirectoryPashName);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�o�^���Ă���e�N�X�`�����擾����//
		inline ChPtr::Shared<Texture9> GetTexture(
			const std::string _dataName)
		{
			if (texList.empty())return nullptr;
			if (texList.find(_dataName) == texList.end())return nullptr;
			return texList[_dataName];
		}

		//�o�^���Ă���f�B���N�g���p�X�̐����擾//
		inline size_t GetPathCnt() { return pathList.size(); }

		//�o�^���Ă���e�N�X�`���̐����擾//
		inline size_t GetTexCnt() { return texList.size(); }

		///////////////////////////////////////////////////////////////////////////////////////

		//�Ώۂ̃e�N�X�`�����������//
		void ClearData(const std::string _DataName);

	private:

		std::map<std::string, ChPtr::Shared<BaseTexture9>>texList;

		std::map<std::string, ChPtr::Shared<std::string>> pathList;

		LPDIRECT3DDEVICE9 device;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		TextureManager9() {}

		~TextureManager9();

	public:

		static TextureManager9& GetInstance()
		{
			static TextureManager9 ins;
			return ins;
		}

	};

	static const std::function<TextureManager9&()>TexManager9 = TextureManager9::GetInstance;
}

#endif