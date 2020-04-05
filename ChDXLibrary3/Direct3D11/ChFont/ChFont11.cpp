
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

#include"ChFont9.h"

using namespace ChD3D9;

///////////////////////////////////////////////////////////////////////////////////////
//ChFont9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void DrawFont::Init(const LPDIRECT3DDEVICE9 _Dv)
{
	FontType = (char*)malloc(sizeof(char) * 50);

	strcpy(FontType, "MS ゴシック");
	Device = _Dv;
	D3DXCreateFont(
		Device
		, FontH
		, FontW
		, FW_REGULAR
		, NULL
		, ChStd::False
		, SHIFTJIS_CHARSET
		, OUT_DEFAULT_PRECIS
		, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, FontType, &LpFont);


}

void DrawFont::Release()
{
	if (ChPtr::NullCheck(LpFont))return;
	free(FontType);
	LpFont->Release();
	LpFont = nullptr;

}

void DrawFont::Draw(
	std::string _DrawStr
	, const long _x
	, const long _y
	, ChStd::COLOR255 _Col)
{

	RECT rc = { _x, _y,_x + FontW, _y + FontH };
	LpFont->DrawText(NULL, _DrawStr.c_str(), _DrawStr.length(), &rc, DT_LEFT | DT_NOCLIP
		, D3DCOLOR_ARGB(_Col.a, _Col.r, _Col.g, _Col.b));
}
