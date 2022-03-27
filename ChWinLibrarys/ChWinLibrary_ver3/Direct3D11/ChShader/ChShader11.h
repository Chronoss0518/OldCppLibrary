#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h

#include"../ChShaderObject/ChShaderObject11.h"

namespace ChD3D11
{
	class Mesh11;
	class Texture11;
	class Sprite11;
	class PolygonBoard11;

	using VSObject = ShaderObject11;
	using PSObject = ShaderObject11;

	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController :public ChCpp::ChCp::InitPack
	{

	protected:

		struct LambertLight
		{
			ChStd::COLOR1f Dif = ChStd::COLOR1f(1.0f, 1.0f, 1.0f, 1.0f);
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

		struct TmpPLight
		{

			ChVec3 Dif = ChVec3(1.0f);
			ChVec3_11 Pos = ChVec3_11();
			float Len = 1.0f;
		};


	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//第一引数にChLibraryの入っているDirectoryPathを選択//
		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _DC
			, IDXGISwapChain* _SC
			, const float& _WindWidth = 1280.0f
			, const float& _WindHeight = 720.0f);

	protected:

		void InitShader();

	public:

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画させるレンダーターゲットを登録する//
		void SetRenderTarget(ChPtr::Shared<Texture11> _Tex);

		inline void SetBackColor(const ChVec4& _Color)
		{
			if (!*this)return;
			if (DrawFlg)return;

			BackColor = _Color;
		}

		//描画対象をバックバッファにする//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (DrawFlg)return;

			RenderTargets.clear();
		}

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const D3D11_CULL_MODE _CULL)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Cull = _CULL;

			RasteriserUpdate = true;
		}

		//描画をする際に利用するフィルタイプをセット//
		inline void SetFilMode(const D3D11_FILL_MODE _Fill)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Fill = _Fill;

			RasteriserUpdate = true;
		}

		//霧効果を使用するか否かのフラグ//
		inline void SetFogFlg(ChStd::Bool _Flg) 
		{
			if (!*this)return;
			if (DrawFlg)return;

			FogFlg = _Flg; 
		}

		//Windサイズの設定//
		inline void SetWindSize(const float _w, const float _h)
		{
			if (!*this)return;
			if (DrawFlg)return;

			WindSize.w = _w;
			WindSize.h = _h;
		}

		inline void SetWindSize(const ChStd::FPOINT& _Size)
		{
			if (!*this)return;
			if (DrawFlg)return;

			WindSize = _Size;
		}

		//自身の用意したライトの強さを表すテクスチャを利用するためのフラグ//
		inline void SetLightPowTexFlg(const ChStd::Bool _Flg)
		{
			if (!*this)return;
			if (DrawFlg)return;

			if (MyLightTex == nullptr)return;
			UseMyLightTex = _Flg;
		}

		inline void SetViewMat(const ChMat_11& _ViewMat)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.ViewMat = _ViewMat;

			BDUpdateFlg = true;

		}

		inline void SetProjMat(const ChMat_11& _ProjMat)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.ProjMat = _ProjMat;

			BDUpdateFlg = true;

		}

		inline void SetWindSize(const ChVec2& _WindSize)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.WindSize = _WindSize;

			BDUpdateFlg = true;

		}

		//inline void SetCamPos(const ChVec3_11& _Pos) { CamPos = _Pos; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline LambertLight& GetLightInstanse() { return Light; }

		struct PointLights
		{
			PointLight Light[7];

			PointLight& operator[](int _Num)
			{
				return Light[_Num];
			}
		};

		inline PointLights& GetPointLightInstanse() { return PosLight; }

		inline D3D11_CULL_MODE GetCullMode()
		{
			return Cull;
		}

		inline D3D11_FILL_MODE GetFillMode()
		{
			return Fill;
		}

		inline ChStd::FPOINT GetWindSize()
		{
			return WindSize;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _Flg);

		//描画可能確認関数//
		inline ChStd::Bool IsDraw()
		{
			return DrawFlg;
		}

		inline ChStd::Bool IsRTDraw() { return RTDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画対象となる画像群の登録を解除する//
		inline void ClearRenderTargets()
		{
			RenderTargets.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始前に呼ぶ関数//
		void DrawStart();

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////
		//Mesh描画群//

		void Draw(
			Mesh11& _Mesh
			, const ChMat_11& _Mat = ChMat_11());

		//ToonShader描画//
		void DrawToons(
			Mesh11& _Mesh
			, const ChStd::COLOR1f& _Color
			, const ChMat_11& _Mat = ChMat_11()
			, const float _Size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//板ポリゴン描画群//

		void Draw(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, PolygonBoard11& _Polygon
			, const ChMat_11& _Mat = ChMat_11());

		//円形で指定範囲を描画//
		void DrawToCircleParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//四角形で指定範囲を描画//
		void DrawSquareParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////
		//Sprite描画群//

		//通常描画//
		void Draw(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, Sprite11& _Sprite
			, const ChMat_11& _Mat = ChMat_11());

		//円形で指定範囲を描画//
		void DrawToCircleParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//四角形で指定範囲を描画//
		void DrawSquareParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _LightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		//レンダーターゲット用フラグ//
		inline void SetRTDraw(const ChStd::Bool _Flg) { RTDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画データの初期化//
		void SetDrawDatas();

		///////////////////////////////////////////////////////////////////////////////////

		void MakeBlurFuncNum();

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		void BaseDataUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		//3Dモデル描画用シェーダー//
		VSObject BVModel;
		PSObject BPModel;
		VSObject PoVTex;
		//ToonSharder用シェーダー//
		VSObject CVModel;
		PSObject CPModel;

		//板ポリゴンなどテクスチャ単体描画用シェーダー//
		VSObject SpVTex;
		PSObject BPTex;


		ChStd::Bool AllCreateFlg = false;

		//描画用//
		ID3D11RenderTargetView* BBTargetView = nullptr;
		ChPtr::Shared<ChD3D11::Texture11>DSBuffer = nullptr;

		//熱感知カメラ用//
		ChPtr::Shared<ChD3D11::Texture11> Temperature = nullptr;
		ChPtr::Shared<ChD3D11::Texture11> TemperaturePowerMap = nullptr;
		//暗視カメラ用//
		ChPtr::Shared<ChD3D11::Texture11> NightVision = nullptr;
		ChPtr::Shared<ChD3D11::Texture11> NightVisionPowerMap = nullptr;

		//ShadowMap生成用//
		ChPtr::Shared<ChD3D11::Texture11> DepthShadowTexture = nullptr;

		//モデルの画像がない場合にセットする//
		ChPtr::Shared<ChD3D11::Texture11>WhiteTex = nullptr;

		//モデルの法線マップがない場合に使用する画像//
		ChPtr::Shared<ChD3D11::Texture11>NormalTex = nullptr;

		//ライトの強さを表す画像情報//
		ChPtr::Shared<ChD3D11::Texture11>LightEffectTex = nullptr;


		ChStd::Bool LightUseFlg = false;

		//描画対象に設定する画像群//
		std::vector<ID3D11RenderTargetView*>RenderTargets;
		ID3D11RenderTargetView** TmpView = nullptr;

		//専用ライト//
		LambertLight Light = LambertLight();

		//専用ポイントライト//
		PointLights PosLight = PointLights();

		ID3D11Device* Device = nullptr;
		ID3D11DeviceContext* DC = nullptr;
		IDXGISwapChain* Window = nullptr;

		//AmbTex = nullptr;

		//ライトの強さを設定する画像//
		ChPtr::Shared<ChD3D11::Texture11>MyLightTex = nullptr;

		ChStd::Bool UseMyLightTex = false;

		//描画可能フラグ//
		ChStd::Bool DrawFlg = false;
		ChStd::Bool RTDrawFlg = false;

		//フォグ描画フラグ//
		ChStd::Bool FogFlg = false;

		//ウィンドサイズ//
		ChStd::FPOINT WindSize;

		//描画後にバックバッファを消去する等のフラグメント//
		DXGI_SWAP_EFFECT BufferDatas = DXGI_SWAP_EFFECT_DISCARD;

		//カリングタイプ//
		D3D11_CULL_MODE Cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//面描画タイプ//
		D3D11_FILL_MODE Fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;


		ID3D11RasterizerState* Rasteriser = nullptr;

		ChStd::Bool RasteriserUpdate = false;

		//背景色//
		ChVec4 BackColor=ChVec4(1.0f,1.0f,1.0f,1.0f);



		struct BaseDatas
		{
			//ビュー変換行列//
			ChMat_11 ViewMat;
			//射影変換行列//
			ChMat_11 ProjMat;
			//画面サイズ//
			ChVec4 WindSize;
		};

		struct CharaDatas
		{
			//モデル行列//
			ChMat_11 ModelMat;
			//スキンメッシュ用行列//
			ChMat_11 SkinWeightMat[1000];

		};

		struct PolygonDatas
		{

			//モデル行列//
			ChMat_11 ModelMat;
			//スプライトベース色//
			ChVec4 BaseColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		};

		ChStd::Bool BDUpdateFlg = true;

		BaseDatas BDObject;
		ConstantBuffer BaseData = nullptr;
		
		CharaDatas CDObject;
		ConstantBuffer CharaData = nullptr;

		PolygonDatas PDObject;
		ConstantBuffer PolygonData = nullptr;

		D3D11_VIEWPORT ViewPort;

		///////////////////////////////////////////////////////////////////////////////////

	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController Ins;
			return Ins;
		}

	protected:

		ShaderController() {}

		~ShaderController() { Release(); }

	};

	static const std::function<ShaderController& ()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08