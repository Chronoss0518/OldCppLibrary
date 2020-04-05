#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture��p��const enum������āASetTexture�̑������ɓ����B
	//�ȍ~�������ɓ��ꂽ�������g����Texture�𑀍삷��B
	typedef class TextureList9
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
			const LPDIRECT3DDEVICE9 _Dv
			, const std::string _FileInDirectoryPath)
		{
			Device = _Dv;

			DirectoryPath = _FileInDirectoryPath;
		}

		inline void Release()
		{

			if (TexList.empty())return;
			TexList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Texture�̓o�^//
		void SetTexture(
			const std::string& _TextureName
			, const ChStd::DataNo DataNum
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const D3DCOLOR ColorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

		//�����F�A��{�F�̐ݒ�//
		void SetBlendColor(
			const ChStd::COLOR255& _Color
			, const ChStd::DataNo _DataNum);

		//�摜�̓������ݒ�//
		void SetBlendAlpha(
			const unsigned char _a
			, const ChStd::DataNo _DataNum);

		//���߂��F��Texture�̍쐬//
		//�o�^���邽�߂�_DataNum�͂��Ԃ��Ă͂Ȃ�Ȃ�//
		void SetColorTex(
			const unsigned long& _Color
			, const ChStd::DataNo _DataNum
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const unsigned long _Type = 0);


		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�O�����p���邽�߂̃e�N�X�`�����擾����//
		inline ChPtr::Shared<Texture9> GetTex(const ChStd::DataNo DataNum)
		{
			if (TexList.find(DataNum) == TexList.end())return nullptr;

			return TexList[DataNum];

		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		std::string DirectoryPath;

		std::map<ChStd::DataNo, ChPtr::Shared<Texture9>>TexList;

		LPDIRECT3DDEVICE9 Device;

		///////////////////////////////////////////////////////////////////////////////////

	}ChTexList9;


}


#endif
//CopyRight Chronoss0518 2018/0
