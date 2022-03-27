
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChFont9.h"

using namespace ChD3D9;

///////////////////////////////////////////////////////////////////////////////////////
//ChFont9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void DrawFont::Init(const LPDIRECT3DDEVICE9 _dv)
{
	fontType =  "MS ゴシック";

	device = _dv;
	D3DXCreateFont(
		device
		, fontSize.h
		, fontSize.w
		, FW_REGULAR
		, NULL
		, false
		, SHIFTJIS_CHARSET
		, OUT_DEFAULT_PRECIS
		, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, fontType.c_str(), &lpFont);

	SetInitFlg(true);
}

void DrawFont::Release()
{
	if (ChPtr::NullCheck(lpFont))return;
	lpFont->Release();
	lpFont = nullptr;

	SetInitFlg(false);
}

void DrawFont::Draw(
	std::string _drawStr
	, const long _x
	, const long _y
	, ChVec4 _col)
{

	auto col = D3DCOLOR_ARGB(
		static_cast<unsigned char>(_col.a * 255),
		static_cast<unsigned char>(_col.r * 255),
		static_cast<unsigned char>(_col.g * 255),
		static_cast<unsigned char>(_col.b * 255));

	RECT rc = { _x, _y,_x + fontSize.w, _y + fontSize.h };
	lpFont->DrawText(NULL, _drawStr.c_str(), _drawStr.length(), &rc, DT_LEFT | DT_NOCLIP
		, col);
}
