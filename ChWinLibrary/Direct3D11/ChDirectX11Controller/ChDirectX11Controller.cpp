#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChDirectX11Controller.h"

using namespace ChD3D11;

void DirectX3D11::Init(
	const HWND _hWnd
	, const bool _FullScreenFlg
	, const unsigned short _ScrW
	, const unsigned short _ScrH)
{

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

	if (ChPtr::NotNullCheck(Device))Device->Release(); Device = nullptr;
	if (ChPtr::NotNullCheck(DeviceContext))DeviceContext->Release(); DeviceContext = nullptr;
	if (ChPtr::NotNullCheck(Window))Window->Release(); Window = nullptr;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::CreateDevice(
	const HWND _hWnd
	, const unsigned short _ScrW
	, const unsigned short _ScrH)
{

	//�E�B���h�E�ݒ�//


	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = _ScrW;
	scd.BufferDesc.Height = _ScrH;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//�h��ւ��鎞��//
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	//��ʏo��//
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//�n���h���R�Â�//
	scd.OutputWindow = _hWnd;

	//1�s�N�Z���Ɏg�����ԕ⊮�F�̐�//
	scd.SampleDesc.Count = 1;

	//�掿���x��//
	scd.SampleDesc.Quality = 0;

	scd.Windowed = true;


	//DirectX�̋@�\�ݒ�//
	D3D_FEATURE_LEVEL Lv = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr
		, D3D_DRIVER_TYPE_HARDWARE
		, nullptr
		, 0
		, &Lv
		, 1
		, D3D11_SDK_VERSION
		, &scd
		, &Window
		, &Device
		, &Lv
		, &DeviceContext
	);




}