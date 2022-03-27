#ifndef Ch_D3D9_TexMa_h
#define Ch_D3D9_TexMa_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture��p��const enum������āASetTexture�̑������ɓ����B
	//�ȍ~�������ɓ��ꂽ�������g����Texture�𑀍삷��B
	class TextureManager9:public ChCpp::ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(LPDIRECT3DDEVICE9 _Dv);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�e�N�X�`����o�^����//
		//�������ɓo�^����e�N�X�`�����킩��₷�����邽�߂̖��O������//
		void SetTexture(
			const std::string& _TextureName
			, const std::string& _DataName
			, const std::string& _UsePathName
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const D3DCOLOR& _ColorKey = D3DCOLOR_ARGB(255,255,255,255)
		);

		//��{�F�̐ݒ�//
		void SetBlendColor(
			const ChVec4& _Color
			, const std::string _DataName);

		//�摜�̓������ݒ�//
		void SetBlendAlpha(
			const unsigned char _a
			, std::string _DataName);

		//���߂��F��Texture�̍쐬//
		void SetColorTex(
			const unsigned long& _Color
			, const std::string& _DataName
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const unsigned long _Type = 0);

		//���p����e�N�X�`���̓����Ă���f�B���N�g����ݒ肷��//
		//SetTexture���ĂԑO�ɂ��̊֐����Ă�//
		void SetDirectoryPath(
			std::string _DirectoryPath
			, const std::string _UseDirectoryPashName);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�o�^���Ă���e�N�X�`�����擾����//
		inline ChPtr::Shared<Texture9> GetTexture(
			const std::string _DataName)
		{
			if (TexList.empty())return nullptr;
			if (TexList.find(_DataName) == TexList.end())return nullptr;
			return TexList[_DataName];
		}

		//�o�^���Ă���f�B���N�g���p�X�̐����擾//
		inline size_t GetPathCnt() { return PathList.size(); }

		//�o�^���Ă���e�N�X�`���̐����擾//
		inline size_t GetTexCnt() { return TexList.size(); }

		///////////////////////////////////////////////////////////////////////////////////////

		//�Ώۂ̃e�N�X�`�����������//
		void ClearData(const std::string _DataName);

	private:

		std::map<std::string, ChPtr::Shared<BaseTexture9>>TexList;

		std::map<std::string, ChPtr::Shared<std::string>> PathList;

		LPDIRECT3DDEVICE9 Device;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		TextureManager9() {}

		~TextureManager9();

	public:

		static TextureManager9& GetInstance()
		{
			static TextureManager9 Ins;
			return Ins;
		}

	};

	static const std::function<TextureManager9&()>TexManager9 = TextureManager9::GetInstance;
}

#endif