#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinSubWind.h"

///////////////////////////////////////////////////////////////////////////////////////
//SubWindÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::SubWind::Create(const std::string& _title
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _parentHandl)
{
	if (!IsInit())return;

	Release();
	RegisterObj();
	x = _x;
	y = _y;
	w = _w;
	h = _h;

	std::string tmpStr = className;

	hIns = CreateWindow(
		tmpStr.c_str(),
		_title.c_str(),
		WS_VISIBLE
		| WS_CHILD 
		| WS_CAPTION
		| WS_TILED
		| WS_CLIPCHILDREN
		| WS_MINIMIZEBOX
		| WS_THICKFRAME,
		_x,
		_y,
		_w,
		_h,
		_parentHandl,
		NULL,
		(HINSTANCE)GetWindowLong(hOwn, GWL_HINSTANCE),
		NULL);
	
	//RegisterObj();
	SetWindowLongPtr(hIns, GWLP_USERDATA, (long)this);



}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::SubWind::Update(const WPARAM& _wParam)
{

	//SendMessage(HIns, WM_PAINT, 0, 0);

}

