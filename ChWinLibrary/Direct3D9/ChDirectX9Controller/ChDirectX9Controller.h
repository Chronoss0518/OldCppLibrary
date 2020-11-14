
#ifndef Ch_D3D9_DXCo_h
#define Ch_D3D9_DXCo_h


namespace ChD3D9
{

	//必要と感じる値をすべてわかりやすくしたもの
	namespace FVF
	{
		const unsigned long XYZ = D3DFVF_XYZ;
		const unsigned long DIFFUSE = D3DFVF_DIFFUSE;
		const unsigned long TEX = D3DFVF_TEX1;
		const unsigned long NORMAL = D3DFVF_NORMAL;
	}

	enum class CULL { NONE = 1, CW, CCW };

	//Direct3D9を利用するために作られたクラス//
	//D3DXも内蔵されている//
	class DirectX3D9:public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndReleas//

		void Init(
			const HWND _hWnd
			, const bool _FullScreenFlg
			, const unsigned short _ScrW
			, const unsigned short _ScrH);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//固定機能描画をする際に利用するライトデータをセット//
		inline void SetLight(const ChStd::DataNo _SetNo, const D3DLIGHT9 *_Light)
		{
			Device->SetLight((DWORD)_SetNo, _Light);
		}

		//固定機能描画をする際に利用するカリングデータをセット//
		inline void SetCullMode(const CULL _CULL)
		{
			Device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_CULL));
		}

		//固定機能描画をする際に利用するテクスチャ描画方法をセット//
		inline void SetFilter(
			_D3DTEXTUREFILTERTYPE _Mip
			, _D3DTEXTUREFILTERTYPE _Min
			, _D3DTEXTUREFILTERTYPE _Mag)
		{
			Device->SetSamplerState(0, D3DSAMP_MIPFILTER, _Mip);
			Device->SetSamplerState(0, D3DSAMP_MINFILTER, _Min);
			Device->SetSamplerState(0, D3DSAMP_MAGFILTER, _Mag);
		}

		//描画を行うためのバックバッファセット//
		inline void SetBackBuffer()
		{
			Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
		}

		//頂点を利用したポリゴンの描画に関するデータのセット//
		inline void SetFVF(unsigned long _FVF)
		{
			Device->SetFVF(_FVF);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D9をつかさどるデバイスの取得//
		inline LPDIRECT3DDEVICE9 GetDevice()
		{
			return Device;
		}

		//対象のマトリックスに対して画面上での位置を取得//
		ChVec3_9 GetOnViewPos(const ChMat_9& _Mat);

		//初期パラメータの取得//
		inline D3DPRESENT_PARAMETERS GetInitParam()
		{
			return Param;
		}

		//射影行列の取得//
		inline const ChMat_9 GetCamPMat()
		{
			ChMat_9 Proj;
			Device->GetTransform(D3DTS_PROJECTION, &Proj);
			return Proj;
		}

		//ビュー行列の取得//
		inline const ChMat_9 GetCamVMat()
		{
			ChMat_9 View;
			Device->GetTransform(D3DTS_VIEW, &View);
			return View;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//固定機能描画可能確認//
		inline ChStd::Bool IsDraw()
		{
			return DFlg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UseFlgFunction//

		//Zバッファ(深度を読み込むバッファ)を利用するか否かのフラグ//
		inline void ZBufferUseFlg(const ChStd::Bool _Flg)
		{
			_Flg == ChStd::True ? Device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE)
				: Device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

			Device->SetRenderState(D3DRS_ZWRITEENABLE, _Flg);
		}

		//固定機能でアルファブレンド(透過合成)を利用するか否かのフラグ//
		inline void AlphaBlendUseFlg(const ChStd::Bool _Flg)
		{
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, _Flg);
			Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, _Flg);
		}

		//固定機能でそれぞれのLightを利用するか否かのフラグ
		inline void LightUseFlg(const ChStd::DataNo _SetNo, const ChStd::Bool _Flg)
		{
			Device->LightEnable((DWORD)_SetNo, _Flg);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SettingFunction//

		//固定機能で描画時にライト計算を行うか否かのフラグ//
		inline void LightSetting(const ChStd::Bool _Flg)
		{
			Device->SetRenderState(D3DRS_LIGHTING, _Flg);
		}

		//固定機能でアルファブレンド(非加算合成)の設定//
		inline void AlphaBlendSetting()
		{
			Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		//固定機能でアルファブレンド(加算合成)の設定//
		inline void AddBlendSetting()
		{
			Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//固定機能で全体の描画設定//
		inline void RenderSetting()
		{
			// レンダリング時のアルファ値の計算方法の設定//
			Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			// テクスチャの色を使用//
			Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			// 頂点の色を使用//
			Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			// レンダリング時の色の計算方法の設定//
			Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Device生成方法//
		ChStd::Bool CreateD3DXDevice(const HWND _hWnd
			, D3DPRESENT_PARAMETERS *_d3dpp);

		///////////////////////////////////////////////////////////////////////////////////

		//デバイスが存在するかしないかの確認//
		inline ChStd::Bool CheckInstanse()
		{
			if (ChPtr::NullCheck(D3D9))return ChStd::False;
			if (ChPtr::NullCheck(Device))return ChStd::False;
			return ChStd::True;
		}

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始時に呼ぶ関数//
		void DrawStart(const D3DCOLOR& _BackColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
		//レンダーターゲット利用した際にFlgをTrueにする//
		void DrawEnd(const ChStd::Bool& _RTFlg = false);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		LPDIRECT3D9 D3D9 = nullptr;
		LPDIRECT3DDEVICE9 Device = nullptr;
		LPDIRECT3DSURFACE9 BackBuffer = nullptr;

		ChStd::Bool DFlg = false;

		int adapter = 0;
		D3DPRESENT_PARAMETERS Param;

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DirectX3D9() {}

		inline ~DirectX3D9()
		{
			Release();
		}

	public:

		static DirectX3D9& GetInstans()
		{
			static DirectX3D9 Ins;
			return Ins;
		}


	};

	const static std::function<DirectX3D9&()> D3D9API = DirectX3D9::GetInstans;

	const static std::function<LPDIRECT3DDEVICE9()> D3D9Device
		= []()->LPDIRECT3DDEVICE9 
	{
		return DirectX3D9::GetInstans().GetDevice();
	};
}

#endif