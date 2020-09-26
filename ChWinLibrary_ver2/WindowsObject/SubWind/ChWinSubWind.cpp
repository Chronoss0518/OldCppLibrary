#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinSubWind.h"

///////////////////////////////////////////////////////////////////////////////////////
//SubWindÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::SubWind::Create(const std::string& _Title
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _ParentHandl)
{
	if (!IsInit())return;

	Release();
	RegisterObj();
	x = _x;
	y = _y;
	w = _w;
	h = _h;

	std::string TmpStr = ClassName;

	HIns = CreateWindow(
		TmpStr.c_str(),
		_Title.c_str(),
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
		_ParentHandl,
		NULL,
		(HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE),
		NULL);
	
	//RegisterObj();
	SetWindowLongPtr(HIns, GWLP_USERDATA, (long)this);



}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::SubWind::Update(const WPARAM& _wParam)
{

	//SendMessage(HIns, WM_PAINT, 0, 0);

}

