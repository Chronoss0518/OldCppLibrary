#ifndef Ch_D3D9_TexMa_h
#define Ch_D3D9_TexMa_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//Texture専用のconst enumを作って、SetTextureの第二引数に入れる。
	//以降第二引数に入れた数字を使ってTextureを操作する。
	class TextureManager9:public ChCpp::ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(LPDIRECT3DDEVICE9 _Dv);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//テクスチャを登録する//
		//第二引数に登録するテクスチャをわかりやすくするための名前を入れる//
		void SetTexture(
			const std::string& _TextureName
			, const std::string& _DataName
			, const std::string& _UsePathName
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const D3DCOLOR& _ColorKey = D3DCOLOR_ARGB(255,255,255,255)
		);

		//基本色の設定//
		void SetBlendColor(
			const ChVec4& _Color
			, const std::string _DataName);

		//画像の透明化設定//
		void SetBlendAlpha(
			const unsigned char _a
			, std::string _DataName);

		//決めた色でTextureの作成//
		void SetColorTex(
			const unsigned long& _Color
			, const std::string& _DataName
			, const unsigned int _GameReSizeWidth
			, const unsigned int _GameReSizeHeight
			, const unsigned long _Type = 0);

		//利用するテクスチャの入っているディレクトリを設定する//
		//SetTextureを呼ぶ前にこの関数を呼ぶ//
		void SetDirectoryPath(
			std::string _DirectoryPath
			, const std::string _UseDirectoryPashName);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//登録してあるテクスチャを取得する//
		inline ChPtr::Shared<Texture9> GetTexture(
			const std::string _DataName)
		{
			if (TexList.empty())return nullptr;
			if (TexList.find(_DataName) == TexList.end())return nullptr;
			return TexList[_DataName];
		}

		//登録してあるディレクトリパスの数を取得//
		inline size_t GetPathCnt() { return PathList.size(); }

		//登録してあるテクスチャの数を取得//
		inline size_t GetTexCnt() { return TexList.size(); }

		///////////////////////////////////////////////////////////////////////////////////////

		//対象のテクスチャを解放する//
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