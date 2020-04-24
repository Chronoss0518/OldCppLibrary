#ifndef Ch_D3D9_TexL_h
#define Ch_D3D9_TexL_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture専用のconst enumを作って、SetTextureの第二引数に入れる。
	//以降第二引数に入れた数字を使ってTextureを操作する。
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

		//もし、XFileフォルダーなどを作っていない場合は第二引数に""を入れる。//
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

		//Textureの登録//
		void SetTexture(
			const std::string& _TextureName
			, const ChStd::DataNo DataNum
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const D3DCOLOR ColorKey = D3DCOLOR_ARGB(0, 0, 0, 0)
		);

		//合成可色、基本色の設定//
		void SetBlendColor(
			const ChStd::COLOR255& _Color
			, const ChStd::DataNo _DataNum);

		//画像の透明化設定//
		void SetBlendAlpha(
			const unsigned char _a
			, const ChStd::DataNo _DataNum);

		//決めた色でTextureの作成//
		//登録するための_DataNumはかぶってはならない//
		void SetColorTex(
			const unsigned long& _Color
			, const ChStd::DataNo _DataNum
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const unsigned long _Type = 0);


		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//外部利用するためのテクスチャを取得する//
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
