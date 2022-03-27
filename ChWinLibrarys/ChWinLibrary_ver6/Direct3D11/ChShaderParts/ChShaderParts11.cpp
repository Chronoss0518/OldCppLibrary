#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChShaderParts11.h"

using namespace ChD3D11::ShaderParts;

///////////////////////////////////////////////////////////////////////////////////
//ViewPort Method//
///////////////////////////////////////////////////////////////////////////////////

void ViewPort::SetDrawData(ID3D11DeviceContext* _DC)
{
	if (ChPtr::NullCheck(_DC))return;

	_DC->RSSetViewports(1, &View);
}

///////////////////////////////////////////////////////////////////////////////////
//DrawWindow Method//
///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Init(
	ID3D11Device* _Device
	, IDXGISwapChain* _SC)
{

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_SC))return;

	Release();

	Window = _SC;

	ID3D11Texture2D* pBackBuffer = nullptr;

	Window->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	_Device->CreateRenderTargetView(pBackBuffer, nullptr, &BBTargetView);

	pBackBuffer->Release();

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Release()
{
	if (!*this)return;


	if (ChPtr::NotNullCheck(BBTargetView))
	{
		BBTargetView->Release();
		BBTargetView = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::SetDrawData(ID3D11DeviceContext* _DC,ID3D11DepthStencilView* _DSView)
{
	if (ChPtr::NullCheck(_DC))return;
	if (!*this)return;

	_DC->OMSetRenderTargets(1, &BBTargetView, _DSView);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::ClearView(ID3D11DeviceContext* _DC,const ChVec4& _Color)
{
	if (ChPtr::NullCheck(_DC))return;
	if (!*this)return;

	_DC->ClearRenderTargetView(BBTargetView, _Color.Val.GetVal());
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Draw()
{
	if (!*this)return;

	Window->Present(SEffect, 0);
}
