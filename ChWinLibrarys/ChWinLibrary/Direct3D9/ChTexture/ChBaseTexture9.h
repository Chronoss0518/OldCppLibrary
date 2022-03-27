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

		void SetBaseColor(const ChVec4& _Col){ Col = _Col; }

		void SetBaseColor(const D3DCOLOR& _Col) { Col = D3DColorToColor255(_Col); }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�I�������ӏ��̐F�擾//
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

		ChVec4 GetBaseColor()const { return Col; }

		D3DCOLOR GetBaseColD3D()const 
		{
			return D3DCOLOR_ARGB(
				static_cast<unsigned char>(Col.a * 255)
				, static_cast<unsigned char>(Col.r * 255)
				, static_cast<unsigned char>(Col.g * 255)
				, static_cast<unsigned char>(Col.b * 255));
		}

		///////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		inline LPDIRECT3DTEXTURE9& InsTex() { return Tex; }

		inline LPDIRECT3DSURFACE9& InsSur() { return Sur; }

		inline LPDIRECT3DSURFACE9& InsZBu() { return ZBu; }

		float&  InsSclXSize() { return ScalingX; }

		float&  InsSclYSize() { return ScalingY; }

		unsigned int& InsOriginalWidth() { return OWidth; }

		unsigned int& InsOriginalHeight() { return OHeight; }

		ChVec4& InsBaseColor() { return Col; }

		///////////////////////////////////////////////////////////////////////////////////

		//��p�g���q�ł̃C���|�[�g//
		static ChVec4 D3DColorToColor255(const D3DCOLOR& _Col);

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFucntion//

		//�O���t�@�C�����摜�쐬//
		void CreateTexture(
			const std::string& _FileName
			, const LPDIRECT3DDEVICE9& _Dev
			, const D3DCOLOR& _ColKey = D3DCOLOR_ARGB(0, 0, 0, 0));

		//�F�t���摜�쐬//
		void CreateColTexture(
			const LPDIRECT3DDEVICE9& _Dev
			, const D3DCOLOR& _Col = D3DCOLOR_ARGB(255, 255, 255, 255)
			, const unsigned long _W = 1
			, const unsigned long _H = 1);

		//�F�t���ڍ׉摜�쐬//
		template<typename T>
		void CreateMinuColTexture(
			const LPDIRECT3DDEVICE9& _Dev
			, const T& _Col
			, const unsigned long _W = 1
			, const unsigned long _H = 1
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8
			, const unsigned long _Usage = 0
			, const _D3DPOOL _Pool = D3DPOOL_MANAGED);

		//�T�[�t�F�C�X�쐬//
		//���摜�쐬��Ɏg�p//
		inline void CreateSurface(const unsigned int _Level)
		{
			if (ChPtr::NullCheck(Tex))return;

			Tex->GetSurfaceLevel(0, &Sur);
		}

		//�[�x�o�b�t�@�̍쐬//
		//���摜�쐬��Ɏg�p//
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

		LPDIRECT3DTEXTURE9 Tex = nullptr;	//�e�N�X�`���}�b�v���[�p//
		LPDIRECT3DSURFACE9 Sur = nullptr;
		LPDIRECT3DSURFACE9 ZBu = nullptr;

		float ScalingX = 1.0f;
		float ScalingY = 1.0f;
		unsigned int OWidth;	//�I���W�i���T�C�Y�̉���//
		unsigned int OHeight;	//�I���W�i���T�C�Y�̏c��//
		ChVec4 Col{ 1.0f,1.0f,1.0f,1.0f };	//�F�ʊ�{�F//

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
			ChStr::StrBinaryToNum(_SetData, _Str, _FPos);
			_FPos += sizeof(T);

		}


	}Texture9;
}

#endif