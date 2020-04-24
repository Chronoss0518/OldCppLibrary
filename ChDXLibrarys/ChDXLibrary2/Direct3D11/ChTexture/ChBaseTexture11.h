#ifndef Ch_D3D9_BTex_h
#define Ch_D3D9_BTex_h

namespace ChTex
{

	typedef class BaseTexture9
	{
	public:


		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseTexture9() {}

		virtual ~BaseTexture9() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetBaseColor(const ChStd::COLOR255& _Col){ Col = _Col; }

		void SetBaseColor(const D3DCOLOR& _Col) { Col = D3DColorToColor255(_Col); }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//選択した箇所の色取得//
		template<class T>
		T GetColor(
			const unsigned int _Width
			, const unsigned int _Height);

		inline const LPDIRECT3DTEXTURE9 GetTex()const { return Tex; }

		inline const LPDIRECT3DSURFACE9 GetSur()const { return Sur; }

		inline const LPDIRECT3DSURFACE9 GetZBu()const { return ZBu; }

		float GetSclXSize()const { return ScalingX; }

		float GetSclYSize()const { return ScalingY; }

		unsigned int GetOriginalWidth()const { return OWidth; }

		unsigned int GetOriginalHeight()const { return OHeight; }

		ChStd::COLOR255 GetBaseColor()const { return Col; }

		D3DCOLOR GetBaseColD3D()const { return D3DCOLOR_ARGB(Col.a, Col.r, Col.g, Col.b); }

		///////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		inline LPDIRECT3DTEXTURE9& InsTex() { return Tex; }

		inline LPDIRECT3DSURFACE9& InsSur() { return Sur; }

		inline LPDIRECT3DSURFACE9& InsZBu() { return ZBu; }

		float&  InsSclXSize() { return ScalingX; }

		float&  InsSclYSize() { return ScalingY; }

		unsigned int& InsOriginalWidth() { return OWidth; }

		unsigned int& InsOriginalHeight() { return OHeight; }

		ChStd::COLOR255& InsBaseColor() { return Col; }

		///////////////////////////////////////////////////////////////////////////////////

		//専用拡張子でのインポート//
		static ChStd::COLOR255 D3DColorToColor255(const D3DCOLOR& _Col);

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFucntion//

		//外部ファイルより画像作成//
		void CreateTexture(
			const std::string& _FileName
			, const LPDIRECT3DDEVICE9& _Dev
			, const D3DCOLOR& _ColKey = D3DCOLOR_ARGB(255, 255, 255, 255));

		//色付き画像作成//
		void CreateColTexture(
			const LPDIRECT3DDEVICE9& _Dev
			, const D3DCOLOR& _Col = D3DCOLOR_ARGB(255, 255, 255, 255)
			, const unsigned long _W = 1
			, const unsigned long _H = 1);

		//色付き詳細画像作成//
		template<typename T>
		void CreateMinuColTexture(
			const LPDIRECT3DDEVICE9& _Dev
			, const T& _Col
			, const unsigned long _W = 1
			, const unsigned long _H = 1
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8
			, const unsigned long _Usage = 0
			, const _D3DPOOL _Pool = D3DPOOL_MANAGED);

		//サーフェイス作成//
		//※画像作成後に使用//
		inline void CreateSurface(const unsigned int _Level)
		{
			if (ChPtr::NullCheck(Tex))return;

			Tex->GetSurfaceLevel(0, &Sur);
		}

		//深度バッファの作成//
		//※画像作成後に使用//
		void CreateZBuffer(
			const LPDIRECT3DDEVICE9& _Dev
			, const _D3DFORMAT _FMT = D3DFMT_D16
			, const _D3DMULTISAMPLE_TYPE _MSample = D3DMULTISAMPLE_NONE
			, const unsigned long _MQuality = 0);

		///////////////////////////////////////////////////////////////////////////////////

		static ChPtr::Shared<BaseTexture9> TextureType(
			const std::string _FileName);

	protected:

		template<typename T>
		inline void SetTexColor(const T& _Color);

		LPDIRECT3DTEXTURE9 Tex = nullptr;	//テクスチャマップ収納用//
		LPDIRECT3DSURFACE9 Sur = nullptr;
		LPDIRECT3DSURFACE9 ZBu = nullptr;

		float ScalingX = 1.0f;
		float ScalingY = 1.0f;
		unsigned int OWidth;	//オリジナルサイズの横幅//
		unsigned int OHeight;	//オリジナルサイズの縦幅//
		ChStd::COLOR255 Col{ 255,255,255,255 };	//色彩基本色//

		///////////////////////////////////////////////////////////////////////////////////

		virtual void OpenFile(const std::string& _FileName) {};

		///////////////////////////////////////////////////////////////////////////////////

		template<typename T>
		void SetBynaryForStr(
			T& _SetData
			, const std::string& _Str
			, size_t& _FPos)
		{
			if (_FPos > _Str.size())return;
			ChStd::StrBinaryToNum(_SetData, _Str, _FPos);
			_FPos += sizeof(T);

		}


	}Texture9;
}

#endif