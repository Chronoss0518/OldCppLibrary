#include<Windows.h>
#include"../../ChGameIncludeFile.h"
#include"ChSubWind.h"

///////////////////////////////////////////////////////////////////////////////////////
//SubWindÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::SubWind::Create(const std::string& _Title
	, const int _x
	, const int _y
	, const int _w
	, const int _h)
{
	Release();

	x = _x;
	y = _y;
	w = _w;
	h = _h;

	HIns = CreateWindow(
		"STATIC",  // Predefined class; Unicode assumed 
		_Title.c_str(),      // WindTitle 
		WS_VISIBLE 
		| WS_CHILD 
		| WS_CAPTION
		| WS_TILED
		| WS_CLIPCHILDREN
		| WS_MINIMIZEBOX
		| WS_THICKFRAME,  // Styles 
		_x,         // x position 
		_y,         // y position 
		_w,        // Button width
		_h,        // Button height
		HOwn,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

/*
	ShowWindow(HIns, SW_SHOWNORMAL);
	UpdateWindow(HIns);
*/
}




