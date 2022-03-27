#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChShaderParts11.h"

using namespace ChD3D11::ShaderParts;

///////////////////////////////////////////////////////////////////////////////////
//ViewPort Method//
///////////////////////////////////////////////////////////////////////////////////

void ViewPort::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;

	_dc->RSSetViewports(1, &View);
}

///////////////////////////////////////////////////////////////////////////////////
//DrawWindow Method//
///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Init(
	ID3D11Device* _device
	, IDXGISwapChain* _SC)
{

	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_SC))return;

	Release();

	window = _SC;

	ID3D11Texture2D* pBackBuffer = nullptr;

	window->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	_device->CreateRenderTargetView(pBackBuffer, nullptr, &bbTargetView);

	pBackBuffer->Release();

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Release()
{
	if (!*this)return;


	if (ChPtr::NotNullCheck(bbTargetView))
	{
		bbTargetView->Release();
		bbTargetView = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::SetDrawData(ID3D11DeviceContext* _dc,ID3D11DepthStencilView* _dsView)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!*this)return;

	_dc->OMSetRenderTargets(1, &bbTargetView, _dsView);
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::ClearView(ID3D11DeviceContext* _dc,const ChVec4& _color)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!*this)return;

	_dc->ClearRenderTargetView(bbTargetView, _color.val.GetVal());
}

///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Draw()
{
	if (!*this)return;

	window->Present(sEffect, 0);
}

///////////////////////////////////////////////////////////////////////////////////
//ChLightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::Init(ID3D11Device* _device)
{
	Release();

	device = _device;

	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));

	Desc.ByteWidth = sizeof(UseLightData);
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	device->CreateBuffer(&Desc, nullptr, &buf);

	{
		ChVec4 tmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			tmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		lightPow.CreateColorTexture(device, tmpCol, 256, 1);


		D3D11_SAMPLER_DESC samp;

		samp.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		lightPow.SetSampler(samp);
	}



	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::Release()
{
	if (!*this)return;

	if (ChPtr::NotNullCheck(buf))
	{
		buf->Release();
		buf = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightDiffuse(const ChVec3& _dif)
{
	if (!*this)return;

	lightDatas.light.dif = _dif;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetUseLightFlg(const ChStd::Bool& _flg)
{
	if (!*this)return;

	lightDatas.light.useLightFlg = _flg;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightDir(const ChVec3& _dir)
{
	if (!*this)return;

	lightDatas.light.dir = _dir;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightAmbientPow(const float _amb)
{
	if (!*this)return;

	lightDatas.light.ambPow = _amb;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightPos(const ChVec3& _pos, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].pos = _pos;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightLen(const float _len, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].len = _len;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].dif = _dif;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPLightUseFlg(const ChStd::Bool& _flg, const unsigned long _no)
{
	if (!*this)return;
	if (_no > 10)return;

	lightDatas.pLight[_no].useFlg = _flg;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetCamPos(const ChVec3& _camPos)
{
	if (!*this)return;

	lightDatas.camPos = _camPos;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetLightData(const ChLightHeader::LightData& _ld)
{
	if (!*this)return;

	lightDatas.camPos = _ld.camPos;
	lightDatas.light = _ld.light;
	for (unsigned long i = 0; i < 10; i++)
	{
		lightDatas.pLight[i] = _ld.pLight[i];
	}

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	_dc->PSSetConstantBuffers(10, 1, &buf);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	_dc->VSSetConstantBuffers(10, 1, &buf);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetDrawData(ID3D11DeviceContext* _dc)
{

	if (!*this)return;

	Update(_dc);

	_dc->VSSetConstantBuffers(10, 1, &buf);
	_dc->PSSetConstantBuffers(10, 1, &buf);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetImportLightPowMap(ChPtr::Shared<Texture11>& _lightPowMap)
{
	if (!*this)return;

	importLightPowMap = _lightPowMap;
}

///////////////////////////////////////////////////////////////////////////////////

ChLightHeader::LightData ChLightHeader::GetLightData()
{
	LightData Out;

	if (!*this)return Out;

	Out.camPos = lightDatas.camPos;
	Out.light = lightDatas.light;

	for (unsigned long i = 0; i < 10; i++)
	{
		Out.pLight[i] = lightDatas.pLight[i];
	}

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::ClearImportLightPowMap()
{
	if (!*this)return;

	importLightPowMap = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::SetTexture(ID3D11DeviceContext* _dc)
{

	Texture11* tmpLightPow = &lightPow;

	if (importLightPowMap != nullptr)
	{
		if (importLightPowMap->IsTex())
		{
			tmpLightPow = importLightPowMap.get();
		}
	}

	tmpLightPow->SetDrawData(_dc, 10);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLightHeader::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	_dc->UpdateSubresource(buf, 0, nullptr, &lightDatas, 0, 0);

	updateFlg = false;
}