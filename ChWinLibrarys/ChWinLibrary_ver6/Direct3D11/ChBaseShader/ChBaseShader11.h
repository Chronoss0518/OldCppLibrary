#ifndef Ch_D3D11_BShader_h
#define Ch_D3D11_BShader_h

#include"../ChShaderObject/ChShaderObject11.h"

namespace ChD3D11
{

	class Mesh11;
	class Texture11;
	class Sprite11;
	class PolygonBoard11;

	class BaseShader11 :public ChCpp::ChCp::Initializer, public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//Structures//

		struct LambertLight
		{
			ChVec4 Dif = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_11 Dir = ChVec3_11(0.0f, -1.0f, 0.0f);
			float AmbPow = 0.3f;
		};

		struct PointLight
		{

			ChVec3 Dif = ChVec3(1.0f);
			float Len = 1.0f;
			ChVec3_11 Pos = ChVec3_11();
			int Flg = 1;
		};

		struct PointLights
		{
			PointLight Light[8];

			PointLight& operator[](int _Num)
			{
				return Light[_Num];
			}
		};

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//��������ChLibrary�̓����Ă���DirectoryPath��I��//
		void Init(
			ID3D11Device* _d
			, ID3D11DeviceContext* _DC
			, IDXGISwapChain* _SC
			, const ChVec2& _WindPos
			, const ChVec2& _WindSize);

	protected:

		virtual void InitShader() = 0;

	public:

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetBackColor(const ChVec4& _Color)
		{
			if (!*this)return;
			if (IsDraw())return;

			BackColor = _Color;
		}

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const D3D11_CULL_MODE _CULL)
		{
			if (!*this)return;
			if (IsDraw())return;

			Cull = _CULL;

			RasteriserUpdate = true;
		}

		//�`�������ۂɗ��p����t�B���^�C�v���Z�b�g//
		inline void SetFillMode(const D3D11_FILL_MODE _Fill)
		{
			if (!*this)return;
			if (IsDraw())return;

			Fill = _Fill;

			RasteriserUpdate = true;
		}

		//�E�B���h�E�n���h���̐ݒ�//
		inline void SetWindSize(const ChVec2 _WindSize)
		{
			if (!*this)return;
			if (IsDraw())return;

			WindSize = _WindSize;

		}

		//��ʏo�͌�ɏo�͂Ɏg�p�����摜���ǂ����邩�̎w��//
		inline void SetSwapEffect(const DXGI_SWAP_EFFECT _Effect)
		{
			if (!*this)return;
			if (IsDraw())return;

			BufferDatas = _Effect;
		}

	protected:

		//�`��f�[�^�̏�����//
		void SetDrawDatas();

	public:


		void SetLightFlg(const ChStd::Bool _Flg) { LightUseFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline D3D11_CULL_MODE GetCullMode()
		{
			return Cull;
		}

		inline D3D11_FILL_MODE GetFillMode()
		{
			return Fill;
		}

		inline ChVec2 GetWindSize()
		{
			return WindSize;
		}

	protected:

		inline ID3D11Device& GetDevice() { return *Device; }

		inline ID3D11DeviceContext& GetDC() { return *DC; }

		inline IDXGISwapChain& GetSC() { return *Window; }

		inline ChD3D11::Texture11 GetWhiteTex() { return WhiteTex; }

		inline ChD3D11::Texture11 GetNormalTex() { return NormalTex; }

		inline LambertLight& GetLightInstanse() { return Light; }

		inline PointLights& GetPointLightInstanse() { return PosLight; }

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw() { return DrawFlg; }

		ChStd::Bool IsLight() { return LightUseFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n�O�ɌĂԊ֐�//
		virtual void DrawStart();

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		virtual inline void DrawEnd()
		{
			DrawFlg = false;
		}

	protected:

		void DrawWindow();

	private:

		ID3D11Device* Device = nullptr;
		ID3D11DeviceContext* DC = nullptr;
		IDXGISwapChain* Window = nullptr;

		//�`���Ƀo�b�N�o�b�t�@���������铙�̃t���O�����g//
		DXGI_SWAP_EFFECT BufferDatas = DXGI_SWAP_EFFECT_DISCARD;

		//�`��\�t���O//
		ChStd::Bool DrawFlg = false;

		//�`��p//
		ID3D11RenderTargetView* BBTargetView = nullptr;
		ChD3D11::Texture11 DSBuffer;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		ChD3D11::Texture11 WhiteTex;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜// 
		ChD3D11::Texture11 NormalTex;

		//�J�����O�^�C�v//
		D3D11_CULL_MODE Cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//�ʕ`��^�C�v//
		D3D11_FILL_MODE Fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		//�E�B���h�E�̃T�C�Y�ƃ|�W�V����//
		ChVec2 WindPos;
		ChVec2 WindSize;

		ID3D11RasterizerState* Rasteriser = nullptr;

		ChStd::Bool RasteriserUpdate = false;

		//�w�i�F//
		ChVec4 BackColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		D3D11_VIEWPORT ViewPort;

		//LightData//

		//���C�g�̋�����\���摜���//
		ChD3D11::Texture11 LightEffectTex;

		ChStd::Bool LightUseFlg = false;

		//���C�g�̋�����ݒ肷��摜//
		ChD3D11::Texture11 MyLightTex;

		//��p���C�g//
		LambertLight Light = LambertLight();

		//��p�|�C���g���C�g//
		PointLights PosLight = PointLights();

	protected:


	};


}

#endif