#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture専用のconst enumを作って、SetTextureの第二引数に入れる。
	//以降第二引数に入れた数字を使ってTextureを操作する。
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

		//もし、XFileフォルダーなどを作っていない場合は第二引数に""を入れる。//
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

		//Textureの登録//
		void SetTexture(
			const std::string& _textureName
			, const ChStd::DataNo _dataNum
			, const unsigned int _gameReSizeWidth
			, const unsigned int _gameReSizeHeight
			, const D3DCOLOR _colorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

		//合成可色、基本色の設定//
		void SetBlendColor(
			const ChVec4& _color
			, const ChStd::DataNo _dataNum);

		//画像の透明化設定//
		void SetBlendAlpha(
			const unsigned char _a
			, const ChStd::DataNo _dataNum);

		//決めた色でTextureの作成//
		//登録するための_DataNumはかぶってはならない//
		void SetColorTex(
			const unsigned long& _color
			, const ChStd::DataNo _dataNum
			, const unsigned int _gameReSizeWidth
			, const unsigned int _gameReSizeHeight
			, const unsigned long _type = 0);


		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//外部利用するためのテクスチャを取得する//
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
