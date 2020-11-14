#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChDirectX11Controller.h"

using namespace ChD3D11;

void DirectX3D11::Init(
	HWND _hWnd
	, const ChStd::Bool _FullScreenFlg
	, const unsigned short _ScrW
	, const unsigned short _ScrH
	, const unsigned short _ScrX
	, const unsigned short _ScrY)
{
	if (ChPtr::NullCheck(_hWnd))return;

	
	CreateDevice(_hWnd, _ScrW, _ScrH);


	if (!IsInstanse())
	{
		PostQuitMessage(0);
		return;
	}

	Window->SetFullscreenState(_FullScreenFlg, NULL);

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::Release()
{

	if (ChPtr::NotNullCheck(Device)) { Device->Release(); Device = nullptr; }
	if (ChPtr::NotNullCheck(DContext))
	{
		DContext->ClearState();  DContext->Release(); DContext = nullptr;
	}

	if (ChPtr::NotNullCheck(Window)) { Window->Release(); Window = nullptr; }

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::CreateDevice(
	HWND _hWnd
	, const unsigned short _ScrW
	, const unsigned short _ScrH)
{

	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = _ScrW;
	scd.BufferDesc.Height = _ScrH;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//塗り替える時間//
	//scd.BufferDesc.RefreshRate.Numerator = 0;
	//scd.BufferDesc.RefreshRate.Denominator = 0;

	//画面出力//
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//ハンドル紐づけ//
	scd.OutputWindow = _hWnd;

	//1ピクセルに使う中間補完色の数//
	scd.SampleDesc.Count = 1;

	//画質レベル//
	scd.SampleDesc.Quality = 0;

	scd.Windowed = true;

	//DirectXの機能設定//
	D3D_FEATURE_LEVEL Lv[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL RLv;

	D3D11CreateDeviceAndSwapChain
	(
		NULL
		, D3D_DRIVER_TYPE_HARDWARE
		, NULL
		, D3D11_CREATE_DEVICE_DEBUG
		//,0
		, Lv
		, 1
		, D3D11_SDK_VERSION
		, &scd
		, &Window
		, &Device
		, &RLv
		, &DContext
	);


}