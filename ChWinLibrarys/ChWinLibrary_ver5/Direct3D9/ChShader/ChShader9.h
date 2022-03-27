#ifndef Ch_D3D9_Shader_h
#define Ch_D3D9_Shader_h

#include"../ChVertexData9.h"

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;
}

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	class RenderTargetList9;
	class RenderTargetManager9;
}

namespace ChD3D9
{



	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController:public ChCp::Initializer,public ChCp::Releaser
	{

	protected:

		struct LambertLight
		{
			ChVec4 dif = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_9 dir = ChVec3_9(0.0f, -1.0f, 0.0f);
			float ambPow = 0.3f;
		};

		struct PointLight
		{
			PointLight() {}

			ChVec3 dif = ChVec3(1.0f);
			float len = 1.0f;
			ChVec3_9 pos = ChVec3_9();
			bool flg;
		};

		struct Material
		{
			ChVec4 dif;
			ChVec3 speCol;
			float spePow;
		};

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//第一引数にChLibraryの入っているDirectoryPathを選択//
		void Init(const LPDIRECT3DDEVICE9 _d
			, const D3DPRESENT_PARAMETERS& param
			, const float& _windWidth = 1280.0f
			, const float& _windHeight = 720.0f);

	protected:

		void InitShader();

	public:

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const CULL _cull)
		{
			cull = _cull;
			device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_cull));
		}

		//霧効果を使用するか否かのフラグ//
		inline void SetFogFlg(ChStd::Bool _flg) { fogFlg = _flg; }

		//Windサイズの設定//
		inline void SetWindSize(const float _w, const float _h)
		{
			windSize.w = _w;
			windSize.h = _h;
		}

		inline void SetWindSize(const ChVec4& _Size)
		{
			windSize = _Size;
		}

		//自身の用意したライトの強さを表すテクスチャを利用するためのフラグ//
		inline void SetLightPowTexFlg(const ChStd::Bool _Flg)
		{
			if (myLightTex == nullptr)return;
			useMyLightTex = _Flg;
		}

		inline void SetCamPos(const ChVec3_9& _pos) { camPos = _pos; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline LambertLight& GetLightInstanse() { return light; }

		struct PointLights
		{
			PointLight light[7];

			PointLight& operator[](int _Num)
			{
				return light[_Num];
			}
		};

		inline PointLights& GetPointLightInstanse() { return posLight; }

		inline CULL GetCullMode()
		{
			return cull;
		}

		inline ChVec2 GetWindSize()
		{
			return windSize;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _flg);

		//描画可能確認関数//
		inline ChStd::Bool IsDraw()
		{
			return drawFlg;
		}

		inline ChStd::Bool IsRTDraw() { return rtDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始前に呼ぶ関数//
		//ChTex::RenderTargetManager9::SetRT//
		//ChTex::RenderTargetList9::SetRTとは併用できません//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
		//ChTex::RenderTargetManager9::ReturnRT//
		//ChTex::RenderTargetList9::ReturnRTとは併用できません//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh描画用関数//
		void DrawMesh(
			const ChPtr::Shared<ChMesh::Mesh9> _mesh
			, const ChMat_9& _mat = ChMat_9());

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh描画用関数//
		void DrawMeshContour(
			const ChPtr::Shared<ChMesh::Mesh9> _mesh
			, const ChVec4& _color
			, const ChMat_9& _mat = ChMat_9()
			, const float _size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////

		//板ポリゴン描画//
		void DrawPolygonBoard(
			const ChPtr::Shared<ChTex::Texture9>& _tex
			, const VertexData& _vertex
			, const ChMat_9& _mat = ChMat_9()
			, const unsigned int _triangleCount = 2);

		///////////////////////////////////////////////////////////////////////////////////

		//スプライト描画//
		void DrawSprite(
			const ChPtr::Shared<ChTex::Texture9>& _tex
			, const ChMat_9& _mat = ChMat_9()
			, const SpriteData&_spData = SpriteData(ChVec2(0.0f, 0.0f), windSize));

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _lightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////

		friend ChTex::RenderTargetList9;
		friend ChTex::RenderTargetManager9;

	protected:

		//レンダーターゲット用フラグ//
		inline void SetRTDraw(const ChStd::Bool _flg) { rtDrawFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画データの初期化//
		void SetDrawDatas(const D3DCOLOR&
			_backColor);

		///////////////////////////////////////////////////////////////////////////////////

		struct TmpPLight
		{
			
			ChVec3 dif = ChVec3(1.0f);
			ChVec3_9 pos = ChVec3_9();
			float len = 1.0f;
		};

		void MakeBlurFuncNum();

		///////////////////////////////////////////////////////////////////////////////////

		//白色の画像生成関数//
		void MakeWhiteTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//ライトの強さを表すテクスチャの生成//
		void MakeLightingPowTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//法線マップ生成用関数//
		void MakeNormalMapTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//標準マテリアルから自身の使うマテリアル型への変更//
		Material SetMateData(D3DMATERIAL9& _mate);

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		//3Dモデル描画用シェーダー//
		LPDIRECT3DVERTEXSHADER9 bVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 bPModel = nullptr;
		LPDIRECT3DVERTEXSHADER9 cVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 cPModel = nullptr;

		//板ポリゴンなどテクスチャ単体描画用シェーダー//
		LPDIRECT3DVERTEXSHADER9 spVTex = nullptr;
		LPDIRECT3DVERTEXSHADER9 poVTex = nullptr;
		LPDIRECT3DPIXELSHADER9 bPTex = nullptr;

		LPD3DXCONSTANTTABLE pixelCnstant = nullptr;
		LPD3DXCONSTANTTABLE vertexCnstant = nullptr;

		ChStd::Bool allCreateFlg = false;

		//ベースとなる頂点情報//
		LPDIRECT3DVERTEXDECLARATION9 baseDec = nullptr;

		//頂点情報変更用//
		LPDIRECT3DVERTEXDECLARATION9 tVerDec = nullptr;
		LPDIRECT3DVERTEXDECLARATION9 mVerDec = nullptr;

		//モデルの画像がない場合にセットする//
		ChPtr::Shared<ChTex::BaseTexture9>whiteTex = nullptr;

		//モデルの法線マップがない場合に使用する画像//
		ChPtr::Shared<ChTex::BaseTexture9>normalTex = nullptr;

		//ライトの強さを表す画像情報//
		ChPtr::Shared<ChTex::BaseTexture9>lightEffectTex = nullptr;

		//ひとつ前の描画保存用//
		ChPtr::Shared<ChTex::Texture9>beforeTex = nullptr;

		ChStd::Bool lightUseFlg = false;

		//専用ライト//
		LambertLight light = LambertLight();

		//専用ポイントライト//
		PointLights posLight = PointLights();

		ChVec3_9 camPos = ChVec3_9();

		LPDIRECT3DDEVICE9 device = nullptr;

		//Device初期化用パラメータ//
		D3DPRESENT_PARAMETERS param{ 0 };

		LPDIRECT3DCUBETEXTURE9 ambTex = nullptr;

		//ライトの強さを設定する画像//
		ChPtr::Shared<ChTex::Texture9>myLightTex = nullptr;

		ChStd::Bool useMyLightTex = false;

		//描画可能フラグ//
		ChStd::Bool drawFlg = false;
		ChStd::Bool rtDrawFlg = false;

		//フォグ描画フラグ//
		ChStd::Bool fogFlg = false;

		//ウィンドサイズ//
		static ChVec2 windSize;

		//カリングタイプ//
		CULL cull = CULL::NONE;

		///////////////////////////////////////////////////////////////////////////////////

	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController ins;
			return ins;
		}

	protected:

		ShaderController() {}

	};

	static const std::function<ShaderController&()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08