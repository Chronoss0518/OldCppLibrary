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

		//第一引数にChLibraryの入っているDirectoryPathを選択//
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

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const D3D11_CULL_MODE _CULL)
		{
			if (!*this)return;
			if (IsDraw())return;

			Cull = _CULL;

			RasteriserUpdate = true;
		}

		//描画をする際に利用するフィルタイプをセット//
		inline void SetFillMode(const D3D11_FILL_MODE _Fill)
		{
			if (!*this)return;
			if (IsDraw())return;

			Fill = _Fill;

			RasteriserUpdate = true;
		}

		//ウィンドウハンドルの設定//
		inline void SetWindSize(const ChVec2 _WindSize)
		{
			if (!*this)return;
			if (IsDraw())return;

			WindSize = _WindSize;

		}

		//画面出力後に出力に使用した画像をどうするかの指定//
		inline void SetSwapEffect(const DXGI_SWAP_EFFECT _Effect)
		{
			if (!*this)return;
			if (IsDraw())return;

			BufferDatas = _Effect;
		}

	protected:

		//描画データの初期化//
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

		//描画可能確認関数//
		inline ChStd::Bool IsDraw() { return DrawFlg; }

		ChStd::Bool IsLight() { return LightUseFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始前に呼ぶ関数//
		virtual void DrawStart();

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
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

		//描画後にバックバッファを消去する等のフラグメント//
		DXGI_SWAP_EFFECT BufferDatas = DXGI_SWAP_EFFECT_DISCARD;

		//描画可能フラグ//
		ChStd::Bool DrawFlg = false;

		//描画用//
		ID3D11RenderTargetView* BBTargetView = nullptr;
		ChD3D11::Texture11 DSBuffer;

		//モデルの画像がない場合にセットする//
		ChD3D11::Texture11 WhiteTex;

		//モデルの法線マップがない場合に使用する画像// 
		ChD3D11::Texture11 NormalTex;

		//カリングタイプ//
		D3D11_CULL_MODE Cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//面描画タイプ//
		D3D11_FILL_MODE Fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		//ウィンドウのサイズとポジション//
		ChVec2 WindPos;
		ChVec2 WindSize;

		ID3D11RasterizerState* Rasteriser = nullptr;

		ChStd::Bool RasteriserUpdate = false;

		//背景色//
		ChVec4 BackColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		D3D11_VIEWPORT ViewPort;

		//LightData//

		//ライトの強さを表す画像情報//
		ChD3D11::Texture11 LightEffectTex;

		ChStd::Bool LightUseFlg = false;

		//ライトの強さを設定する画像//
		ChD3D11::Texture11 MyLightTex;

		//専用ライト//
		LambertLight Light = LambertLight();

		//専用ポイントライト//
		PointLights PosLight = PointLights();

	protected:


	};


}

#endif