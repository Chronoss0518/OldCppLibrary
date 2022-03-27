
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChSprite/ChSprite9.h"
#include"ChStringController9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChStringController9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void StringController9::SetStrTexture(const std::string& _str)
{
	std::string tmpStr;

	D3DXCreateTextureFromFileEx(
		device
		, tmpStr.c_str()
		, size.w, size.h, 1, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_DEFAULT
		, NULL, NULL, NULL
		, &strTex->InsTex());

}

///////////////////////////////////////////////////////////////////////////////////

StringController9::StringController9(
	const LPDIRECT3DDEVICE9 _dv
	, const std::string& _path
	, const std::string& _type
	, const unsigned short _originalWedth
	, const unsigned short _originalHeight)
{
	size.w = _originalWedth;
	size.h = _originalHeight;
	if (size.w == 0 || size.h == 0)return;
	device = _dv;
	strPath = _path;
	typeName = _type;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void StringController9::DrawSprightString(
	const std::string& _str
	, const ChMat_9& _mat
	, Sprite9 &_sp)
{
	if (device == nullptr)return;
	if (_str.length() <= 0)return;

	std::string tmpStr;
	tmpStr = _str + strPath;

	for (unsigned short i = 0; i < _str.length(); i++)
	{
		//char tmpChar[3];
		SetStrTexture(_str);

		_sp.DrawSprite(
			strTex
			, _mat
			, ChVec3_9(0.0f, 0.0f, 0.0f));
	}

}

///////////////////////////////////////////////////////////////////////////////////

void StringController9::SetStringColor(const ChVec4& _color)
{
	strTex->GetBaseColor() = _color;
}

///////////////////////////////////////////////////////////////////////////////////


