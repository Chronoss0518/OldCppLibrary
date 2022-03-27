

#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"../ChMesh/ChMesh11.h"
#include"../ChPolygonBoard/ChPolygonBoard11.h"
#include"../ChSprite/ChSprite11.h"
#include"ChBaseShader11.h"

using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderController11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void BaseShader11::Init(
	ID3D11Device* _Device
	, ID3D11DeviceContext* _DC
	, IDXGISwapChain* _SC
	, const ChVec2& _WindPos
	, const ChVec2& _WindSize) {

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_DC))return;
	if (ChPtr::NullCheck(_SC))return;

	Device = (_Device);
	DC = (_DC);
	Window = _SC;

	WindPos = _WindPos;
	WindSize = _WindSize;

	ViewPort.MaxDepth = 1.0f;
	ViewPort.MinDepth = 0.0f;
	ViewPort.TopLeftX = WindPos.w;
	ViewPort.TopLeftY = WindPos.h;

	ViewPort.Width = WindSize.x;
	ViewPort.Height = WindSize.y;

	WhiteTex.CreateColorTexture(Device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

	NormalTex.CreateColorTexture(Device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	{

		ID3D11Texture2D* pBackBuffer;

		_SC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		_Device->CreateRenderTargetView(pBackBuffer, nullptr, &BBTargetView);

		pBackBuffer->Release();

	}

	DSBuffer.CreateDepthBuffer(Device, WindSize.x, WindSize.y);

	//描画方法//
	D3D11_RASTERIZER_DESC RasteriserDesc
	{
		Fill
		,Cull
		,true
		,0
		,0.0f
		,0.0f
		,false
		,false
		,false
		,false
	};

	Device->CreateRasterizerState(&RasteriserDesc, &Rasteriser);

	DC->RSSetState(Rasteriser);

	{
		ChVec4 TmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			TmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		LightEffectTex.CreateColorTexture(_Device, TmpCol, 256, 1);

	}

	InitShader();

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void BaseShader11::Release()
{

	WhiteTex.Release();
	NormalTex.Release();

	if (ChPtr::NotNullCheck(BBTargetView))
	{
		BBTargetView->Release();
		BBTargetView = nullptr;
	}

}

///////////////////////////////////////////////////////////////////////////////////

void BaseShader11::SetDrawDatas()
{

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (RasteriserUpdate)
	{
		Rasteriser->Release();

		//描画方法//
		D3D11_RASTERIZER_DESC RasteriserDesc
		{
			Fill
			,Cull
			,true
			,0
			,0.0f
			,0.0f
			,false
			,false
			,false
			,false
		};


		Device->CreateRasterizerState(&RasteriserDesc, &Rasteriser);

		DC->RSSetState(Rasteriser);

		RasteriserUpdate = false;

	}

	DC->RSSetState(Rasteriser);

	ViewPort.Width = WindSize.x;
	ViewPort.Height = WindSize.y;
	DC->RSSetViewports(1, &ViewPort);
}

///////////////////////////////////////////////////////////////////////////////////

void BaseShader11::DrawStart()
{

	DC->OMSetRenderTargets(1, &BBTargetView, DSBuffer.GetDSView());
	DC->ClearRenderTargetView(BBTargetView, BackColor.Val.GetVal());
	DSBuffer.ClearDepthBuffer(DC);

	SetDrawDatas();

}

///////////////////////////////////////////////////////////////////////////////////

void BaseShader11::DrawWindow()
{
	Window->Present(BufferDatas, 0);
}
