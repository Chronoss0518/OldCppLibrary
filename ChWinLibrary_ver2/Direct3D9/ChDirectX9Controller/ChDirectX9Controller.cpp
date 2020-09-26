
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

using namespace ChD3D9;

void DirectX3D9::Init(
	const HWND _hWnd
	, const bool _FullScreenFlg
	, const unsigned short _ScrW
	, const unsigned short _ScrH)
{



	if (_FullScreenFlg) {

	}
	else {
		RECT rc = { 0,0,_ScrW,_ScrH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(_hWnd, NULL, 10, 10, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!D3D9)
	{
		// オブジェクト作成失敗
		MessageBox(NULL, "Direct3D の作成に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP);
		// 終了する
		PostQuitMessage(0);
		return;
	}
	// 使用するアダプタ番号
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D 初期化パラメータの設定
	if (_FullScreenFlg)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		D3D9->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = _ScrW;
	d3dpp.BackBufferHeight = _ScrH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!_FullScreenFlg)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}

	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//フレーム数の制限解除.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//ﾘｾｯﾄ用に状態情報を保存
	Param = d3dpp;

	if (!CreateD3DXDevice(_hWnd, &d3dpp))
	{
		D3D9->Release();
		PostQuitMessage(0);
		return;
	}

	// レンダリング・ステートを設定//
	// Z バッファ有効化->前後関係の計算を正確にしてくれる//
	ZBufferUseFlg(ChStd::True);

	// アルファブレンディング有効化//
	AlphaBlendUseFlg(ChStd::True);

	// アルファブレンディング方法を設定//
	AlphaBlendSetting();

	// レンダリング時のアルファ値の計算方法の設定//
	RenderSetting();

	//裏面カリング
	SetCullMode(CULL::CCW);

	// フィルタ設定
	SetFilter(D3DTEXF_LINEAR, D3DTEXF_LINEAR, D3DTEXF_LINEAR);

	// ライト
	LightSetting(ChStd::True);

	SetBackBuffer();

	SetFVF((FVF::XYZ | FVF::DIFFUSE | FVF::TEX));

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::Release()
{

	if (ChPtr::NotNullCheck(D3D9))D3D9->Release(); D3D9 = nullptr;
	if (ChPtr::NotNullCheck(BackBuffer))BackBuffer->Release(); BackBuffer = nullptr;
	if (ChPtr::NotNullCheck(Device))Device->Release(); Device = nullptr;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool DirectX3D9::CreateD3DXDevice(const HWND _hWnd
	, D3DPRESENT_PARAMETERS *_d3dpp)
{
	// デバイスの作成 - T&L HAL
	if (FAILED(D3D9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &Device)))
	{
		// 失敗したので HAL で試行
		if (FAILED(D3D9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &Device)))
		{
			// 失敗したので REF で試行
			if (FAILED(D3D9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &Device)))
			{
				// 結局失敗した
				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);

				return ChStd::False;
			}
		}
	}

	return ChStd::True;
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::DrawStart(const D3DCOLOR&
	_BackColor)
{
	// 描画準備
	Device->BeginScene();
	// バックバッファと Z バッファをクリア
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _BackColor, 1.0f, 0);
	
	DFlg = true;

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::DrawEnd(const ChStd::Bool& _RTFlg)
{

	// 描画終了
	Device->EndScene();

	DFlg = false;

	if (_RTFlg)return;

	// バックバッファをプライマリバッファにコピー
	if (FAILED(Device->Present(NULL, NULL, NULL, NULL)))
	{
		Device->Reset(&Param);
	}

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3_9 DirectX3D9::GetOnViewPos(const ChMat_9& _Mat)
{
	Device->BeginScene();

	D3DVIEWPORT9 ViewPort;
	ChMat_9 TmpMat, TmpVMat, TmpPMat;
	ChVec3_9 TmpVec;
	TmpVec = _Mat;

	TmpMat.Identity();

	Device->GetViewport(&ViewPort);

	Device->GetTransform(D3DTS_VIEW, &TmpVMat);
	Device->GetTransform(D3DTS_PROJECTION, &TmpPMat);

	D3DXVec3Project(&TmpVec, &TmpVec, &ViewPort, &TmpPMat, &TmpVMat, &TmpMat);

	Device->EndScene();

	return TmpVec;
}
