#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../BaseIncluder/ChD3D11I.h"

#include"ChDirectX11Controller.h"

using namespace ChD3D11;

void DirectX3D11::Init(
	HWND _hWnd
	, const ChStd::Bool _fullScreenFlg
	, const unsigned short _scrW
	, const unsigned short _scrH
	, const unsigned short _scrX
	, const unsigned short _scrY)
{
	if (ChPtr::NullCheck(_hWnd))return;

	
	CreateDevice(_hWnd, _scrW, _scrH);


	if (!IsInstanse())
	{
		PostQuitMessage(0);
		return;
	}

	window->SetFullscreenState(_fullScreenFlg, NULL);

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::Release()
{

	if (ChPtr::NotNullCheck(device)) { device->Release(); device = nullptr; }
	if (ChPtr::NotNullCheck(dContext))
	{
		dContext->ClearState();  dContext->Release(); dContext = nullptr;
	}

	if (ChPtr::NotNullCheck(window)) { window->Release(); window = nullptr; }

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::CreateDevice(
	HWND _hWnd
	, const unsigned short _scrW
	, const unsigned short _scrH)
{

	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = _scrW;
	scd.BufferDesc.Height = _scrH;
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
	D3D_FEATURE_LEVEL lv[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL rLv;

	D3D11CreateDeviceAndSwapChain
	(
		NULL
		, D3D_DRIVER_TYPE_HARDWARE
		, NULL
		, D3D11_CREATE_DEVICE_DEBUG
		//,0
		, lv
		, 1
		, D3D11_SDK_VERSION
		, &scd
		, &window
		, &device
		, &rLv
		, &dContext
	);


}