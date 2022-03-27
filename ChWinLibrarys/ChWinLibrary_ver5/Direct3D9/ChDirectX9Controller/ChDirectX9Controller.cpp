
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

using namespace ChD3D9;

void DirectX3D9::Init(
	const HWND _hWnd
	, const bool _fullScreenFlg
	, const unsigned short _scrW
	, const unsigned short _scrH)
{

	if (_fullScreenFlg) {

	}
	else {
		RECT rc = { 0,0,_scrW,_scrH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(_hWnd, NULL, 10, 10, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d9)
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
	if (_fullScreenFlg)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		//		d3dpp.backBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		d3d9->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = _scrW;
	d3dpp.BackBufferHeight = _scrH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!_fullScreenFlg)
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
	param = d3dpp;

	if (!CreateD3DXDevice(_hWnd, &d3dpp))
	{
		d3d9->Release();
		PostQuitMessage(0);
		return;
	}

	// レンダリング・ステートを設定//
	// Z バッファ有効化->前後関係の計算を正確にしてくれる//
	ZBufferUseFlg(true);

	// アルファブレンディング有効化//
	AlphaBlendUseFlg(true);

	// アルファブレンディング方法を設定//
	AlphaBlendSetting();

	// レンダリング時のアルファ値の計算方法の設定//
	RenderSetting();

	//裏面カリング
	SetCullMode(CULL::CCW);

	// フィルタ設定
	SetFilter(D3DTEXF_LINEAR, D3DTEXF_LINEAR, D3DTEXF_LINEAR);

	// ライト
	LightSetting(true);

	SetBackBuffer();

	SetFVF((FVF::XYZ | FVF::DIFFUSE | FVF::TEX));

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::Release()
{

	if (ChPtr::NotNullCheck(d3d9))d3d9->Release(); d3d9 = nullptr;
	if (ChPtr::NotNullCheck(backBuffer))backBuffer->Release(); backBuffer = nullptr;
	if (ChPtr::NotNullCheck(device))device->Release(); device = nullptr;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool DirectX3D9::CreateD3DXDevice(const HWND _hWnd
	, D3DPRESENT_PARAMETERS *_d3dpp)
{
	// デバイスの作成 - T&L HAL
	if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &device)))
	{
		// 失敗したので HAL で試行
		if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
		{
			// 失敗したので REF で試行
			if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
			{
				// 結局失敗した
				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);

				return false;
			}
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::DrawStart(const D3DCOLOR&
	_BackColor)
{
	// 描画準備
	device->BeginScene();
	// バックバッファと Z バッファをクリア
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _BackColor, 1.0f, 0);
	
	dFlg = true;

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::DrawEnd(const ChStd::Bool& _RTFlg)
{

	// 描画終了
	device->EndScene();

	dFlg = false;

	if (_RTFlg)return;

	// バックバッファをプライマリバッファにコピー
	if (FAILED(device->Present(NULL, NULL, NULL, NULL)))
	{
		device->Reset(&param);
	}

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3_9 DirectX3D9::GetOnViewPos(const ChMat_9& _Mat)
{
	device->BeginScene();

	D3DVIEWPORT9 ViewPort;
	ChMat_9 TmpMat, TmpVMat, TmpPMat;
	ChVec3_9 TmpVec;
	TmpVec = _Mat;

	TmpMat.Identity();

	device->GetViewport(&ViewPort);

	device->GetTransform(D3DTS_VIEW, &TmpVMat);
	device->GetTransform(D3DTS_PROJECTION, &TmpPMat);

	D3DXVec3Project(&TmpVec, &TmpVec, &ViewPort, &TmpPMat, &TmpVMat, &TmpMat);

	device->EndScene();

	return TmpVec;
}
