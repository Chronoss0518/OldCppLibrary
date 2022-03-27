
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinRadioButton.h"


///////////////////////////////////////////////////////////////////////////////////////
//RadioButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::RadioButton::Create(const std::string& _buttonText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _parentHandl
	, const ChStd::Bool _glpFlg)
{
	if (!IsInit())return;

	Release();

	x = _x;
	y = _y;
	w = _w;
	h = _h;

	RegisterObj();

	hIns = CreateWindow(
		"BUTTON",  // Predefined class; Unicode assumed 
		_buttonText.c_str(),      // Button text 
		WS_VISIBLE
		| WS_CHILD
		| (_glpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN,  // Styles 
		_x,         // x position 
		_y,         // y position 
		_w,        // Button width
		_h,        // Button height
		_parentHandl,     // Parent window
		(HMENU)myID,       // No menu.
		(HINSTANCE)GetWindowLong(hOwn, GWL_HINSTANCE),
		NULL);      // Pointer not needed.


	RedrawWindow(hOwn, nullptr, nullptr, NULL);

}
