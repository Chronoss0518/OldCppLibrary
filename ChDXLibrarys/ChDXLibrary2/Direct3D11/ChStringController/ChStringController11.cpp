
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
#include"../ChSprite/ChSprite9.h"
#include"ChStringController9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChStringController9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void StringController9::SetStrTexture(const std::string& _Str)
{
	std::string TmpStr;

	D3DXCreateTextureFromFileEx(
		Device
		, TmpStr.c_str()
		, W, H, 1, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_DEFAULT
		, NULL, NULL, NULL
		, &StrTex->InsTex());

}

///////////////////////////////////////////////////////////////////////////////////

StringController9::StringController9(
	const LPDIRECT3DDEVICE9 _Dv
	, const std::string& _Path
	, const std::string& _Type
	, const unsigned short _OriginalWedth
	, const unsigned short _OriginalHeight)
{
	W = _OriginalWedth;
	H = _OriginalHeight;
	if (W == 0 || H == 0)return;
	Device = _Dv;
	StrPath = _Path;
	TypeName = _Type;
}

///////////////////////////////////////////////////////////////////////////////////

void StringController9::DrawSprightString(
	const std::string& _Str
	, const ChMat_9& _Mat
	, Sprite9 &_Sp)
{
	if (Device == nullptr)return;
	if (_Str.length() <= 0)return;

	std::string TmpStr;
	TmpStr = _Str + StrPath;

	for (unsigned short i = 0; i < _Str.length(); i++)
	{
		//char TmpChar[3];
		SetStrTexture(_Str);

		_Sp.DrawSprite(
			StrTex
			, _Mat
			, ChVec3_9(0.0f, 0.0f, 0.0f));
	}

}

///////////////////////////////////////////////////////////////////////////////////

void StringController9::SetStringColor(const ChStd::COLOR255& _Color)
{
	StrTex->GetBaseColor() = _Color;
}

///////////////////////////////////////////////////////////////////////////////////


