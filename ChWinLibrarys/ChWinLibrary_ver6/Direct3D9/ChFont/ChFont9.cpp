
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

void DrawFont::Init(const LPDIRECT3DDEVICE9 _Dv)
{
	FontType =  "MS ゴシック";

	Device = _Dv;
	D3DXCreateFont(
		Device
		, FontH
		, FontW
		, FW_REGULAR
		, NULL
		, false
		, SHIFTJIS_CHARSET
		, OUT_DEFAULT_PRECIS
		, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, FontType.c_str(), &LpFont);

	SetInitFlg(true);
}

void DrawFont::Release()
{
	if (ChPtr::NullCheck(LpFont))return;
	LpFont->Release();
	LpFont = nullptr;

	SetInitFlg(false);
}

void DrawFont::Draw(
	std::string _DrawStr
	, const long _x
	, const long _y
	, ChVec4 _Col)
{

	auto col = D3DCOLOR_ARGB(
		static_cast<unsigned char>(_Col.a * 255),
		static_cast<unsigned char>(_Col.r * 255),
		static_cast<unsigned char>(_Col.g * 255),
		static_cast<unsigned char>(_Col.b * 255));

	RECT rc = { _x, _y,_x + FontW, _y + FontH };
	LpFont->DrawText(NULL, _DrawStr.c_str(), _DrawStr.length(), &rc, DT_LEFT | DT_NOCLIP
		, col);
}
