
#include"../../ChGameIncludeFile.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

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
	, const unsigned short _WH)
{
	DBData = ChPtr::Make_S<Texture9>();

	DBData->InsOriginalWidth() = _WW;
	DBData->InsOriginalHeight() = _WH;

	DBData->InsSclXSize() = 1.0f;
	DBData->InsSclYSize() = 1.0f;

	Device = _Dv;
	Device->GetRenderTarget(0, &DBData->InsSur());
	Device->GetDepthStencilSurface(&DBData->InsZBu());
}

///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::Release()
{
	ReturnRT();
	RTList.clear();
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
		, D3DCOLOR_ARGB(255, 0, 0, 0)
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

void RenderTargetManager9::SetRT(const std::string& _DataName)
{
	if (RTList.find(_DataName) == RTList.end())return;
	if (DBData == nullptr)return;
	Device->SetRenderTarget(0, RTList[_DataName]->GetSur());
	Device->SetDepthStencilSurface(RTList[_DataName]->GetZBu());

	Device->Clear(
		0
		, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_ARGB
		(
			ClearColor.a
			, ClearColor.r
			, ClearColor.g
			, ClearColor.b
		)
		, 1.0f, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void RenderTargetManager9::ReturnRT()
{
	if (DBData == nullptr)return;
	Device->SetRenderTarget(0, DBData->GetSur());
	Device->SetDepthStencilSurface(DBData->GetZBu());

}
