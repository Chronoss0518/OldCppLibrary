
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
	class DirectX3D9:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndReleas//

		void Init(
			const HWND _hWnd
			, const bool _fullScreenFlg
			, const unsigned short _scrW
			, const unsigned short _scrH);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//固定機能描画をする際に利用するライトデータをセット//
		inline void SetLight(const ChStd::DataNo _setNo, const D3DLIGHT9 *_light)
		{
			device->SetLight((DWORD)_setNo, _light);
		}

		//固定機能描画をする際に利用するカリングデータをセット//
		inline void SetCullMode(const CULL _cull)
		{
			device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_cull));
		}

		//固定機能描画をする際に利用するテクスチャ描画方法をセット//
		inline void SetFilter(
			_D3DTEXTUREFILTERTYPE _mip
			, _D3DTEXTUREFILTERTYPE _min
			, _D3DTEXTUREFILTERTYPE _mag)
		{
			device->SetSamplerState(0, D3DSAMP_MIPFILTER, _mip);
			device->SetSamplerState(0, D3DSAMP_MINFILTER, _min);
			device->SetSamplerState(0, D3DSAMP_MAGFILTER, _mag);
		}

		//描画を行うためのバックバッファセット//
		inline void SetBackBuffer()
		{
			device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
		}

		//頂点を利用したポリゴンの描画に関するデータのセット//
		inline void SetFVF(unsigned long _FVF)
		{
			device->SetFVF(_FVF);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D9をつかさどるデバイスの取得//
		inline LPDIRECT3DDEVICE9 GetDevice()
		{
			return device;
		}

		//対象のマトリックスに対して画面上での位置を取得//
		ChVec3_9 GetOnViewPos(const ChMat_9& _mat);

		//初期パラメータの取得//
		inline D3DPRESENT_PARAMETERS GetInitParam()
		{
			return param;
		}

		//射影行列の取得//
		inline const ChMat_9 GetCamPMat()
		{
			ChMat_9 proj;
			device->GetTransform(D3DTS_PROJECTION, &proj);
			return proj;
		}

		//ビュー行列の取得//
		inline const ChMat_9 GetCamVMat()
		{
			ChMat_9 view;
			device->GetTransform(D3DTS_VIEW, &view);
			return view;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//固定機能描画可能確認//
		inline ChStd::Bool IsDraw()
		{
			return dFlg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UseFlgFunction//

		//Zバッファ(深度を読み込むバッファ)を利用するか否かのフラグ//
		inline void ZBufferUseFlg(const ChStd::Bool _flg)
		{
			_flg ? device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE)
				: device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

			device->SetRenderState(D3DRS_ZWRITEENABLE, _flg);
		}

		//固定機能でアルファブレンド(透過合成)を利用するか否かのフラグ//
		inline void AlphaBlendUseFlg(const ChStd::Bool _flg)
		{
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, _flg);
			device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, _flg);
		}

		//固定機能でそれぞれのLightを利用するか否かのフラグ
		inline void LightUseFlg(const ChStd::DataNo _setNo, const ChStd::Bool _flg)
		{
			device->LightEnable((DWORD)_setNo, _flg);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SettingFunction//

		//固定機能で描画時にライト計算を行うか否かのフラグ//
		inline void LightSetting(const ChStd::Bool _flg)
		{
			device->SetRenderState(D3DRS_LIGHTING, _flg);
		}

		//固定機能でアルファブレンド(非加算合成)の設定//
		inline void AlphaBlendSetting()
		{
			device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		//固定機能でアルファブレンド(加算合成)の設定//
		inline void AddBlendSetting()
		{
			device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//固定機能で全体の描画設定//
		inline void RenderSetting()
		{
			// レンダリング時のアルファ値の計算方法の設定//
			device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			// テクスチャの色を使用//
			device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			// 頂点の色を使用//
			device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			// レンダリング時の色の計算方法の設定//
			device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Device生成方法//
		ChStd::Bool CreateD3DXDevice(const HWND _hWnd
			, D3DPRESENT_PARAMETERS *_d3dpp);

		///////////////////////////////////////////////////////////////////////////////////

		//デバイスが存在するかしないかの確認//
		inline ChStd::Bool CheckInstanse()
		{
			if (ChPtr::NullCheck(d3d9))return false;
			if (ChPtr::NullCheck(device))return false;
			return true;
		}

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始時に呼ぶ関数//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
		//レンダーターゲット利用した際にFlgをTrueにする//
		void DrawEnd(const ChStd::Bool& _rtFlg = false);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		LPDIRECT3D9 d3d9 = nullptr;
		LPDIRECT3DDEVICE9 device = nullptr;
		LPDIRECT3DSURFACE9 backBuffer = nullptr;

		ChStd::Bool dFlg = false;

		int adapter = 0;
		D3DPRESENT_PARAMETERS param;

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
			static DirectX3D9 ins;
			return ins;
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