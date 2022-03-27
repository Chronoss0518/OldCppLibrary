
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include<DirectXTex.h>
#include<WICTextureLoader11.h>

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib, "DirectXTex_MDd.lib")
#else
#pragma comment(lib, "DirectXTex_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib, "DirectXTex_MD.lib")
#else
#pragma comment(lib, "DirectXTex_MT.lib")
#endif

#endif

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"ChTexture11.h"

using namespace ChD3D11;

static ID3D11Device* SDevice = nullptr;

///////////////////////////////////////////////////////////////////////////////////////
//Texture11Method//
///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateTexture(const std::string& _TexPath)
{
	if (_TexPath.length() <= 0)return;
	if (!D3D11API().IsInit())return;

	ID3D11Device* TmpDevice = D3D11Device();

	CreateTexture(_TexPath, TmpDevice);

}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateTexture(const std::string& _TexPath, ID3D11Device* _Device)
{
	if (_TexPath.length() <= 0)return;
	if (ChPtr::NullCheck(_Device))return;

	Release();

	Device = _Device;

	if (FAILED(DirectX::CreateWICTextureFromFile(
		Device
		, ChStr::ToWString(_TexPath).c_str()
		, (ID3D11Resource**)&BaseTex
		, &TexView)))
	{
		Release();
		return;
	}

	Init(_Device);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateTexture(const std::wstring& _TexPath)
{

	if (_TexPath.length() <= 0)return;
	if (!D3D11API().IsInit())return;

	ID3D11Device* TmpDevice = (D3D11Device());

	CreateTexture(_TexPath, TmpDevice);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateTexture(const std::wstring& _TexPath, ID3D11Device* _Device)
{
	if (_TexPath.length() <= 0)return;
	if (ChPtr::NullCheck(_Device))return;

	Release();

	Device = _Device;

	if (FAILED(DirectX::CreateWICTextureFromFile(
		Device
		, _TexPath.c_str()
		, (ID3D11Resource**)&BaseTex
		, &TexView)))
	{
		Release();
		return;
	}

	Init(_Device);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateColorTexture(
	const ChVec4& _Color
	, const unsigned long _Width
	, const unsigned long _Height
	, const unsigned int _CPUFlg)
{


	if (!D3D11API().IsInit())return;

	ID3D11Device* TmpDevice = (D3D11Device());

	CreateColorTexture(TmpDevice, _Color,_Width,_Height, _CPUFlg);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateColorTexture(
	ID3D11Device* _Device
	, const ChVec4& _Color
	, const unsigned long _Width
	, const unsigned long _Height
	, const unsigned int _CPUFlg)
{

	if (ChPtr::NullCheck(_Device))return;
	if (_Width <= 0 || _Height <= 0)return;
	if (_Width >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION
		|| _Height >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)return;


	Release();

	Device = _Device;

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Width = _Width;
	Desc.Height = _Height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags = _CPUFlg;
	Desc.MiscFlags = 0;

	TextureSize = _Height * _Width;
	PixellData = new ChVec4[TextureSize];

	for (unsigned long h = 0; h < _Height; h++)
	{
		for (unsigned long w = 0; w < _Width; w++)
		{
			PixellData[w + (h * w)] = (_Color);
		}
	}

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = PixellData;
	Data.SysMemPitch = _Width * sizeof(ChVec4);
	Data.SysMemSlicePitch = _Height * _Width * sizeof(ChVec4);

	Device->CreateTexture2D(&Desc, &Data, &BaseTex);

	CreateSRV();

	Init(_Device);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateColorTexture(
	const ChVec4* _ColorArray
	, const unsigned long _Width
	, const unsigned long _Height
	, const unsigned int _CPUFlg)
{
	if (!D3D11API().IsInit())return;

	ID3D11Device* TmpDevice = (D3D11Device());

	CreateColorTexture(TmpDevice, _ColorArray, _Width, _Height,_CPUFlg);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateColorTexture(
	ID3D11Device* _Device
	, const ChVec4* _ColorArray
	, const unsigned long _Width
	, const unsigned long _Height
	, const unsigned int _CPUFlg)
{

	if (ChPtr::NullCheck(_Device))return;
	if (_Width <= 0 || _Height <= 0)return;
	if (_Width >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION
		|| _Height >= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)return;


	Release();

	Device = _Device;

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Width = _Width;
	Desc.Height = _Height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags = _CPUFlg;
	Desc.MiscFlags = 0;

	TextureSize = _Height * _Width;
	PixellData = new ChVec4[TextureSize];

	for (unsigned long h = 0; h < _Height; h++)
	{
		for (unsigned long w = 0; w < _Width; w++)
		{
			PixellData[w + (h * w)] = (_ColorArray[w + (h * w)]);
		}
	}

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = PixellData;
	Data.SysMemPitch = _Width * sizeof(ChVec4);
	Data.SysMemSlicePitch = 0;

	Device->CreateTexture2D(&Desc, &Data, &BaseTex);

	CreateSRV();

	Init(_Device);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateRenderTarget(
	const unsigned long _Width
	, const unsigned long _Height
	, const unsigned int _CPUFlg)
{

	if (!D3D11API().IsInit())return;

	ID3D11Device* TmpDevice = (D3D11Device());
	IDXGISwapChain* Wind = (D3D11API().GetSC());

	CreateRenderTarget(TmpDevice, Wind, _Width, _Height,_CPUFlg);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateRenderTarget(
	ID3D11Device* _Device
	, IDXGISwapChain* _SC
	, const unsigned long _Width
	, const unsigned long _Height
	, const unsigned int _CPUFlg)
{

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_SC))return;

	Release();

	Device = _Device;

	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = _Width;
	txDesc.Height = _Height;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = _CPUFlg;
	txDesc.MiscFlags = 0;

	_Device->CreateTexture2D(&txDesc, NULL, &BaseTex);

	if (ChPtr::NullCheck(BaseTex))return;

	if (FAILED(Device->CreateRenderTargetView(BaseTex, nullptr, &RTView)))
	{
		Release();
	}

	CreateSRV();

	Init(_Device);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateDepthBuffer(
	const float& _Width
	, const float& _Height
	, const unsigned int _CPUFlg)
{

	if (!D3D11API().IsInit())return;

	ID3D11Device* TmpDevice = (D3D11Device());

	CreateDepthBuffer(TmpDevice, _Width, _Height,_CPUFlg);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateDepthBuffer(
	ID3D11Device* _Device
	, const float& _Width
	, const float& _Height
	, const unsigned int _CPUFlg)
{
	if (ChPtr::NullCheck(_Device))return;

	Release();

	Device = _Device;

	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = static_cast<unsigned int>(_Width);
	txDesc.Height = static_cast<unsigned int>(_Height);
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = _CPUFlg;
	txDesc.MiscFlags = 0;
	_Device->CreateTexture2D(&txDesc, NULL, &BaseTex);

	if (ChPtr::NullCheck(BaseTex))return;


	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;

	Device->CreateDepthStencilView(BaseTex, &dsDesc, &DSView);

	CreateSRV();

	Init(_Device);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::Release()
{

	if (ChPtr::NotNullCheck(Sampler)) { Sampler->Release(); Sampler = nullptr; }
	if (ChPtr::NotNullCheck(TexView)) { TexView->Release(); TexView = nullptr; }
	if (ChPtr::NotNullCheck(RTView)) { RTView->Release(); RTView = nullptr; }
	if (ChPtr::NotNullCheck(DSView)) { DSView->Release(); DSView = nullptr; }
	if (ChPtr::NotNullCheck(BaseTex)) { BaseTex->Release(); BaseTex = nullptr; }

	if (TextureSize > 0) 
	{
		TextureSize < 2 ? delete PixellData  : delete[] PixellData;
		TextureSize = 0;
		PixellData = nullptr;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::ClearBackBuffer(ID3D11DeviceContext* _DC, const ChVec4& _BackColor)
{
	if (ChPtr::NullCheck(_DC))return;

	_DC->ClearRenderTargetView(RTView,_BackColor.Val.GetVal());
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::ClearDepthBuffer(
	ID3D11DeviceContext* _DC
	, const UINT _Flgment)
{
	if (ChPtr::NullCheck(_DC))return;

	_DC->ClearDepthStencilView(DSView, _Flgment, 1.0f, 0);
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::InitSampler()
{

	ZeroMemory(&SDesc, sizeof(D3D11_SAMPLER_DESC));
	SDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	UpdateSampler();
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::UpdateSampler()
{
	if (!SDUpdateFlg)return;

	Device->CreateSamplerState(&SDesc, &Sampler);

	SDUpdateFlg = false;
}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::SetDrawData(ID3D11DeviceContext* _DC,unsigned int _TextureNo)
{
	if (ChPtr::NullCheck(TexView))return;

	UpdateSampler();

	_DC->PSSetShaderResources(_TextureNo, 1, &TexView);
	_DC->PSSetSamplers(_TextureNo, 1,&Sampler);

}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::CreateSRV()
{


	if (ChPtr::NullCheck(BaseTex))return;

	D3D11_TEXTURE2D_DESC txDesc;

	BaseTex->GetDesc(&txDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC SDesc;
	SDesc.Format = txDesc.Format;
	SDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SDesc.Texture2D.MipLevels = txDesc.MipLevels;
	SDesc.Texture2D.MostDetailedMip = 0;

	Device->CreateShaderResourceView(BaseTex, &SDesc, &TexView);

	BaseFormat = txDesc.Format;
}

///////////////////////////////////////////////////////////////////////////////////////

ChVec4 Texture11::GetBitColor(
	const unsigned long _Width
	, const unsigned long _Height)
{
	if (!IsTex())return ChVec4(0.0f,0.0f,0.0f,0.0f);
	
	return GetBitColor(_Width, _Height, ChD3D11::D3D11DC());

}

///////////////////////////////////////////////////////////////////////////////////////

ChVec4 Texture11::GetBitColor(
	const unsigned long _Width
	, const unsigned long _Height
	, ID3D11DeviceContext* _DC)
{
	if (!IsTex())return ChVec4(0.0f, 0.0f, 0.0f, 0.0f);
	if (ChPtr::NullCheck(_DC))return ChVec4(0.0f, 0.0f, 0.0f, 0.0f);

	ChVec4 Out = ChVec4(0.0f,0.0f,0.0f,1.0f);

	ChMath::ChVector2Base<unsigned long> Size;

	{
		D3D11_TEXTURE2D_DESC desk;

		BaseTex->GetDesc(&desk);

		Size.x = desk.Width;
		Size.y = desk.Height;

	}

	if (Size.x > _Width || Size.y > _Height)return Out;

	D3D11_MAPPED_SUBRESOURCE map;

	_DC->Map(BaseTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);

	if (BaseFormat == DXGI_FORMAT_R32G32B32A32_FLOAT)
	{
		unsigned long i = (_Width + (_Height * Size.x));
		Out = *(static_cast<ChVec4*>(map.pData) + i);
	}
	else if (BaseFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
	{
		unsigned long i = (_Width + (_Height * Size.x));
		Out = static_cast<float>(*(static_cast<unsigned int*>(map.pData) + i));
	}

	_DC->Unmap(BaseTex,0);

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////////

void Texture11::Init(ID3D11Device* _Device)
{
	InitSampler();

	SDevice = Device;
}

