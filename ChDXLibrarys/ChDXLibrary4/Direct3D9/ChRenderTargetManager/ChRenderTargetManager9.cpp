
#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"
#include"../../ChInclude/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChRenderTargetManager9.h"

using namespace ChTex;
using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////
//ChRenderTargetManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::Init(
	const LPDIRECT3DDEVICE9& _Dv
	, const unsigned short _WW
	, const unsigned short _WH
	, const ChD3D9::ShaderController* _Shader)
{
	DBData = ChPtr::Make_S<Texture9>();

	DBData->InsOriginalWidth() = _WW;
	DBData->InsOriginalHeight() = _WH;

	DBData->InsSclXSize() = 1.0f;
	DBData->InsSclYSize() = 1.0f;

	Device = _Dv;
	Device->GetRenderTarget(0, &DBData->InsSur());
	Device->GetDepthStencilSurface(&DBData->InsZBu());

	SetInitFlg(true);

	if (ChPtr::NullCheck(_Shader))
	{
		if (!ChD3D9::Shader())return;
		UShader = &ChD3D9::Shader();
		return;
	}
	if (!*_Shader)return;

	UShader = const_cast<ChD3D9::ShaderController*>(_Shader);
}

///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::Release()
{
	ReturnRT();
	RTList.clear();

	SetInitFlg(false);

}

///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::CreateRT(
	const std::string& _DataName
	, const UINT _RTW
	, const UINT _RTH
	, const _D3DFORMAT _FMT)
{
	if (_RTW <= 0 || _RTH <= 0)return;
	if (RTList.find(_DataName) != RTList.end())return;

	auto TmpRT = ChPtr::Make_S<Texture9>();

	TmpRT->CreateMinuColTexture<D3DCOLOR>(
		Device
		, D3DCOLOR_ARGB(0, 0, 0, 0)
		, _RTW
		, _RTH
		, _FMT
		, D3DUSAGE_RENDERTARGET
		, D3DPOOL_DEFAULT);

	if (ChPtr::NullCheck(TmpRT->GetTex()))return;

	TmpRT->CreateSurface(0);

	if (ChPtr::NullCheck(TmpRT->GetSur()))return;

	TmpRT->CreateZBuffer(Device);

	if (ChPtr::NullCheck(TmpRT->GetZBu()))return;

	RTList[_DataName]=TmpRT;

}

///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::SetRT(
	const std::string& _DataName
	, const D3DCOLOR _BackCol)
{
	if (RTList.find(_DataName) == RTList.end())return;
	if (DBData == nullptr)return;

	if (ChPtr::NotNullCheck(UShader))
	{
		if (UShader->IsDraw())return;
	}

	Device->SetRenderTarget(0, RTList[_DataName]->GetSur());
	Device->SetDepthStencilSurface(RTList[_DataName]->GetZBu());


	if (ChPtr::NotNullCheck(UShader))
	{
		UShader->SetRTDraw(true);
		UShader->SetDrawDatas(_BackCol);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::ReturnRT()
{
	if (DBData == nullptr)return;
	Device->SetRenderTarget(0, DBData->GetSur());
	Device->SetDepthStencilSurface(DBData->GetZBu());

	if (ChPtr::NotNullCheck(UShader))
	{
		UShader->SetRTDraw(false);
	}

}
