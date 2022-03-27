#ifndef Ch_D3D9_BTex_h
#define Ch_D3D9_BTex_h

namespace ChTex
{

	typedef class BaseTexture9:public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetBaseColor(const ChVec4& _col){ col = _col; }

		void SetBaseColor(const D3DCOLOR& _col) { col = D3DColorToColor255(_col); }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//選択した箇所の色取得//
		template<class T>
		T GetColor(
			const unsigned int _width
			, const unsigned int _height);

		inline const LPDIRECT3DTEXTURE9 GetTex()const { return tex; }

		inline const LPDIRECT3DSURFACE9 GetSur()const { return sur; }

		inline const LPDIRECT3DSURFACE9 GetZBu()const { return zBu; }

		float GetSclXSize()const { return scal.x; }

		float GetSclYSize()const { return scal.y; }

		unsigned int GetOriginalWidth()const { return original.w; }

		unsigned int GetOriginalHeight()const { return original.h; }

		ChVec4 GetBaseColor()const { return col; }

		D3DCOLOR GetBaseColD3D()const 
		{
			return D3DCOLOR_ARGB(
				static_cast<unsigned char>(col.a * 255)
				, static_cast<unsigned char>(col.r * 255)
				, static_cast<unsigned char>(col.g * 255)
				, static_cast<unsigned char>(col.b * 255));
		}

		///////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		inline LPDIRECT3DTEXTURE9& InsTex() { return tex; }

		inline LPDIRECT3DSURFACE9& InsSur() { return sur; }

		inline LPDIRECT3DSURFACE9& InsZBu() { return zBu; }

		float&  InsSclXSize() { return scal.x; }

		float&  InsSclYSize() { return scal.y; }

		unsigned int& InsOriginalWidth() { return original.w; }

		unsigned int& InsOriginalHeight() { return original.h; }

		ChVec4& InsBaseColor() { return col; }

		///////////////////////////////////////////////////////////////////////////////////

		//専用拡張子でのインポート//
		static ChVec4 D3DColorToColor255(const D3DCOLOR& _col);

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFucntion//

		//外部ファイルより画像作成//
		void CreateTexture(
			const std::string& _fileName
			, const LPDIRECT3DDEVICE9& _dev
			, const D3DCOLOR& _colKey = D3DCOLOR_ARGB(0, 0, 0, 0));

		//色付き画像作成//
		void CreateColTexture(
			const LPDIRECT3DDEVICE9& _dev
			, const D3DCOLOR& _col = D3DCOLOR_ARGB(255, 255, 255, 255)
			, const unsigned long _w = 1
			, const unsigned long _h = 1);

		//色付き詳細画像作成//
		template<typename T>
		void CreateMinuColTexture(
			const LPDIRECT3DDEVICE9& _dev
			, const T& _col
			, const unsigned long _w = 1
			, const unsigned long _h = 1
			, const _D3DFORMAT _format = D3DFMT_A8R8G8B8
			, const unsigned long _usage = 0
			, const _D3DPOOL _pool = D3DPOOL_MANAGED);

		//サーフェイス作成//
		//※画像作成後に使用//
		inline void CreateSurface(const unsigned int _level)
		{
			if (ChPtr::NullCheck(tex))return;

			tex->GetSurfaceLevel(0, &sur);
		}

		//深度バッファの作成//
		//※画像作成後に使用//
		void CreateZBuffer(
			const LPDIRECT3DDEVICE9& _dev
			, const _D3DFORMAT _format = D3DFMT_D16
			, const _D3DMULTISAMPLE_TYPE _mSample = D3DMULTISAMPLE_NONE
			, const unsigned long _mQuality = 0);

		///////////////////////////////////////////////////////////////////////////////////

		static ChPtr::Shared<BaseTexture9> TextureType(
			const std::string _fileName);

	protected:

		template<typename T>
		inline void SetTexColor(const T& _color);

		LPDIRECT3DTEXTURE9 tex = nullptr;	//テクスチャマップ収納用//
		LPDIRECT3DSURFACE9 sur = nullptr;
		LPDIRECT3DSURFACE9 zBu = nullptr;

		ChMath::Vector2Base<float>scal;//拡縮のサイズ//

		ChMath::Vector2Base<unsigned int>original;//オリジナルのサイズ//

		ChVec4 col{ 1.0f,1.0f,1.0f,1.0f };	//色彩基本色//

		///////////////////////////////////////////////////////////////////////////////////

		virtual void OpenFile(const std::string& _fileName) {};

		///////////////////////////////////////////////////////////////////////////////////

		template<typename T>
		void SetBynaryForStr(
			T& _setData
			, const std::string& _str
			, size_t& _fPos)
		{
			if (_fPos > _str.size())return;
			ChStr::StrBinaryToNum(_setData, _str.c_str(), _fPos);
			_fPos += sizeof(T);

		}


	}Texture9;
}

#endif